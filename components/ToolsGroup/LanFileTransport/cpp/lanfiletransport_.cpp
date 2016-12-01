/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "lanfiletransport.h"

// Qt lib import
#include <QHostInfo>
#include <QStandardPaths>
#include <QtConcurrent>

// JQNetwork lib import
#include <JQNetworkLan>
#include <JQNetworkConnect>
#include <JQNetworkPackage>
#include <JQNetworkServer>
#include <JQNetworkClient>

// JQLibrary import
#include "JQFile.h"

using namespace LanFileTransport;

#define SERVERPORT 25230
#define LANPORT 25229
#define LANMULTICASTADDRESS QHostAddress( "229.134.50.25" )

Manage::Manage():
    jqNetworkServer_( JQNetworkServer::createServer( SERVERPORT, QHostAddress::Any, true ) ),
    jqNetworkClient_( JQNetworkClient::createClient( true ) ),
    jqNetworkLan_( JQNetworkLan::createLan( LANMULTICASTADDRESS, LANPORT ) ),
    savePath_( QStandardPaths::writableLocation( QStandardPaths::DownloadLocation ) )
{
    jqNetworkServer_->connectSettings()->filePathProvider = [ this ](const auto &, const auto &package, const auto &fileName)->QString
    {
        const auto &&path = package->appendData()[ "path" ].toString();

        if ( path.isEmpty() )
        {
            qDebug() << "filePathProvider: package append dont contains path, fileName:" << fileName;
            return "";
        }

        return this->savePath_ + path;
    };
    jqNetworkServer_->serverSettings()->packageReceivedCallback = [ this ](const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
    {
//        qDebug() << "packageReceivedCallback:" << package->appendData();

        connect->replyPayloadData( package->randomFlag(), { } );
    };

    jqNetworkClient_->clientSettings()->packageSendingCallback = [ this ](
            const JQNetworkConnectPointer &,
            const QString &hostName,
            const quint16 &,
            const qint32 &,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        )
    {
        this->mutex_.lock();

        auto it = this->mapForConnectSendCounter_.find( hostName );

        if ( it == this->mapForConnectSendCounter_.end() )
        {
            qDebug() << "packageSendingCallback: error";

            this->mutex_.unlock();
            return;
        }

        it.value().alreadySendSizeTotal += payloadCurrentSize;

        if ( ( payloadCurrentIndex + payloadCurrentSize ) == payloadTotalSize )
        {
            ++it.value().alreadySendFileCount;
        }

        this->emitSendingSignal( hostName, it.value() );

        this->mutex_.unlock();
    };

    jqNetworkLan_->setAppendData( this->localHostName() );
    jqNetworkLan_->lanSettings()->lanNodeListChangedCallback = [ this ]()
    {
        this->refreshLanNodes();
    };

    qDebug() << "JQNetworkServer begin:" << jqNetworkServer_->begin();
    qDebug() << "JQNetworkClient begin:" << jqNetworkClient_->begin();
    qDebug() << "JQNetworkLan begin:" << jqNetworkLan_->begin();
}

void Manage::setShowSelf(const bool &showSelf)
{
    showSelf_ = showSelf;

    this->refreshLanNodes();
}

void Manage::sendOnlinePing()
{
    jqNetworkLan_->sendOnline();
}

QVariantList Manage::lanNodes()
{
    mutex_.lock();

    const auto lanNodes = lanNodes_;

    mutex_.unlock();

    return lanNodes;
}

QString Manage::localHostName() const
{
#ifdef Q_OS_MAC
    return QHostInfo::localHostName().replace( ".local", "" );
#endif
    return QHostInfo::localHostName();
}

QString Manage::localHostAddress()
{
    auto lanAddressEntries = jqNetworkLan_->lanAddressEntries();
    if ( lanAddressEntries.isEmpty() ) { return ""; }
    return lanAddressEntries.first().ip.toString();
}

QString Manage::localNodeMarkSummary()
{
    return jqNetworkLan_->nodeMarkSummary();
}

QString Manage::transport(const QString &hostAddress, const QVariantList &filePaths)
{
    if ( filePaths.isEmpty() ) { return "cancel"; }

    qint64 sizeTotal = 0;
    int fileCount = 0;
    QString rootPath;
    QSharedPointer< QList< QPair< QString, QFileInfo > > > sourceSmallFileList( new QList< QPair< QString, QFileInfo > > ); // [ { path, fileInfo }, ... ]
    QSharedPointer< QList< QPair< QString, QFileInfo > > > sourceBigFileList( new QList< QPair< QString, QFileInfo > > ); // [ { path, fileInfo }, ... ]

    auto pushFileToList = [ &sizeTotal, &fileCount, &sourceSmallFileList, &sourceBigFileList, &rootPath ](const QFileInfo &fileInfo)
    {
        if ( !fileInfo.isFile() || !fileInfo.exists() ) { return; }

        if ( rootPath.isEmpty() )
        {
            qDebug() << "Manage::transport: error";
            return;
        }

        sizeTotal += fileInfo.size();
        ++fileCount;

        if ( fileInfo.size() > 16 * 1024 * 1024 )
        {
            sourceBigFileList->push_back( { fileInfo.filePath().mid( rootPath.size() ), fileInfo } );
        }
        else
        {
            sourceSmallFileList->push_back( { fileInfo.filePath().mid( rootPath.size() ), fileInfo } );
        }
    };

    for ( const auto &filePath: filePaths )
    {
        auto filePath_ = filePath.toString();
        if ( filePath_.endsWith( "/" ) )
        {
            filePath_.remove( filePath_.size() - 1, 1 );
        }

        QFileInfo currentFileInfo( filePath_ );

        if ( rootPath.isEmpty() )
        {
            rootPath = currentFileInfo.path();
        }

        if ( currentFileInfo.isFile() )
        {
            pushFileToList( currentFileInfo );
        }
        else
        {
            JQFile::foreachFileFromDirectory(
                        QDir( filePath_ ),
                        [ &pushFileToList ](const QFileInfo &fileInfo)
                        {
                            pushFileToList( fileInfo );
                        },
                        true
                    );
        }
    }

    mutex_.lock();

    mapForConnectSendCounter_[ hostAddress ] = { 0, 0, sizeTotal, fileCount };

    mutex_.unlock();

    QSharedPointer< JQNetworkConnectPointerAndPackageSharedPointerFunction > continueSend( new JQNetworkConnectPointerAndPackageSharedPointerFunction );

    *continueSend = [ this, continueSend, sourceSmallFileList, sourceBigFileList, hostAddress ](const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer &)
    {
        QPair< QString, QFileInfo > currentPair;

        if ( !sourceSmallFileList->isEmpty() )
        {
            currentPair = sourceSmallFileList->first();
            sourceSmallFileList->pop_front();
        }
        else if ( !sourceBigFileList->isEmpty() )
        {
            currentPair = sourceBigFileList->first();
            sourceBigFileList->pop_front();
        }
        else
        {
            emit this->sendFinish( hostAddress );
            return;
        }

        this->jqNetworkClient_->sendFileData(
                    hostAddress,
                    SERVERPORT,
                    currentPair.second,
                    { { "path", currentPair.first } },
                    *continueSend,
                    nullptr
        );
    };

    ( *continueSend )( JQNetworkConnectPointer(), JQNetworkPackageSharedPointer() );

    return "OK";
}

QString Manage::savePath()
{
    return savePath_;
}

void Manage::refreshLanNodes()
{
    qDebug() << "refreshLanNodes";

    QVariantList buf;

    for ( const auto &lanNode: this->jqNetworkLan_->availableLanNodes() )
    {
        qDebug() << "refreshLanNodes:" << lanNode.matchAddress;

        const auto &hostAddress = lanNode.matchAddress.toString();

        if ( !showSelf_ && lanNode.isSelf ) { continue; }

        auto connect = this->jqNetworkClient_->getConnect( hostAddress, SERVERPORT );
        if ( connect )
        {
            this->mapForConnectToHostAddress_[ connect.data() ] = hostAddress;
        }
        else
        {
            if ( !this->jqNetworkClient_->waitForCreateConnect( hostAddress, SERVERPORT ) )
            {
                qDebug() << "connect fail:" << hostAddress;
                continue;
            }
        }

        buf.push_back( QVariantMap( {
                                        { "nodeMarkSummary", lanNode.nodeMarkSummary },
                                        { "hostName", lanNode.appendData },
                                        { "hostAddress", hostAddress }
                                    } ) );
    }

    mutex_.lock();

    lanNodes_ = buf;

    mutex_.unlock();

    emit this->lanNodeChanged();
}

void Manage::emitSendingSignal(const QString &hostName, const SendCounter &counter)
{
//    qDebug() << "emitSendingSignal:" << hostName << counter.alreadySendSizeTotal << counter.alreadySendFileCount << counter.sizeTotal << counter.fileCount;

    qreal sendPercentage = ( ( (double)counter.alreadySendSizeTotal / (double)counter.sizeTotal ) + ( (double)counter.alreadySendFileCount / (double)counter.fileCount ) ) / 2.0;

    emit this->sending( hostName, sendPercentage );
}
