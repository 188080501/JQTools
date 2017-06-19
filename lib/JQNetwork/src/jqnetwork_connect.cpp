/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_connect.h"

// C lib import
#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
#   include <utime.h>
#endif

// Qt lib import
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QStandardPaths>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkProxy>

// JQNetwork lib import
#include <JQNetworkPackage>

// JQNetworkConnectSettings
void JQNetworkConnectSettings::setFilePathProviderToDefaultDir()
{
    const auto &&defaultDir = QStandardPaths::writableLocation( QStandardPaths::TempLocation );

    filePathProvider = [ defaultDir ](const auto &, const auto &, const auto &fileName)
    { return QString( "%1/JQNetworkReceivedFile/%2" ).arg( defaultDir, fileName ); };
}

void JQNetworkConnectSettings::setFilePathProviderToDir(const QDir &dir)
{
    filePathProvider = [ dir ](const auto &, const auto &, const auto &fileName)
    { return QString( "%1/%2" ).arg( dir.path(), fileName ); };
}

// JQNetworkConnect
JQNetworkConnect::JQNetworkConnect(const JQNetworkConnectSettingsSharedPointer &connectSettings):
    connectSettings_( connectSettings ),
    tcpSocket_( new QTcpSocket ),
    connectCreateTime_( QDateTime::currentMSecsSinceEpoch() )
{
    connect( tcpSocket_.data(), &QAbstractSocket::stateChanged, this, &JQNetworkConnect::onTcpSocketStateChanged, Qt::DirectConnection );
    connect( tcpSocket_.data(), &QAbstractSocket::bytesWritten, this, &JQNetworkConnect::onTcpSocketBytesWritten, Qt::DirectConnection );
    connect( tcpSocket_.data(), &QTcpSocket::readyRead, this, &JQNetworkConnect::onTcpSocketReadyRead, Qt::DirectConnection );

    if ( connectSettings_->fileTransferEnabled && !connectSettings_->filePathProvider )
    {
        connectSettings_->setFilePathProviderToDefaultDir();

        qDebug() << "JQNetworkConnect: fileTransfer is enabled, but filePathProvider is null, use default dir:"
                 << connectSettings_->filePathProvider( JQNetworkConnectPointer( nullptr ), JQNetworkPackageSharedPointer( nullptr ), QString() );
    }

#ifdef Q_OS_IOS

    static bool flag = true;
    if ( flag )
    {
        flag = false;

        QTcpSocket socket;
        socket.setProxy( QNetworkProxy::NoProxy );
        socket.connectToHost( "baidu.com", 12345 );
        socket.waitForConnected( 10 );
    }

#endif
}

void JQNetworkConnect::createConnect(
        const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
        const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
        const JQNetworkConnectSettingsSharedPointer &connectSettings,
        const QString &hostName,
        const quint16 &port
    )
{
    JQNetworkConnectSharedPointer newConnect( new JQNetworkConnect( connectSettings ) );
    newConnect->runOnConnectThreadCallback_ = runOnConnectThreadCallback;
    newConnect->sendRandomFlagRotaryIndex_ = connectSettings->randomFlagRangeStart - 1;

    JQNETWORK_NULLPTR_CHECK( onConnectCreatedCallback );
    onConnectCreatedCallback( newConnect );

    newConnect->startTimerForConnectToHostTimeOut();

    newConnect->tcpSocket_->setProxy( QNetworkProxy::NoProxy );
    newConnect->tcpSocket_->connectToHost( hostName, port );
}

void JQNetworkConnect::createConnect(
        const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
        const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
        const JQNetworkConnectSettingsSharedPointer &connectSettings,
        const qintptr &socketDescriptor
    )
{
    JQNetworkConnectSharedPointer newConnect( new JQNetworkConnect( connectSettings ) );
    newConnect->runOnConnectThreadCallback_ = runOnConnectThreadCallback;
    newConnect->sendRandomFlagRotaryIndex_ = connectSettings->randomFlagRangeStart - 1;

    JQNETWORK_NULLPTR_CHECK( onConnectCreatedCallback );
    onConnectCreatedCallback( newConnect );

    newConnect->startTimerForConnectToHostTimeOut();

    newConnect->tcpSocket_->setSocketDescriptor( socketDescriptor );
}

