/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_INC
#define JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_INC

// JQNetwork lib import
#include "jqnetwork_connectpool.h"

inline bool JQNetworkConnectPool::containsConnect(const QString &hostName, const quint16 &port)
{
    mutex_.lock();

    auto contains = bimapForHostAndPort1.contains( QString( "%1:%2" ).arg( hostName ).arg( port ) );

    mutex_.unlock();

    return contains;
}

inline bool JQNetworkConnectPool::containsConnect(const qintptr &socketDescriptor)
{
    mutex_.lock();

    auto contains = bimapForSocketDescriptor1.contains( socketDescriptor );

    mutex_.unlock();

    return contains;
}

inline void JQNetworkConnectPool::onConnectToHostError(const JQNetworkConnectPointer &connect)
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->connectToHostErrorCallback );
    connectPoolSettings_->connectToHostErrorCallback( connect, this );
}

inline void JQNetworkConnectPool::onConnectToHostTimeout(const JQNetworkConnectPointer &connect)
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->connectToHostTimeoutCallback );
    connectPoolSettings_->connectToHostTimeoutCallback( connect, this );
}

inline void JQNetworkConnectPool::onRemoteHostClosed(const JQNetworkConnectPointer &connect)
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->remoteHostClosedCallback );
    connectPoolSettings_->remoteHostClosedCallback( connect, this );
}

inline void JQNetworkConnectPool::onPackageSending(
        const JQNetworkConnectPointer &connect,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->packageSendingCallback );
    connectPoolSettings_->packageSendingCallback( connect, this, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize );
}

inline void JQNetworkConnectPool::onPackageReceiving(
        const JQNetworkConnectPointer &connect,
        const qint32 &randomFlag,
        const qint64 &payloadCurrentIndex,
        const qint64 &payloadCurrentSize,
        const qint64 &payloadTotalSize
    )
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->packageReceivingCallback );
    connectPoolSettings_->packageReceivingCallback( connect, this, randomFlag, payloadCurrentIndex, payloadCurrentSize, payloadTotalSize );
}

inline void JQNetworkConnectPool::onPackageReceived(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->packageReceivedCallback );
    connectPoolSettings_->packageReceivedCallback( connect, this, package );
}

inline void JQNetworkConnectPool::onWaitReplySucceedPackage(
        const JQNetworkConnectPointer &connect,
        const JQNetworkPackageSharedPointer &package,
        const std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &) > &callback
    )
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->waitReplyPackageSucceedCallback );
    connectPoolSettings_->waitReplyPackageSucceedCallback( connect, this, package, callback );
}

inline void JQNetworkConnectPool::onWaitReplyPackageFail(
        const JQNetworkConnectPointer &connect,
        const std::function< void(const JQNetworkConnectPointer &connect) > &callback
    )
{
    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->waitReplyPackageFailCallback );
    connectPoolSettings_->waitReplyPackageFailCallback( connect, this, callback );
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_INC
