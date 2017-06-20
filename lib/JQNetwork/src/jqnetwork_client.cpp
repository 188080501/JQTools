/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_client.h"

// Qt lib import
#include <QDebug>
#include <QThread>
#include <QSemaphore>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

// JQNetwork lib import
#include <JQNetworkConnectPool>
#include <JQNetworkConnect>
#include <JQNetworkPackage>
#include <JQNetworkProcessor>

using namespace std;
using namespace std::placeholders;

QWeakPointer< JQNetworkThreadPool > JQNetworkClient::globalSocketThreadPool_;
QWeakPointer< JQNetworkThreadPool > JQNetworkClient::globalCallbackThreadPool_;

JQNetworkClient::JQNetworkClient(
        const JQNetworkClientSettingsSharedPointer &clientSettings,
        const JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
        const JQNetworkConnectSettingsSharedPointer connectSettings
    ):
    clientSettings_( clientSettings ),
    connectPoolSettings_( connectPoolSettings ),
    connectSettings_( connectSettings )
{ }

JQNetworkClient::~JQNetworkClient()
{
    if ( !socketThreadPool_ ) { return; }

    socketThreadPool_->waitRunEach(
                [ this ]()
                {
                    this->connectPools_[ QThread::currentThread() ].clear();
                }
    );
}

JQNetworkClientSharedPointer JQNetworkClient::createClient(
        const bool &fileTransferEnabled
    )
{
    JQNetworkClientSettingsSharedPointer clientSettings( new JQNetworkClientSettings );
    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings( new JQNetworkConnectPoolSettings );
    JQNetworkConnectSettingsSharedPointer connectSettings( new JQNetworkConnectSettings );

    if ( fileTransferEnabled )
    {
        connectSettings->fileTransferEnabled = true;
        connectSettings->setFilePathProviderToDefaultDir();
    }

    return JQNetworkClientSharedPointer( new JQNetworkClient( clientSettings, connectPoolSettings, connectSettings ) );
}

bool JQNetworkClient::begin()
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::begin", false );

    nodeMarkSummary_ = JQNetworkNodeMark::calculateNodeMarkSummary( clientSettings_->dutyMark );

    if ( globalSocketThreadPool_ )
    {
        socketThreadPool_ = globalSocketThreadPool_.toStrongRef();
    }
    else
    {
        socketThreadPool_ = QSharedPointer< JQNetworkThreadPool >( new JQNetworkThreadPool( clientSettings_->globalSocketThreadCount ) );
        globalSocketThreadPool_ = socketThreadPool_.toWeakRef();
    }

    if ( globalCallbackThreadPool_ )
    {
        callbackThreadPool_ = globalCallbackThreadPool_.toStrongRef();
    }
    else
    {
        callbackThreadPool_ = QSharedPointer< JQNetworkThreadPool >( new JQNetworkThreadPool( clientSettings_->globalCallbackThreadCount ) );
        globalCallbackThreadPool_ = callbackThreadPool_.toWeakRef();
    }

    if ( !processors_.isEmpty() )
    {
        QSet< QThread * > receivedPossibleThreads;

        callbackThreadPool_->waitRunEach( [ &receivedPossibleThreads ]()
        {
            receivedPossibleThreads.insert( QThread::currentThread() );
        } );

        for ( const auto &processor: processors_ )
        {
            processor->setReceivedPossibleThreads( receivedPossibleThreads );
        }
    }

    socketThreadPool_->waitRunEach(
                [
                    this
                ]()
                {
                    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings(
                                new JQNetworkConnectPoolSettings( *this->connectPoolSettings_ )
                            );
                    JQNetworkConnectSettingsSharedPointer connectSettings(
                                new JQNetworkConnectSettings( *this->connectSettings_ )
                            );

                    connectPoolSettings->connectToHostErrorCallback         = bind( &JQNetworkClient::onConnectToHostError, this, _1, _2 );
                    connectPoolSettings->connectToHostTimeoutCallback       = bind( &JQNetworkClient::onConnectToHostTimeout, this, _1, _2 );
                    connectPoolSettings->connectToHostSucceedCallback       = bind( &JQNetworkClient::onConnectToHostSucceed, this, _1, _2 );
                    connectPoolSettings->remoteHostClosedCallback           = bind( &JQNetworkClient::onRemoteHostClosed, this, _1, _2 );
                    connectPoolSettings->readyToDeleteCallback              = bind( &JQNetworkClient::onReadyToDelete, this, _1, _2 );
                    connectPoolSettings->packageSendingCallback             = bind( &JQNetworkClient::onPackageSending, this, _1, _2, _3, _4, _5, _6 );
                    connectPoolSettings->packageReceivingCallback           = bind( &JQNetworkClient::onPackageReceiving, this, _1, _2, _3, _4, _5, _6 );
                    connectPoolSettings->packageReceivedCallback            = bind( &JQNetworkClient::onPackageReceived, this, _1, _2, _3 );
                    connectPoolSettings->waitReplyPackageSucceedCallback    = bind( &JQNetworkClient::onWaitReplySucceedPackage, this, _1, _2, _3, _4 );
                    connectPoolSettings->waitReplyPackageFailCallback       = bind( &JQNetworkClient::onWaitReplyPackageFail, this, _1, _2, _3 );

                    connectSettings->randomFlagRangeStart = 1;
                    connectSettings->randomFlagRangeEnd = 999999999;

                    connectPools_[ QThread::currentThread() ] = JQNetworkConnectPoolSharedPointer(
                                new JQNetworkConnectPool(
                                    connectPoolSettings,
                                    connectSettings
                                )
                            );
                }
    );

    return true;
}

