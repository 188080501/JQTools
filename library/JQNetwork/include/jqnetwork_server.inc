/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_SERVER_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_SERVER_INC_

// JQNetwork lib import
#include "jqnetwork_server.h"

inline JQNetworkServerSettingsSharedPointer JQNetworkServer::serverSettings()
{
    return serverSettings_;
}

inline JQNetworkConnectPoolSettingsSharedPointer JQNetworkServer::connectPoolSettings()
{
    return connectPoolSettings_;
}

inline JQNetworkConnectSettingsSharedPointer JQNetworkServer::connectSettings()
{
    return connectSettings_;
}

inline QString JQNetworkServer::nodeMarkSummary() const
{
    return nodeMarkSummary_;
}

inline QSet< QString > JQNetworkServer::availableProcessorMethodNames() const
{
    return QSet< QString >::fromList( processorCallbacks_.keys() );
}

inline void JQNetworkServer::onConnectToHostError(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &)
{
    if ( !serverSettings_->connectToHostErrorCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->connectToHostErrorCallback
                ]()
                {
                    callback( connect );
                }
    );
}

inline void JQNetworkServer::onConnectToHostTimeout(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &)
{
    if ( !serverSettings_->connectToHostTimeoutCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->connectToHostTimeoutCallback
                ]()
                {
                    callback( connect );
                }
    );
}

inline void JQNetworkServer::onConnectToHostSucceed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &)
{
    if ( !serverSettings_->connectToHostSucceedCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->connectToHostSucceedCallback
                ]()
                {
                    callback( connect );
                }
    );
}

inline void JQNetworkServer::onRemoteHostClosed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &)
{
    if ( !serverSettings_->remoteHostClosedCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->remoteHostClosedCallback
                ]()
                {
                    callback( connect );
                }
    );
}

inline void JQNetworkServer::onReadyToDelete(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &)
{
    if ( !serverSettings_->readyToDeleteCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->readyToDeleteCallback
                ]()
                {
                    callback( connect );
                }
    );
}

inline void JQNetworkServer::onPackageSending(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    if ( !serverSettings_->packageSendingCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->packageSendingCallback,
                    randomFlag,
                    payloadCurrentIndex,
                    payloadCurrentSize,
                    payloadTotalSize
                ]()
                {
                    callback( connect, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize );
                }
    );
}

inline void JQNetworkServer::onPackageReceiving(
        const JQNetworkConnectPointer &connect,
        const JQNetworkConnectPoolPointer &,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    if ( !serverSettings_->packageReceivingCallback ) { return; }

    callbackThreadPool_->run(
                [
                    connect,
                    callback = serverSettings_->packageReceivingCallback,
                    randomFlag,
                    payloadCurrentIndex,
                    payloadCurrentSize,
                    payloadTotalSize
                ]()
                {
                    callback( connect, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize );
                }
    );
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_SERVER_INC_
