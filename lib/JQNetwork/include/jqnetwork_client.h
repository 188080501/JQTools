/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CLIENG_H_
#define JQNETWORK_INCLUDE_JQNETWORK_CLIENG_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

struct JQNetworkClientSettings
{
    QString dutyMark;
    int maximumAutoConnectToHostWaitTime = 10 * 1000;

    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port ) > connectToHostErrorCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port ) > connectToHostTimeoutCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port ) > connectToHostSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port ) > remoteHostClosedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port ) > readyToDeleteCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageSendingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageReceivingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const QString &hostName, const quint16 &port, const JQNetworkPackageSharedPointer & ) > packageReceivedCallback = nullptr;

    int globalSocketThreadCount = JQNETWORK_ADVISE_THREADCOUNT;
    int globalProcessorThreadCount = 1;
};

class JQNetworkClient: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkClient )

public:
    JQNetworkClient(
            const JQNetworkClientSettingsSharedPointer &clientSettings,
            const JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
            const JQNetworkConnectSettingsSharedPointer connectSettings
        );

    ~JQNetworkClient();

    static JQNetworkClientSharedPointer createClient(
            const bool &fileTransferEnabled = false
        );

    inline JQNetworkClientSettingsSharedPointer clientSettings();

    inline JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings();

    inline JQNetworkConnectSettingsSharedPointer connectSettings();

    inline QString nodeMarkSummary() const;

    bool begin();

    void registerProcessor(const JQNetworkProcessorPointer &processor);

    inline QSet< QString > availableProcessorMethodNames() const;


    void createConnect(const QString &hostName, const quint16 &port);

    bool waitForCreateConnect(
            const QString &hostName,
            const quint16 &port,
            const int &maximumConnectToHostWaitTime = -1
        );

    qint32 sendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QByteArray &payloadData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 sendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QVariantMap &variantMap,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 sendFileData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendFileData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendFileData(
            const QString &hostName,
            const quint16 &port,
            const QFileInfo &fileInfo,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 waitForSendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendPayloadData(
            const QString &hostName,
            const quint16 &port,
            const QByteArray &payloadData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 waitForSendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendVariantMapData(
            const QString &hostName,
            const quint16 &port,
            const QVariantMap &variantMap,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 waitForSendFileData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendFileData(
            const QString &hostName,
            const quint16 &port,
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 waitForSendFileData(
            const QString &hostName,
            const quint16 &port,
            const QFileInfo &fileInfo,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    JQNetworkConnectPointer getConnect(const QString &hostName, const quint16 &port);

    bool containsConnect(const QString &hostName, const quint16 &port);

private:
    void onConnectToHostError(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    void onConnectToHostTimeout(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    void onConnectToHostSucceed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    void onRemoteHostClosed(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    void onReadyToDelete(const JQNetworkConnectPointer &connect, const JQNetworkConnectPoolPointer &connectPool);

    void onPackageSending(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const qint32 &randomFlag,
            const qint64 &payloadCurrentIndex,
            const qint64 &payloadCurrentSize,
            const qint64 &payloadTotalSize
        );

    void onPackageReceiving(
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

    void onWaitReplySucceedPackage(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const JQNetworkPackageSharedPointer &package,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback
        );

    void onWaitReplyPackageFail(
            const JQNetworkConnectPointer &connect,
            const JQNetworkConnectPoolPointer &connectPool,
            const JQNetworkConnectPointerFunction &failCallback
        );

private:
    // Thread pool
    static QWeakPointer< JQNetworkThreadPool > globalSocketThreadPool_;
    QSharedPointer< JQNetworkThreadPool > socketThreadPool_;
    static QWeakPointer< JQNetworkThreadPool > globalCallbackThreadPool_;
    QSharedPointer< JQNetworkThreadPool > callbackThreadPool_;

    // Settings
    JQNetworkClientSettingsSharedPointer clientSettings_;
    JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings_;
    JQNetworkConnectSettingsSharedPointer connectSettings_;

    // Client
    QMap< QThread *, JQNetworkConnectPoolSharedPointer > connectPools_;

    // Processor
    QSet< JQNetworkProcessor * > processors_;
    QMap< QString, std::function< void( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer & ) > > processorCallbacks_;

    // Other
    QString nodeMarkSummary_;
    QMutex mutex_;
    QMap< QString, QWeakPointer< QSemaphore > > waitConnectSucceedSemaphore_; // "127.0.0.1:34543" -> SemaphoreForConnect
};

// inc import
#include "jqnetwork_client.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_CLIENG_H_