void JQNetworkClient::registerProcessor(const JQNetworkProcessorPointer &processor)
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::registerProcessor" );

    if ( !connectPools_.isEmpty() )
    {
        qDebug() << "JQNetworkClient::registerProcessor: please use registerProcessor befor begin()";
        return;
    }

    const auto &&availableSlots = processor->availableSlots();
    auto counter = 0;

    for ( const auto &currentSlot: availableSlots )
    {
        if ( processorCallbacks_.contains( currentSlot ) )
        {
            qDebug() << "JQNetworkClient::registerProcessor: double register:" << currentSlot;
            continue;
        }

        const auto &&callback = [ processor ](const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
        {
            if ( !processor )
            {
                qDebug() << "JQNetworkClient::registerProcessor: processor is null";
                return;
            }

            processor->handlePackage( connect, package );
        };

        processorCallbacks_[ currentSlot ] = callback;
        ++counter;
    }

    processors_.insert( processor );

    if ( !counter )
    {
        qDebug() << "JQNetworkClient::registerProcessor: no available slots in processor:" << processor->metaObject()->className();
    }
}

void JQNetworkClient::createConnect(const QString &hostName, const quint16 &port)
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::createConnect" );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::createConnect: this client need to begin:" << this;
        return;
    }

    const auto &&rotaryIndex = socketThreadPool_->nextRotaryIndex();

    auto runOnConnectThreadCallback =
            [
                this,
                rotaryIndex
            ](const std::function< void() > &runCallback)
            {
                this->socketThreadPool_->run( runCallback, rotaryIndex );
            };

    socketThreadPool_->run(
                [
                    this,
                    runOnConnectThreadCallback,
                    hostName,
                    port
                ]()
                {
                    this->connectPools_[ QThread::currentThread() ]->createConnect(
                        runOnConnectThreadCallback,
                        hostName,
                        port
                    );
                },
                rotaryIndex
    );
}

bool JQNetworkClient::waitForCreateConnect(
        const QString &hostName,
        const quint16 &port,
        const int &maximumConnectToHostWaitTime
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::waitForCreateConnect", false );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::waitForCreateConnect: this client need to begin:" << this;
        return false;
    }

    if ( this->containsConnect( hostName, port ) )
    {
        return true;
    }

    QSharedPointer< QSemaphore > semaphore( new QSemaphore );
    const auto &&hostKey = QString( "%1:%2" ).arg( hostName, QString::number( port ) );

    mutex_.lock();

    waitConnectSucceedSemaphore_[ hostKey ] = semaphore.toWeakRef();
    this->createConnect( hostName, port );

    mutex_.unlock();

    const auto &&acquireSucceed = semaphore->tryAcquire(
                1,
                ( maximumConnectToHostWaitTime == -1 ) ? ( connectSettings_->maximumConnectToHostWaitTime ) : ( maximumConnectToHostWaitTime )
            );

    mutex_.lock();

    waitConnectSucceedSemaphore_.remove( hostKey );

    mutex_.unlock();

    return acquireSucceed;
}

qint32 JQNetworkClient::sendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::sendPayloadData", 0 );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::sendPayloadData: this client need to begin:" << this;

        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    auto connect = this->getConnect( hostName, port );

    if ( !connect )
    {
        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    return connect->sendPayloadData(
                targetActionFlag,
                payloadData,
                appendData,
                succeedCallback,
                failCallback
            );
}

qint32 JQNetworkClient::sendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::sendVariantMapData", 0 );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::sendVariantMapData: this client need to begin:" << this;

        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    return this->sendPayloadData(
                hostName,
                port,
                targetActionFlag,
                QJsonDocument( QJsonObject::fromVariantMap( variantMap ) ).toJson( QJsonDocument::Compact ),
                appendData,
                succeedCallback,
                failCallback
            );
}

