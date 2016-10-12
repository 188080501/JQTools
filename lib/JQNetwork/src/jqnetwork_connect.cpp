/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_connect.h"

// Qt lib import
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>
#include <QDateTime>

// JQNetwork lib import
#include <JQNetworkPackage>

// JQNetworkConnect
JQNetworkConnect::JQNetworkConnect():
    tcpSocket_( new QTcpSocket ),
    connectCreateTime_( QDateTime::currentMSecsSinceEpoch() )
{
    connect( tcpSocket_.data(), &QAbstractSocket::stateChanged, this, &JQNetworkConnect::onTcpSocketStateChanged, Qt::DirectConnection );
    connect( tcpSocket_.data(), &QAbstractSocket::bytesWritten, this, &JQNetworkConnect::onTcpSocketBytesWritten, Qt::DirectConnection );
    connect( tcpSocket_.data(), &QTcpSocket::readyRead, this, &JQNetworkConnect::onTcpSocketReadyRead, Qt::DirectConnection );
}

void JQNetworkConnect::createConnect(
        const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
        const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
        const JQNetworkConnectSettingsSharedPointer &connectSettings,
        const QString &hostName,
        const quint16 &port
    )
{
    JQNetworkConnectSharedPointer newConnect( new JQNetworkConnect );
    newConnect->connectSettings_ = connectSettings;
    newConnect->runOnConnectThreadCallback_ = runOnConnectThreadCallback;
    newConnect->sendRandomFlagRotaryIndex_ = connectSettings->randomFlagRangeStart - 1;

    JQNETWORK_NULLPTR_CHECK( onConnectCreatedCallback );
    onConnectCreatedCallback( newConnect );

    newConnect->startTimerForConnectToHostTimeOut();

    newConnect->tcpSocket_->connectToHost( hostName, port );
}

void JQNetworkConnect::createConnect(
        const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
        const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
        const JQNetworkConnectSettingsSharedPointer &connectSettings,
        const qintptr &socketDescriptor
    )
{
    JQNetworkConnectSharedPointer newConnect( new JQNetworkConnect );
    newConnect->connectSettings_ = connectSettings;
    newConnect->runOnConnectThreadCallback_ = runOnConnectThreadCallback;
    newConnect->sendRandomFlagRotaryIndex_ = connectSettings->randomFlagRangeStart - 1;

    JQNETWORK_NULLPTR_CHECK( onConnectCreatedCallback );
    onConnectCreatedCallback( newConnect );

    newConnect->startTimerForConnectToHostTimeOut();

    newConnect->tcpSocket_->setSocketDescriptor( socketDescriptor );
}

void JQNetworkConnect::close()
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    this->onReadyToDelete();
}

qint32 JQNetworkConnect::sendPayloadData(
        const QByteArray &payloadData,
        const std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &) > &succeedCallback,
        const std::function< void(const JQNetworkConnectPointer &connect) > &failCallback
    )
{
    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

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

    this->realSendPayloadData( currentRandomFlag, payloadData, succeedCallback, failCallback );

    return currentRandomFlag;
}

