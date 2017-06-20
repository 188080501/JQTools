/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_H_
#define JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

struct JQNetworkConnectPoolSettings
{
    bool autoReconnect = true;
    int reconnectIntervalTime = 15 * 1000;

    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer & ) > connectToHostErrorCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer & ) > connectToHostTimeoutCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer & ) > connectToHostSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer & ) > remoteHostClosedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer & ) > readyToDeleteCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageSendingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageReceivingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer &, const JQNetworkPackageSharedPointer & ) > packageReceivedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer &, const JQNetworkPackageSharedPointer &, const JQNetworkConnectPointerAndPackageSharedPointerFunction & ) > waitReplyPackageSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkConnectPoolPointer &, const JQNetworkConnectPointerFunction & ) > waitReplyPackageFailCallback = nullptr;
};

class JQNetworkConnectPool: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkConnectPool )

public:
    JQNetworkConnectPool(
            JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
            JQNetworkConnectSettingsSharedPointer connectSettings
        );

    ~JQNetworkConnectPool();

    void createConnect(
            const std::function< void( std::function< void() > ) > runOnConnectThreadCallback,
            const QString &hostName,
            const quint16 &port
        );

    void createConnect(
            const std::function< void( std::function< void() > ) > runOnConnectThreadCallback,
            const qintptr &socketDescriptor
        );

    inline bool containsConnect(const QString &hostName, const quint16 &port);

    inline bool containsConnect(const qintptr &socketDescriptor);

    QPair< QString, quint16 > getHostAndPortByConnect(const JQNetworkConnectPointer &connect);

    qintptr getSocketDescriptorByConnect(const JQNetworkConnectPointer &connect);

    JQNetworkConnectPointer getConnectByHostAndPort(const QString &hostName, const quint16 &port);

    JQNetworkConnectPointer getConnectBySocketDescriptor(const qintptr &socketDescriptor);

private:
    inline void onConnectToHostError(const JQNetworkConnectPointer &connectz);

    inline void onConnectToHostTimeout(const JQNetworkConnectPointer &connect);

    void onConnectToHostSucceed(const JQNetworkConnectPointer &connect);

    inline void onRemoteHostClosed(const JQNetworkConnectPointer &connect);

    void onReadyToDelete(const JQNetworkConnectPointer &connect);

    inline void onPackageSending(
            const JQNetworkConnectPointer &connect,
            const qint32 &randomFlag,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        );

    inline void onPackageReceiving(
            const JQNetworkConnectPointer &connect,
            const qint32 &randomFlag,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        );

    inline void onPackageReceived(
            const JQNetworkConnectPointer &connect,
            const JQNetworkPackageSharedPointer &package
         );

    inline void onWaitReplyPackageSucceed(
            const JQNetworkConnectPointer &connect,
            const JQNetworkPackageSharedPointer &package,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback
        );

    inline void onWaitReplyPackageFail(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPointerFunction &failCallback
        );

private:
    // Settings
    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings_;
    JQNetworkConnectSettingsSharedPointer connectSettings_;

    // Connect
    QMap< JQNetworkConnect *, JQNetworkConnectSharedPointer > connectForConnecting_;
    QMap< JQNetworkConnect *, JQNetworkConnectSharedPointer > connectForConnected_;

    QMap< QString, JQNetworkConnectPointer > bimapForHostAndPort1; // "127.0.0.1:34543" -> Connect
    QMap< JQNetworkConnect *, QString > bimapForHostAndPort2; // Connect -> "127.0.0.1:34543"
    QMap< qintptr, JQNetworkConnectPointer > bimapForSocketDescriptor1; // socketDescriptor -> Connect
    QMap< JQNetworkConnect *, qintptr > bimapForSocketDescriptor2; // Connect -> socketDescriptor

    // Other
    QMutex mutex_;
};

// inc import
#include "jqnetwork_connectpool.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECTPOOL_H_
