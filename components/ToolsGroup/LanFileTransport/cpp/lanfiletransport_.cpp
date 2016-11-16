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

// JQNetwork lib import
#include <JQNetworkLan>
#include <JQNetworkConnect>
#include <JQNetworkPackage>
#include <JQNetworkServer>
#include <JQNetworkClient>

// JQLibrary import
#include "JQFile.h"
#include "JQFilePack.h"

using namespace LanFileTransport;

Manage::Manage():
    jqNetworkServer_( JQNetworkServer::createServer( 25219 ) ),
    jqNetworkClient_( JQNetworkClient::createClient() ),
    jqNetworkLan_( JQNetworkLan::createLan( QHostAddress( "229.134.50.24" ), 25218 ) )
{
    jqNetworkServer_->serverSettings()->packageReceivedCallback = [ this ](const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
    {
        const auto &&sourceBuffer = package->payloadData();

        const auto &&unpackResult = JQFilePack::unpack( sourceBuffer, this->savePath() );

        if ( !unpackResult.first )
        {
            qDebug() << "unpack error";
            return;
        }

        connect->replyPayloadData( package->randomFlag(), { } );
    };

    jqNetworkClient_->clientSettings()->packageSendingCallback = [ this ](
            const JQNetworkConnectPointer &,
            const QString &hostName,
            const quint16 &,
            const qint32 &,
            const qint64 &payloadCurrentIndex,
            const qint64 &,
            const qint64 &payloadTotalSize
        )
    {
        emit this->sending( hostName, payloadCurrentIndex, payloadTotalSize );
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
    return QHostInfo::localHostName().replace(".local", "");
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

    QFileInfoList sources;

    for ( const auto &filePath: filePaths )
    {
        auto filePath_ = filePath.toString();
        if ( filePath_.endsWith( "/" ) )
        {
            filePath_.remove( filePath_.size() - 1, 1 );
        }

        sources.push_back( filePath_ );
    }

    QByteArray targetBuffer;

    const auto &&packResult = JQFilePack::pack( sources, targetBuffer );

    if ( !packResult.first ) { return "packFail"; }

    jqNetworkClient_->sendPayloadData(
                hostAddress,
                25219,
                targetBuffer,
                [ this, hostAddress ](const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer &)
                {
                    emit this->sendFinish( hostAddress );
                }
            );

    return "OK";
}

QString Manage::savePath()
{
    return QStandardPaths::writableLocation( QStandardPaths::DownloadLocation );
}

void Manage::refreshLanNodes()
{
    qDebug() << "refreshLanNodes";

    QVariantList buf;

    for ( const auto &lanNode: this->jqNetworkLan_->availableLanNodes() )
    {
        qDebug() << lanNode.matchAddress;

        const auto &hostAddress = lanNode.matchAddress.toString();

        if ( !showSelf_ && lanNode.isSelf ) { continue; }

        auto connect = this->jqNetworkClient_->getConnect( hostAddress, 25219 );
        if ( connect )
        {
            this->mapForConnectToHostAddress_[ connect.data() ] = hostAddress;
        }
        else
        {
            if ( !this->jqNetworkClient_->waitForCreateConnect( hostAddress, 25219 ) )
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
