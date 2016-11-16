/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_server.h"

// Qt lib import
#include <QDebug>
#include <QTcpServer>
#include <QThread>
#include <QMetaObject>

// JQNetwork lib import
#include <JQNetworkConnectPool>
#include <JQNetworkConnect>
#include <JQNetworkProcessor>

// JQNetworkServerHelper
class JQNetworkServerHelper: public QTcpServer
{
public:
    JQNetworkServerHelper(const std::function< void(qintptr socketDescriptor) > &onIncomingConnectionCallback):
        onIncomingConnectionCallback_( onIncomingConnectionCallback )
    { }

    ~JQNetworkServerHelper() = default;

private:
    inline void incomingConnection(qintptr socketDescriptor)
    {
        onIncomingConnectionCallback_( socketDescriptor );
    }

private:
    std::function< void(qintptr socketDescriptor) > onIncomingConnectionCallback_;
};

// JQNetworkServer
QWeakPointer< JQNetworkThreadPool > JQNetworkServer::globalServerThreadPool_;
QWeakPointer< JQNetworkThreadPool > JQNetworkServer::globalSocketThreadPool_;
QWeakPointer< JQNetworkThreadPool > JQNetworkServer::globalProcessorThreadPool_;

JQNetworkServer::JQNetworkServer(
        const JQNetworkServerSettingsSharedPointer serverSettings,
        const JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
        const JQNetworkConnectSettingsSharedPointer connectSettings
    ):
    serverSettings_( serverSettings ),
    connectPoolSettings_( connectPoolSettings ),
    connectSettings_( connectSettings )
{ }

JQNetworkServer::~JQNetworkServer()
{
    if ( !this->tcpServer_ ) { return; }

    serverThreadPool_->waitRun(
                [
                    this
                ]()
                {
                    tcpServer_->close();
                    tcpServer_.clear();
                }
    );

    socketThreadPool_->waitRunEach(
                [ & ]()
                {
                    connectPools_[ QThread::currentThread() ].clear();
                }
    );
}

JQNetworkServerSharedPointer JQNetworkServer::createServer(
        const quint16 &listenPort,
        const QHostAddress &listenAddress
    )
{
    JQNetworkServerSettingsSharedPointer serverSettings( new JQNetworkServerSettings );
    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings( new JQNetworkConnectPoolSettings );
    JQNetworkConnectSettingsSharedPointer connectSettings( new JQNetworkConnectSettings );

    serverSettings->listenAddress = listenAddress;
    serverSettings->listenPort = listenPort;

    return JQNetworkServerSharedPointer( new JQNetworkServer( serverSettings, connectPoolSettings, connectSettings ) );
}