qint32 JQNetworkClient::sendFileData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::sendFileData", 0 );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::sendFileData: this client need to begin:" << this;

        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    auto connect = this->getConnect( hostName, port );

    if ( !connect )
    {
        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    return connect->sendFileData(
                targetActionFlag,
                fileInfo,
                appendData,
                succeedCallback,
                failCallback
            );
}

qint32 JQNetworkClient::waitForSendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::waitForSendPayloadData", 0 );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::waitForSendPayloadData: this client need to begin:" << this;

        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    QSemaphore semaphore;

    const auto &&sendReply = this->sendPayloadData(
                hostName,
                port,
                targetActionFlag,
                payloadData,
                appendData,
                [
                    &semaphore,
                    succeedCallback
                ]
                (const auto &connect, const auto &package)
                {
                    if ( succeedCallback )
                    {
                        succeedCallback( connect, package );
                    }
                    semaphore.release( 1 );
                },
                [
                    &semaphore,
                    failCallback
                ]
                (const auto &connect)
                {
                    if ( failCallback )
                    {
                        failCallback( connect );
                    }
                    semaphore.release( 1 );
                }
            );

    semaphore.acquire();

    return sendReply;
}

qint32 JQNetworkClient::waitForSendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::waitForSendVariantMapData", 0 );

    return this->waitForSendPayloadData(
                hostName,
                port,
                targetActionFlag,
                QJsonDocument( QJsonObject::fromVariantMap( variantMap ) ).toJson( QJsonDocument::Compact ),
                appendData,
                succeedCallback,
                failCallback
            );
}

qint32 JQNetworkClient::waitForSendFileData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QVariantMap &appendData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::waitForSendFileData", 0 );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::waitForSendFileData: this client need to begin:" << this;

        if ( failCallback )
        {
            failCallback( nullptr );
        }
        return 0;
    }

    QSemaphore semaphore;

    const auto &&sendReply = this->sendFileData(
                hostName,
                port,
                targetActionFlag,
                fileInfo,
                appendData,
                [
                    &semaphore,
                    succeedCallback
                ]
                (const auto &connect, const auto &package)
                {
                    if ( succeedCallback )
                    {
                        succeedCallback( connect, package );
                    }
                    semaphore.release( 1 );
                },
                [
                    &semaphore,
                    failCallback
                ]
                (const auto &connect)
                {
                    if ( failCallback )
                    {
                        failCallback( connect );
                    }
                    semaphore.release( 1 );
                }
            );

    semaphore.acquire();

    return sendReply;
}

JQNetworkConnectPointer JQNetworkClient::getConnect(const QString &hostName, const quint16 &port)
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::getConnect", nullptr );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::getConnect: this client need to begin:" << this;
        return { };
    }

    for ( const auto &connectPool: this->connectPools_ )
    {
        auto connect = connectPool->getConnectByHostAndPort( hostName, port );

        if ( !connect ) { continue; }

        return connect;
    }

    const auto &&autoConnectSucceed = this->waitForCreateConnect( hostName, port, clientSettings_->maximumAutoConnectToHostWaitTime );

    if ( !autoConnectSucceed ) { return { }; }

    for ( const auto &connectPool: this->connectPools_ )
    {
        auto connect = connectPool->getConnectByHostAndPort( hostName, port );

        if ( !connect ) { continue; }

        return connect;
    }

    return { };
}

bool JQNetworkClient::containsConnect(const QString &hostName, const quint16 &port)
{
    JQNETWORK_THISNULL_CHECK( "JQNetworkClient::containsConnect", false );

    if ( !socketThreadPool_ )
    {
        qDebug() << "JQNetworkClient::containsConnect: this client need to begin:" << this;
        return { };
    }

    for ( const auto &connectPool: this->connectPools_ )
    {
        auto connect = connectPool->getConnectByHostAndPort( hostName, port );

        if ( !connect ) { continue; }

        return true;
    }

    return false;
}

void JQNetworkClient::onConnectToHostError(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool)
{
    if ( !clientSettings_->connectToHostErrorCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onConnectToHostError: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second
                ]()
                {
                    this->clientSettings_->connectToHostErrorCallback( connect, hostName, port );
                }
    );
}

void JQNetworkClient::onConnectToHostTimeout(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool)
{
    if ( !clientSettings_->connectToHostTimeoutCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onConnectToHostTimeout: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second
                ]()
                {
                    this->clientSettings_->connectToHostTimeoutCallback( connect, hostName, port );
                }
    );
}

