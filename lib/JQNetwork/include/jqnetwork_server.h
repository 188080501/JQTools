/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_SERVER_H_
#define JQNETWORK_INCLUDE_JQNETWORK_SERVER_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

struct JQNetworkServerSettings
{
    QString dutyMark;

    QHostAddress listenAddress = QHostAddress::Any;
    quint16 listenPort = 0;

    std::function< void( const JQNetworkConnectPointer & ) > connectToHostErrorCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > connectToHostTimeoutCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > connectToHostSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > remoteHostClosedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > readyToDeleteCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageSendingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageReceivingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer & ) > packageReceivedCallback = nullptr;

    int globalServerThreadCount = 1;
    int globalSocketThreadCount = JQNETWORK_ADVISE_THREADCOUNT;
    int globalProcessorThreadCount = JQNETWORK_ADVISE_THREADCOUNT;
};

class JQNetworkServer: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkServer )

public:
    JQNetworkServer(
            const JQNetworkServerSettingsSharedPointer serverSettings,
            const JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
            const JQNetworkConnectSettingsSharedPointer connectSettings
        );

    ~JQNetworkServer();

    static JQNetworkServerSharedPointer createServer(
            const quint16 &listenPort,
            const QHostAddress &listenAddress = QHostAddress::Any,
            const bool &fileTransferEnabled = false
        );

    inline JQNetworkServerSettingsSharedPointer serverSettings();

    inline JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings();

    inline JQNetworkConnectSettingsSharedPointer connectSettings();

    inline QString nodeMarkSummary() const;

    bool begin();

    void registerProcessor(const JQNetworkProcessorPointer &processor);

    inline QSet< QString > availableProcessorMethodNames() const;

private:
    void incomingConnection(const qintptr &socketDescriptor);

    inline void onConnectToHostError(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    inline void onConnectToHostTimeout(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    inline void onConnectToHostSucceed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    inline void onRemoteHostClosed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    inline void onReadyToDelete(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    inline void onPackageSending(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const qint32 &randomFlag,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        );

    inline void onPackageReceiving(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const qint32 &randomFlag,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        );

    void onPackageReceived(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const JQNetworkPackageSharedPointer &package
        );

private:
    // Thread pool
    static QWeakPointer< JQNetworkThreadPool > globalServerThreadPool_;
    QSharedPointer< JQNetworkThreadPool > serverThreadPool_;
    static QWeakPointer< JQNetworkThreadPool > globalSocketThreadPool_;
    QSharedPointer< JQNetworkThreadPool > socketThreadPool_;
    static QWeakPointer< JQNetworkThreadPool > globalCallbackThreadPool_;
    QSharedPointer< JQNetworkThreadPool > callbackThreadPool_;

    // Settings
    JQNetworkServerSettingsSharedPointer serverSettings_;
    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings_;
    JQNetworkConnectSettingsSharedPointer connectSettings_;

    // Server
    QSharedPointer< QTcpServer > tcpServer_;
    QMap< QThread *, JQNetworkConnectPoolSharedPointer > connectPools_;

    // Processor
    QSet< JQNetworkProcessor * > processors_;
    QMap< QString, std::function< void( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer & ) > > processorCallbacks_;

    // Other
    QString nodeMarkSummary_;
};

// inc import
#include "jqnetwork_server.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_SERVER_H_