void JQNetworkConnect::close()
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::close" );

    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    this->onReadyToDelete();
}

qint32 JQNetworkConnect::sendPayloadData(
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::sendPayloadData", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto currentRandomFlag = this->nextRandomFlag();

    const auto &&readySendPayloadDataSucceed = this->readySendPayloadData(
                currentRandomFlag,
                targetActionFlag,
                payloadData,
                appendData,
                succeedCallback,
                failCallback
            );
    if ( !readySendPayloadDataSucceed ) { return 0; }

    return currentRandomFlag;
}

qint32 JQNetworkConnect::sendVariantMapData(
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::sendVariantMapData", 0 );

    return this->sendPayloadData(
                targetActionFlag,
                QJsonDocument( QJsonObject::fromVariantMap( variantMap ) ).toJson( QJsonDocument::Compact ),
                appendData,
                succeedCallback,
                failCallback
            );
}

qint32 JQNetworkConnect::sendFileData(
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::sendFileData", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto currentRandomFlag = this->nextRandomFlag();

    const auto &&readySendFileDataSucceed = this->readySendFileData(
                currentRandomFlag,
                targetActionFlag,
                fileInfo,
                appendData,
                succeedCallback,
                failCallback
            );
    if ( !readySendFileDataSucceed ) { return 0; }

    return currentRandomFlag;
}

qint32 JQNetworkConnect::replyPayloadData(
        const qint32 &receivedPackageRandomFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::replyPayloadData", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto &&readySendPayloadDataSucceed = this->readySendPayloadData(
                receivedPackageRandomFlag,
                { }, // empty targetActionFlag
                payloadData,
                appendData,
                nullptr,
                nullptr
            );
    if ( !readySendPayloadDataSucceed ) { return 0; }

    return receivedPackageRandomFlag;
}

qint32 JQNetworkConnect::replyVariantMapData(
        const qint32 &receivedPackageRandomFlag,
        const QVariantMap &variantMap,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::replyVariantMapData", 0 );

    return this->replyPayloadData(
                receivedPackageRandomFlag,
                QJsonDocument( QJsonObject::fromVariantMap( variantMap ) ).toJson( QJsonDocument::Compact ),
                appendData
            );
}

qint32 JQNetworkConnect::replyFile(
        const qint32 &receivedPackageRandomFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::replyFile", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto &&readySendFileData = this->readySendFileData(
                receivedPackageRandomFlag,
                { }, // empty targetActionFlag
                fileInfo,
                appendData,
                nullptr,
                nullptr
            );
    if ( !readySendFileData ) { return 0; }

    return receivedPackageRandomFlag;
}

bool JQNetworkConnect::putPayloadData(
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::putPayloadData", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto &&readySendPayloadDataSucceed = this->readySendPayloadData(
                2000000001,
                targetActionFlag,
                payloadData,
                appendData,
                nullptr,
                nullptr
            );
    if ( !readySendPayloadDataSucceed ) { return 0; }

    return true;
}

bool JQNetworkConnect::putVariantMapData(
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::putVariantMapData", 0 );

    return this->putPayloadData(
                targetActionFlag,
                QJsonDocument( QJsonObject::fromVariantMap( variantMap ) ).toJson( QJsonDocument::Compact ),
                appendData
            );
}

bool JQNetworkConnect::putFile(
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkConnect::putFile", 0 );

    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    const auto &&readySendFileData = this->readySendFileData(
                2000000001,
                targetActionFlag,
                fileInfo,
                appendData,
                nullptr,
                nullptr
            );
    if ( !readySendFileData ) { return 0; }

    return true;
}

void JQNetworkConnect::onTcpSocketStateChanged()
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    const auto &&state = tcpSocket_->state();