void JQNetworkClient::onConnectToHostSucceed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool)
{
    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onConnectToHostSucceed: connect error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second
                ]()
                {
                    const auto &&hostKey = QString( "%1:%2" ).arg( hostName, QString::number( port ) );

                    this->mutex_.lock();

                    {
                        auto it = this->waitConnectSucceedSemaphore_.find( hostKey );
                        if ( it != this->waitConnectSucceedSemaphore_.end() )
                        {
                            if ( it->data() )
                            {
                                it->data()->release( 1 );
                            }
                            else
                            {
                                qDebug() << "JQNetworkClient::onConnectToHostSucceed: semaphore error";
                            }
                        }
                    }

                    this->mutex_.unlock();

                    if ( !this->clientSettings_->connectToHostSucceedCallback ) { return; }
                    this->clientSettings_->connectToHostSucceedCallback( connect, hostName, port );
                }
            );
}

void JQNetworkClient::onRemoteHostClosed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool)
{
    if ( !clientSettings_->remoteHostClosedCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onRemoteHostClosed: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second
                ]()
                {
                    this->clientSettings_->remoteHostClosedCallback( connect, hostName, port );
                }
    );
}

void JQNetworkClient::onReadyToDelete(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool)
{
    if ( !clientSettings_->readyToDeleteCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onReadyToDelete: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second
                ]()
                {
                    this->clientSettings_->readyToDeleteCallback( connect, hostName, port );
                }
    );
}

void JQNetworkClient::onPackageSending(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &connectPool,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    if ( !clientSettings_->packageSendingCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onPackageSending: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second,
                    randomFlag,
                    payloadCurrentIndex,
                    payloadCurrentSize,
                    payloadTotalSize
                ]()
                {
                    this->clientSettings_->packageSendingCallback(
                        connect,
                        hostName,
                        port,
                        randomFlag,
                        payloadCurrentIndex,
                        payloadCurrentSize,
                        payloadTotalSize
                    );
                }
    );
}

void JQNetworkClient::onPackageReceiving(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &connectPool,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    if ( !clientSettings_->packageReceivingCallback ) { return; }

    const auto &&reply = connectPool->getHostAndPortByConnect( connect );

    if ( reply.first.isEmpty() || !reply.second )
    {
        qDebug() << "JQNetworkClient::onPackageReceiving: error";
        return;
    }

    callbackThreadPool_->run(
                [
                    this,
                    connect,
                    hostName = reply.first,
                    port = reply.second,
                    randomFlag,
                    payloadCurrentIndex,
                    payloadCurrentSize,
                    payloadTotalSize
                ]()
                {
                    this->clientSettings_->packageReceivingCallback(
                        connect,
                        hostName,
                        port,
                        randomFlag,
                        payloadCurrentIndex,
                        payloadCurrentSize,
                        payloadTotalSize
                    );
                }
    );
}

void JQNetworkClient::onPackageReceived(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &connectPool,
        const JQNetworkPackageSharedPointer &package
    )
{
    if ( processorCallbacks_.isEmpty() )
    {
        if ( !clientSettings_->packageReceivedCallback ) { return; }

        const auto &&reply = connectPool->getHostAndPortByConnect( connect );

        if ( reply.first.isEmpty() || !reply.second )
        {
            qDebug() << "JQNetworkClient::onPackageReceived: error";
            return;
        }

        callbackThreadPool_->run(
                    [
                        this,
                        connect,
                        hostName = reply.first,
                        port = reply.second,
                        package
                    ]()
                    {
                        this->clientSettings_->packageReceivedCallback( connect, hostName, port, package );
                    }
        );
    }
    else
    {
        if ( package->targetActionFlag().isEmpty() )
        {
            qDebug() << "JQNetworkClient::onPackageReceived: processor is enable, but package targetActionFlag is empty";
            return;
        }

        const auto &&it = processorCallbacks_.find( package->targetActionFlag() );
        if ( it == processorCallbacks_.end() )
        {
            qDebug() << "JQNetworkClient::onPackageReceived: processor is enable, but package targetActionFlag not match:" << package->targetActionFlag();
            return;
        }

        callbackThreadPool_->run(
                    [
                        connect,
                        package,
                        callback = *it
                    ]()
                    {
                        callback( connect, package );
                    }
        );
    }
}

void JQNetworkClient::onWaitReplySucceedPackage(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &,
        const JQNetworkPackageSharedPointer &package,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback
    )
{
    callbackThreadPool_->run(
                [
                    connect,
                    package,
                    succeedCallback
                ]()
                {
                    succeedCallback( connect, package );
                }
    );
}

void JQNetworkClient::onWaitReplyPackageFail(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    callbackThreadPool_->run(
                [
                    connect,
                    failCallback
                ]()
                {
                    failCallback( connect );
                }
    );
}