bool JQNetworkServer::begin()
{
    nodeMarkSummary_ = JQNetworkNodeMark::calculateNodeMarkSummary( serverSettings_->dutyMark );

    if ( globalServerThreadPool_ )
    {
        serverThreadPool_ = globalServerThreadPool_.toStrongRef();
    }
    else
    {
        serverThreadPool_ = QSharedPointer< JQNetworkThreadPool >( new JQNetworkThreadPool( serverSettings_->globalServerThreadCount ) );
        globalServerThreadPool_ = serverThreadPool_.toWeakRef();
    }

    if ( globalSocketThreadPool_ )
    {
        socketThreadPool_ = globalSocketThreadPool_.toStrongRef();
    }
    else
    {
        socketThreadPool_ = QSharedPointer< JQNetworkThreadPool >( new JQNetworkThreadPool( serverSettings_->globalSocketThreadCount ) );
        globalSocketThreadPool_ = socketThreadPool_.toWeakRef();
    }

    if ( globalProcessorThreadPool_ )
    {
        processorThreadPool_ = globalProcessorThreadPool_.toStrongRef();
    }
    else
    {
        processorThreadPool_ = QSharedPointer< JQNetworkThreadPool >( new JQNetworkThreadPool( serverSettings_->globalProcessorThreadCount ) );
        globalProcessorThreadPool_ = processorThreadPool_.toWeakRef();
    }

    bool listenSucceed = false;

    serverThreadPool_->waitRun(
                [
                    this,
                    &listenSucceed
                ]()
                {
                    this->tcpServer_ = QSharedPointer< QTcpServer >( new JQNetworkServerHelper( [ this ]( auto socketDescriptor )
                        { this->incomingConnection( socketDescriptor ); } ) );

                    listenSucceed = this->tcpServer_->listen(
                                this->serverSettings_->listenAddress,
                                this->serverSettings_->listenPort
                            );
                }
    );

    if ( !listenSucceed ) { return false; }

    socketThreadPool_->waitRunEach(
                [
                    this
                ]()
                {
                    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings( new JQNetworkConnectPoolSettings( *this->connectPoolSettings_ ) );
                    JQNetworkConnectSettingsSharedPointer connectSettings( new JQNetworkConnectSettings( *this->connectSettings_ ) );

                    connectPoolSettings->connectToHostErrorCallback   = [ this ](const auto &connect, const auto &connectPool)
                        { this->onConnectToHostError( connect, connectPool ); };
                    connectPoolSettings->connectToHostTimeoutCallback = [ this ](const auto &connect, const auto &connectPool)
                        { this->onConnectToHostTimeout( connect, connectPool ); };
                    connectPoolSettings->connectToHostSucceedCallback = [ this ](const auto &connect, const auto &connectPool)
                        { this->onConnectToHostSucceed( connect, connectPool ); };
                    connectPoolSettings->remoteHostClosedCallback     = [ this ](const auto &connect, const auto &connectPool)
                        { this->onRemoteHostClosed( connect, connectPool ); };
                    connectPoolSettings->readyToDeleteCallback        = [ this ](const auto &connect, const auto &connectPool)
                        { this->onReadyToDelete( connect, connectPool ); };
                    connectPoolSettings->packageSendingCallback       = [ this ](const auto &connect, const auto &connectPool, const auto &randomFlag, const auto &payloadCurrentIndex, const auto &payloadCurrentSize, const auto &payloadTotalSize)
                        { this->onPackageSending( connect, connectPool, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize ); };
                    connectPoolSettings->packageReceivingCallback     = [ this ](const auto &connect, const auto &connectPool, const auto &randomFlag, const auto &payloadCurrentIndex, const auto &payloadCurrentSize, const auto &payloadTotalSize)
                        { this->onPackageReceiving( connect, connectPool, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize ); };
                    connectPoolSettings->packageReceivedCallback      = [ this ](const auto &connect, const auto &connectPool, const auto &package)
                        { this->onPackageReceived( connect, connectPool, package ); };

                    connectSettings->randomFlagRangeStart = 1000000000;
                    connectSettings->randomFlagRangeEnd = 1999999999;

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

void JQNetworkServer::registerProcessor(const JQNetworkProcessorPointer &processor)
{
    const auto &&availableSlots = processor->availableSlots();

    for ( const auto &currentSlot: availableSlots )
    {
        if ( processor_.contains( currentSlot ) )
        {
            qDebug() << "JQNetworkServer::registerProcessor: double register:" << currentSlot;
            continue;
        }

        const auto &&callback = [ processor ](const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
        {
            if ( !processor )
            {
                qDebug() << "JQNetworkServer::registerProcessor: processor is null";
                return;
            }

            processor->handlePackage( connect, package );
        };
        processor_[ currentSlot ] = callback;
    }
}

void JQNetworkServer::incomingConnection(const qintptr &socketDescriptor)
{
    const auto &&rotaryIndex = socketThreadPool_->nextRotaryIndex();

    auto runOnConnectThreadCallback =
        [
            this,
            rotaryIndex
        ](const std::function< void() > &callback)
        {
            this->socketThreadPool_->run( callback, rotaryIndex );
        };

    socketThreadPool_->run(
                [
                    this,
                    runOnConnectThreadCallback,
                    socketDescriptor
                ]()
                {
                    this->connectPools_[ QThread::currentThread() ]->createConnect(
                        runOnConnectThreadCallback,
                        socketDescriptor
                    );
                },
                rotaryIndex
    );
}

void JQNetworkServer::onPackageReceived(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &,
        const JQNetworkPackageSharedPointer &package
    )
{
    JQNETWORK_NULLPTR_CHECK( serverSettings_->packageReceivedCallback );

    processorThreadPool_->run(
                [
                    connect,
                    package,
                    callback = serverSettings_->packageReceivedCallback
                ]()
                {
                    callback( connect, package );
                }
    );
}