//    qDebug() << "onTcpSocketStateChanged:" << this << ": state:" << state;

    switch ( state )
    {
        case QAbstractSocket::ConnectedState:
        {
            if ( !timerForConnectToHostTimeOut_.isNull() )
            {
                timerForConnectToHostTimeOut_.clear();
            }

            JQNETWORK_NULLPTR_CHECK( connectSettings_->connectToHostSucceedCallback );
            connectSettings_->connectToHostSucceedCallback( this );

            onceConnectSucceed_ = true;
            connectSucceedTime_ = QDateTime::currentMSecsSinceEpoch();

            break;
        }
        case QAbstractSocket::UnconnectedState:
        {
            switch ( tcpSocket_->error() )
            {
                case QAbstractSocket::UnknownSocketError:
                {
                    if ( onceConnectSucceed_ ) { break; }

                    JQNETWORK_NULLPTR_CHECK( connectSettings_->connectToHostErrorCallback );
                    connectSettings_->connectToHostErrorCallback( this );

                    break;
                }
                case QAbstractSocket::RemoteHostClosedError:
                {
                    JQNETWORK_NULLPTR_CHECK( connectSettings_->remoteHostClosedCallback );
                    connectSettings_->remoteHostClosedCallback( this );
                    break;
                }
                case QAbstractSocket::HostNotFoundError:
                case QAbstractSocket::ConnectionRefusedError:
                {
                    JQNETWORK_NULLPTR_CHECK( connectSettings_->connectToHostErrorCallback );
                    connectSettings_->connectToHostErrorCallback( this );
                    break;
                }
                default:
                {
                    qDebug() << "onTcpSocketStateChanged: unknow error:" << tcpSocket_->error();
                    break;
                }
            }

            this->onReadyToDelete();
            break;
        }
        default: { break; }
    }
}

void JQNetworkConnect::onTcpSocketBytesWritten(const qint64 &bytes)
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    waitForSendBytes_ -= bytes;
    alreadyWrittenBytes_ += bytes;

//    qDebug() << "onTcpSocketBytesWritten:" << waitForSendBytes_ << alreadyWrittenBytes_ << QThread::currentThread();
}

void JQNetworkConnect::onTcpSocketReadyRead()
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    const auto &&data = tcpSocket_->readAll();

    tcpSocketBuffer_.append( data );