qint32 JQNetworkConnect::replyPayloadData(
        const qint32 &randomFlag,
        const QByteArray &payloadData
    )
{
    if ( isAbandonTcpSocket_ ) { return 0; }
    JQNETWORK_NULLPTR_CHECK( runOnConnectThreadCallback_, 0 );

    this->realSendPayloadData( randomFlag, payloadData, nullptr, nullptr );

    return randomFlag;
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
            auto package = JQNetworkPackage::createPackage( tcpSocketBuffer_ );

            if ( package->isCompletePackage() )
            {
                switch ( package->packageFlag() )
                {
                    case JQNETWORKPACKAGE_DATATRANSPORTPACKGEFLAG:
                    {
                        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                        connectSettings_->packageReceivingCallback( this, package->randomFlag(), 0, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                        this->onTransportPackageReceived( package );
                        break;
                    }
                    case JQNETWORKPACKAGE_DATAREQUESTPACKGEFLAG:
                    {
                        if ( !sendPackagePool_.contains( package->randomFlag() ) )
                        {
                            qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: no contains randonFlag:" << package->randomFlag();
                            break;
                        }

                        auto &packages = sendPackagePool_[ package->randomFlag() ];

                        if ( packages.isEmpty() )
                        {
                            qDebug() << "JQNetworkConnect::onTcpSocketReadyRead: packages is empty:" << package->randomFlag();
                            break;
                        }

                        auto nextPackage = packages.first();
                        packages.pop_front();

                        this->realSendPackage( nextPackage );

                        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageSendingCallback );
                        connectSettings_->packageSendingCallback(
                                    this, package->randomFlag(),
                                    nextPackage->payloadDataOriginalIndex(),
                                    nextPackage->payloadDataOriginalCurrentSize(),
                                    nextPackage->payloadDataTotalSize()
                                );

                        if ( packages.isEmpty() )
                        {
                            sendPackagePool_.remove( package->randomFlag() );
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
            else
            {
                const auto &&itForPackage = receivePackagePool_.find( package->randomFlag() );

                if ( itForPackage != receivePackagePool_.end() )
                {
                    auto payloadCurrentIndex = ( *itForPackage )->payloadDataCurrentSize();
                    JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                    connectSettings_->packageReceivingCallback( this, package->randomFlag(), payloadCurrentIndex, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                    if ( !(*itForPackage)->mixPackage( package ) )
                    {
                        receivePackagePool_.erase( itForPackage );
                        return;
                    }

                    if ( (*itForPackage)->isAbandonPackage() )
                    {
                        continue;
                    }

                    if ( (*itForPackage)->isCompletePackage() )
                    {
                        this->onTransportPackageReceived( *itForPackage );
                        receivePackagePool_.erase( itForPackage );
                    }
                    else
                    {
                        this->realSendDataRequest( package->randomFlag() );
                    }
                }
                else
                {
                    JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivingCallback );
                    connectSettings_->packageReceivingCallback( this, package->randomFlag(), 0, package->payloadDataCurrentSize(), package->payloadDataTotalSize() );

                    receivePackagePool_[ package->randomFlag() ] = package;

                    this->realSendDataRequest( package->randomFlag() );
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

void JQNetworkConnect::onTransportPackageReceived(const JQNetworkPackageSharedPointer &package)
{
    if ( ( package->randomFlag() >= connectSettings_->randomFlagRangeStart ) &&
         ( package->randomFlag() < connectSettings_->randomFlagRangeEnd ) )
    {
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
        JQNETWORK_NULLPTR_CHECK( connectSettings_->packageReceivedCallback );
        connectSettings_->packageReceivedCallback( this, package );
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

void JQNetworkConnect::realSendPackage(const JQNetworkPackageSharedPointer &package)
{
    const auto &&buffer = package->toByteArray();

    waitForSendBytes_ += buffer.size();
    tcpSocket_->write( buffer );
}

void JQNetworkConnect::realSendPayloadData(
        const qint32 &randomFlag,
        const QByteArray &payloadData,
        const std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &) > &succeedCallback,
        const std::function< void(const JQNetworkConnectPointer &connect) > &failCallback
    )
{
    bool compressionPayloadData = false;

    if ( connectSettings_->packageCompressionThresholdForConnectSucceedElapsed != -1)
    {
        if ( this->connectSucceedElapsed() >= connectSettings_->packageCompressionThresholdForConnectSucceedElapsed )
        {
            compressionPayloadData = true;
        }

        if ( ( connectSettings_->packageCompressionMinimumBytes != -1 ) &&
             ( payloadData.size() < connectSettings_->packageCompressionMinimumBytes ) )
        {
            compressionPayloadData = false;
        }
    }

    auto packages = JQNetworkPackage::createTransportPackages(
                payloadData,
                randomFlag,
                connectSettings_->cutPackageSize,
                compressionPayloadData
            );
    if ( packages.isEmpty() )
    {
        qDebug() << "JQNetworkConnect::reaySendPayloadData: createPackagesFromPayloadData error";
        return;
    }

    if ( this->thread() == QThread::currentThread() )
    {
        this->realSendPayloadData( randomFlag, packages, succeedCallback, failCallback );
    }
    else
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
                        this->realSendPayloadData( randomFlag, packages, succeedCallback, failCallback );
                    }
        );
    }
}

void JQNetworkConnect::realSendPayloadData(
        const qint32 &randomFlag,
        const QList< JQNetworkPackageSharedPointer > &packages,
        const std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &) > &succeedCallback,
        const std::function< void(const JQNetworkConnectPointer &connect) > &failCallback
    )
{
    auto firstPackage = packages.first();

    this->realSendPackage( firstPackage );

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
        sendPackagePool_[ randomFlag ] = packages;
        sendPackagePool_[ randomFlag ].pop_front();
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

void JQNetworkConnect::realSendDataRequest(const qint32 &randomFlag)
{
    if ( isAbandonTcpSocket_ ) { return; }
    JQNETWORK_NULLPTR_CHECK( tcpSocket_ );

    this->realSendPackage( JQNetworkPackage::createRequestPackage( randomFlag ) );
}