//    qDebug() << tcpSocketBuffer_.size() << data.size();

    forever
    {
        const auto &&checkReply = JQNetworkPackage::checkDataIsReadyReceive( tcpSocketBuffer_ );

        if ( checkReply > 0 )
        {
            return;
        }
        else if ( checkReply < 0 )
        {
            tcpSocketBuffer_.remove( 0, checkReply * -1 );
        }
        else
        {
            auto package = JQNetworkPackage::readPackage( tcpSocketBuffer_ );

            if ( package->isCompletePackage() )
            {
                switch ( package->packageFlag() )
                {
                    case JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG:
                    case JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG:
                    {
                        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                        connectSettings_->packageReceivingCallback( this, package->randomFlag(), 0, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                        this->onDataTransportPackageReceived( package );
                        break;
                    }
                    case JQNETWORKPACKAGE_PAYLOADDATAREQUESTPACKGEFLAG:
                    {
                        if ( !sendPayloadPackagePool_.contains( package->randomFlag() ) )
                        {
                            qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: no contains randonFlag:" << package->randomFlag();
                            break;
                        }

                        auto &packages = sendPayloadPackagePool_[ package->randomFlag() ];

                        if ( packages.isEmpty() )
                        {
                            qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: packages is empty:" << package->randomFlag();
                            break;
                        }

                        auto nextPackage = packages.first();
                        packages.pop_front();

                        this->sendPackageToRemote( nextPackage );

                        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageSendingCallback );
                        connectSettings_->packageSendingCallback(
                                    this,
                                    package->randomFlag(),
                                    nextPackage->payloadDataOriginalIndex(),
                                    nextPackage->payloadDataOriginalCurrentSize(),
                                    nextPackage->payloadDataTotalSize()
                                );

                        if ( packages.isEmpty() )
                        {
                            sendPayloadPackagePool_.remove( package->randomFlag() );
                        }

                        break;
                    }
                    case JQNETWORKPACKAGE_FILEDATAREQUESTPACKGEFLAG:
                    {
                        const auto &&itForFile = waitForSendFiles_.find( package->randomFlag() );
                        const auto &&fileIsContains = itForFile != waitForSendFiles_.end();

                        if ( !fileIsContains )
                        {
                            qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: Not contains file, randomFlag:" << package->randomFlag();
                            break;
                        }

                        const auto &&currentFileData = itForFile.value()->read( connectSettings_->cutPackageSize );

                        this->sendPackageToRemote(
                                    JQNetworkPackage::createFileTransportPackage(
                                        { }, // empty targetActionFlag,
                                        { }, // empty fileInfo
                                        currentFileData,
                                        { }, // empty appendData
                                        package->randomFlag(),
                                        this->needCompressionPayloadData( currentFileData.size() )
                                    )
                                );

                        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageSendingCallback );
                        connectSettings_->packageSendingCallback(
                                    this,
                                    package->randomFlag(),
                                    itForFile.value()->pos() - currentFileData.size(),
                                    currentFileData.size(),
                                    itForFile.value()->size()
                                );

                        if ( itForFile.value()->atEnd() )
                        {
                            itForFile.value()->close();
                            waitForSendFiles_.erase( itForFile );
                        }

                        break;
                    }
                    default:
                    {
                        qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: unknow packageFlag (isCompletePackage):" << package->packageFlag();
                        break;
                    }
                }
            }
            else
            {
                switch ( package->packageFlag() )
                {
                    case JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG:
                    {
                        const auto &&itForPackage = receivePayloadPackagePool_.find( package->randomFlag() );
                        const auto &&packageIsCached = itForPackage != receivePayloadPackagePool_.end();

                        if ( packageIsCached )
                        {
                            auto payloadCurrentIndex = ( *itForPackage )->payloadDataCurrentSize();
                            JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                            connectSettings_->packageReceivingCallback( this, package->randomFlag(), payloadCurrentIndex, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                            if ( !(*itForPackage)->mixPackage( package ) )
                            {
                                receivePayloadPackagePool_.erase( itForPackage );
                                return;
                            }

                            if ( (*itForPackage)->isAbandonPackage() )
                            {
                                continue;
                            }

                            if ( (*itForPackage)->isCompletePackage() )
                            {
                                this->onDataTransportPackageReceived( *itForPackage );
                                receivePayloadPackagePool_.erase( itForPackage );
                            }
                            else
                            {
                                this->sendDataRequestToRemote( package );
                            }
                        }
                        else
                        {
                            JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                            connectSettings_->packageReceivingCallback( this, package->randomFlag(), 0, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                            receivePayloadPackagePool_[ package->randomFlag() ] = package;

                            this->sendDataRequestToRemote( package );
                        }
                        break;
                    }
                    default:
                    {
                        qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: unknow packageFlag:" << package->packageFlag();
                        break;
                    }
                }
            }
        }
    }
}

void JQNetworkConnect::onTcpSocketConnectToHostTimeOut()
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( timerForConnectToHostTimeOut_ );
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    JQNETWORK_NULLPTR_CHECK( connectSettings_->connectToHostTimeoutCallback );
    connectSettings_->connectToHostTimeoutCallback( this );

    this->onReadyToDelete();
}

void JQNetworkConnect::onSendPackageCheck()
{
//    qDebug() << "onSendPackageCheck:" << QThread::currentThread() << this->thread();

    if ( onReceivedCallbacks_.isEmpty() )
    {
        timerForSendPackageCheck_.clear();
    }
    else
    {
        const auto &&currentTime = QDateTime::currentMSecsSinceEpoch();

        auto it = onReceivedCallbacks_.begin();

        while ( ( it != onReceivedCallbacks_.end() ) &&
                ( ( currentTime - it->sendTime ) > connectSettings_->maximumReceivePackageWaitTime ) )
        {
            if ( it->failCallback )
            {
                JQNETWORK_NULLPTR_CHECK( connectSettings_->waitReplyPackageFailCallback );
                connectSettings_->waitReplyPackageFailCallback( this, it->failCallback );
            }

            onReceivedCallbacks_.erase( it );
            it = onReceivedCallbacks_.begin();
        }

        if ( !onReceivedCallbacks_.isEmpty() )
        {
            timerForSendPackageCheck_->start();
        }
    }
}

void JQNetworkConnect::startTimerForConnectToHostTimeOut()
{
    if ( timerForConnectToHostTimeOut_ )
    {
        qDebug() << "startTimerForConnectToHostTimeOut: error, timer already started";
        return;
    }

    if ( connectSettings_->maximumConnectToHostWaitTime == -1 ) { return; }

    timerForConnectToHostTimeOut_.reset( new QTimer );
    connect( timerForConnectToHostTimeOut_.data(), &QTimer::timeout,
             this, &JQNetworkConnect::onTcpSocketConnectToHostTimeOut,
             Qt::DirectConnection );

    timerForConnectToHostTimeOut_->setSingleShot( true );
    timerForConnectToHostTimeOut_->start( connectSettings_->maximumConnectToHostWaitTime );
}

void JQNetworkConnect::startTimerForSendPackageCheck()
{
    if ( timerForSendPackageCheck_ )
    {
        qDebug() << "startTimerForSendPackageCheck: error, timer already started";
        return;
    }

    if ( connectSettings_->maximumSendPackageWaitTime == -1 ) { return; }

    timerForSendPackageCheck_.reset( new QTimer );
    connect( timerForSendPackageCheck_.data(), &QTimer::timeout,
             this, &JQNetworkConnect::onSendPackageCheck,
             Qt::DirectConnection );

    timerForSendPackageCheck_->setSingleShot( true );
    timerForSendPackageCheck_->start( 1000 );
}

void JQNetworkConnect::onDataTransportPackageReceived(const JQNetworkPackageSharedPointer &package)
{
    if ( ( package->randomFlag() >= connectSettings_->randomFlagRangeStart ) &&
         ( package->randomFlag() < connectSettings_->randomFlagRangeEnd ) )
    {
        if ( package->packageFlag() == JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG )
        {
            this->onFileDataTransportPackageReceived( package, false );
        }

        auto it = onReceivedCallbacks_.find( package->randomFlag() );
        if ( it == onReceivedCallbacks_.end() ) { return; }

        if ( it->succeedCallback )
        {
            JQNETWORK_NULLPTR_CHECK( connectSettings_->waitReplyPackageSucceedCallback );
            connectSettings_->waitReplyPackageSucceedCallback( this, package, it->succeedCallback );
        }

        onReceivedCallbacks_.erase( it );
    }
    else
    {
        switch ( package->packageFlag() )
        {
            case JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG:
            {
                JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivedCallback );
                connectSettings_->packageReceivedCallback( this, package );
                break;
            }
            case JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG:
            {
                this->onFileDataTransportPackageReceived( package, true );
                break;
            }
            default:
            {
                qDebug() << "JQNetworkConnect::onDataTransportPackageReceived: Unknow packageFlag:" << package->packageFlag();
                break;
            }
        }
    }
}

bool JQNetworkConnect::onFileDataTransportPackageReceived(
        const JQNetworkPackageSharedPointer &package,
        const bool &callbackOnFinish
    )
{
    const auto &&itForPackage = receivedFilePackagePool_.find( package->randomFlag() );
    const auto &&packageIsCached = itForPackage != receivedFilePackagePool_.end();

    auto checkFinish = [ this, packageIsCached, callbackOnFinish ](const JQNetworkPackageSharedPointer &firstPackage, QSharedPointer< QFile > &file)->bool
    {
        const auto &&fileSize = firstPackage->fileSize();

        if ( file->pos() != fileSize )
        {
            if ( !packageIsCached )
            {
                this->receivedFilePackagePool_[ firstPackage->randomFlag() ] = { firstPackage, file };
            }

            this->sendDataRequestToRemote( firstPackage );
            return false;
        }

        const auto &&filePermissions = firstPackage->filePermissions();

        file->setPermissions( QFile::Permissions( filePermissions ) );

        file->close();
        file.clear();

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
        utimbuf timeBuf = { static_cast< time_t >( firstPackage->fileLastReadTime().toTime_t() ), static_cast< time_t >( firstPackage->fileLastModifiedTime().toTime_t() ) };
        utime( firstPackage->localFilePath().toLatin1().data(), &timeBuf );
#endif

        if ( callbackOnFinish )
        {
            JQNETWORK_NULLPTR_CHECK( this->connectSettings_->packageReceivedCallback, false );
            this->connectSettings_->packageReceivedCallback( this, firstPackage );
        }

        return true;
    };

    if ( packageIsCached )
    {
        itForPackage.value().second->write( package->payloadData() );
        itForPackage.value().second->waitForBytesWritten( connectSettings_->maximumFileWriteWaitTime );

        return checkFinish( itForPackage.value().first, itForPackage.value().second );
    }
    else
    {
        const auto &&fileName = package->fileName();
        const auto &&fileSize = package->fileSize();

        JQNETWORK_NULLPTR_CHECK( connectSettings_->filePathProvider, false );
        const auto &&localFilePath = connectSettings_->filePathProvider( this, package, fileName );

        if ( localFilePath.isEmpty() )
        {
            qDebug() << "JQNetworkConnect::onFileDataTransportPackageReceived: File path is empty, fileName:" << fileName;
            return false;
        }

        const auto &&localFileInfo = QFileInfo( localFilePath );

        if ( !localFileInfo.dir().exists() && !localFileInfo.dir().mkpath( localFileInfo.dir().absolutePath() ) )
        {
            qDebug() << "JQNetworkConnect::onFileDataTransportPackageReceived: mkpath error, filePath:" << localFilePath;
            return false;
        }

        QSharedPointer< QFile > file( new QFile( localFilePath ) );
        if ( !file->open( QIODevice::WriteOnly ) )
        {
            qDebug() << "JQNetworkConnect::onFileDataTransportPackageReceived: Open file error, filePath:" << localFilePath;
            return false;
        }

        if ( !file->resize( fileSize ) )
        {
            qDebug() << "JQNetworkConnect::onFileDataTransportPackageReceived: File resize error, filePath:" << localFilePath;
            return false;
        }

        package->setLocalFilePath( localFilePath );

        file->write( package->payloadData() );
        file->waitForBytesWritten( connectSettings_->maximumFileWriteWaitTime );

        package->clearPayloadData();

        return checkFinish( package, file );
    }
}

void JQNetworkConnect::onReadyToDelete()
{
    if ( isAbandonTcpSocket_ ) { return; }
    isAbandonTcpSocket_ = true;

    if ( !timerForConnectToHostTimeOut_ )
    {
        timerForConnectToHostTimeOut_.clear();
    }

    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );
    tcpSocket_->close();

    JQNETWORK_NULLPTR_CHECK( connectSettings_->readyToDeleteCallback );
    connectSettings_->readyToDeleteCallback( this );
}

qint32 JQNetworkConnect::nextRandomFlag()
{
    mutexForSend_.lock();

    if ( sendRandomFlagRotaryIndex_ >= connectSettings_->randomFlagRangeEnd )
    {
        sendRandomFlagRotaryIndex_ = connectSettings_->randomFlagRangeStart;
    }
    else
    {
        ++sendRandomFlagRotaryIndex_;
    }

    const auto currentRandomFlag = sendRandomFlagRotaryIndex_;

    mutexForSend_.unlock();

    return currentRandomFlag;
}

bool JQNetworkConnect::readySendPayloadData(
        const qint32 &randomFlag,
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    auto packages = JQNetworkPackage::createPayloadTransportPackages(
                targetActionFlag,
                payloadData,
                appendData,
                randomFlag,
                connectSettings_->cutPackageSize,
                this->needCompressionPayloadData( payloadData.size() )
            );
    if ( packages.isEmpty() )
    {
        qDebug() << "JQNetworkConnect::readySendPayloadData: createPackagesFromPayloadData error";
        return false;
    }

    this->readySendPackages( randomFlag, packages, succeedCallback, failCallback );

    return true;
}

bool JQNetworkConnect::readySendFileData(
        const qint32 &randomFlag,
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    if ( waitForSendFiles_.contains( randomFlag ) )
    {
        qDebug() << "JQNetworkConnect::readySendFileData: file is sending, filePath:" << fileInfo.filePath();
        return false;
    }

    if ( !fileInfo.exists() )
    {
        qDebug() << "JQNetworkConnect::readySendFileData: file not exists, filePath:" << fileInfo.filePath();
        return false;
    }

    QSharedPointer< QFile > file( new QFile( fileInfo.filePath() ) );

    if ( !file->open( QIODevice::ReadOnly ) )
    {
        qDebug() << "JQNetworkConnect::readySendFileData: file open error, filePath:" << fileInfo.filePath();
        return false;
    }

    const auto &&fileData = file->read( connectSettings_->cutPackageSize );

    if ( !file->atEnd() )
    {
        waitForSendFiles_[ randomFlag ] = file;
    }

    auto packages = QList< JQNetworkPackageSharedPointer >(
                {
                    JQNetworkPackage::createFileTransportPackage(
                        targetActionFlag,
                        fileInfo,
                        fileData,
                        appendData,
                        randomFlag,
                        this->needCompressionPayloadData( fileData.size() )
                    )
                }
            );

    this->readySendPackages( randomFlag, packages, succeedCallback, failCallback );

    return true;
}

void JQNetworkConnect::readySendPackages(
        const qint32 &randomFlag,
        QList< JQNetworkPackageSharedPointer > &packages,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    if ( this->thread() != QThread::currentThread() )
    {
        runOnConnectThreadCallback_(
                    [
                        this,
                        randomFlag,
                        packages,
                        succeedCallback,
                        failCallback
                    ]()
                    {
                        auto buf = packages;

                        this->readySendPackages( randomFlag, buf, succeedCallback, failCallback );
                    }
        );

        return;
    }

    auto firstPackage = packages.first();

    this->sendPackageToRemote( firstPackage );

    if ( succeedCallback || failCallback )
    {
        onReceivedCallbacks_[ randomFlag ] =
        {
            QDateTime::currentMSecsSinceEpoch(),
            succeedCallback,
            failCallback
        };

        if ( !timerForSendPackageCheck_ )
        {
            this->startTimerForSendPackageCheck();
        }
    }

    if ( packages.size() > 1 )
    {
        sendPayloadPackagePool_[ randomFlag ].swap( packages );
        sendPayloadPackagePool_[ randomFlag ].pop_front();
    }

    JQNETWORK_NULLPTR_CHECK( connectSettings_->packageSendingCallback );
    connectSettings_->packageSendingCallback(
                this,
                randomFlag,
                0,
                firstPackage->payloadDataOriginalCurrentSize(),
                firstPackage->payloadDataTotalSize()
            );
}

void JQNetworkConnect::sendDataRequestToRemote(const JQNetworkPackageSharedPointer &package)
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    switch ( package->packageFlag() )
    {
        case JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG:
        {
            this->sendPackageToRemote( JQNetworkPackage::createPayloadDataRequestPackage( package->randomFlag() ) );
            break;
        }
        case JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG:
        {
            this->sendPackageToRemote( JQNetworkPackage::createFileDataRequestPackage( package->randomFlag() ) );
            break;
        }
        default:
        {
            qDebug() << "JQNetworkConnect::realSendDataRequest: Unknow packageFlag:" << package->packageFlag();
            break;
        }
    }
}

void JQNetworkConnect::sendPackageToRemote(const JQNetworkPackageSharedPointer &package)
{
    const auto &&buffer = package->toByteArray();

    waitForSendBytes_ += buffer.size();
    tcpSocket_->write( buffer );
}
