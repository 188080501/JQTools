/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CONNECT_H_
#define JQNETWORK_INCLUDE_JQNETWORK_CONNECT_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

struct JQNetworkConnectSettings
{
    bool longConnection = true;
    bool autoMaintainLongConnection = false;

    int streamFormat = -1;
    qint64 cutPackageSize = JQNETWORKPACKAGE_ADVISE_CUTPACKAGESIZE;
    qint64 packageCompressionMinimumBytes = 1024;
    int packageCompressionThresholdForConnectSucceedElapsed = 500;
    qint64 maximumSendForTotalByteCount = -1;
    qint64 maximumSendPackageByteCount = -1;
    int maximumSendSpeed = -1; // Byte/s
    qint64 maximumReceiveForTotalByteCount = -1;
    qint64 maximumReceivePackageByteCount = -1;
    int maximumReceiveSpeed = -1; // Byte/s
    bool fileTransferEnabled = false;

    qint32 randomFlagRangeStart = -1;
    qint32 randomFlagRangeEnd = -1;

    int maximumConnectToHostWaitTime = 15 * 1000;
    int maximumSendPackageWaitTime = 30 * 1000;
    int maximumReceivePackageWaitTime = 30 * 1000;
    int maximumNoCommunicationTime = 30 * 1000;
    int maximumFileWriteWaitTime = 30 * 1000;
    int maximumConnectionTime = -1;

    std::function< void( const JQNetworkConnectPointer & ) > connectToHostErrorCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > connectToHostTimeoutCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > connectToHostSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > remoteHostClosedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer & ) > readyToDeleteCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageSendingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const qint32 &, const qint64 &, const qint64 &, const qint64 & ) > packageReceivingCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer & ) > packageReceivedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer &, const JQNetworkConnectPointerAndPackageSharedPointerFunction & ) > waitReplyPackageSucceedCallback = nullptr;
    std::function< void( const JQNetworkConnectPointer &, const std::function< void(const JQNetworkConnectPointer &connect ) > & ) > waitReplyPackageFailCallback = nullptr;
    std::function< QString( const JQNetworkConnectPointer &, const JQNetworkPackageSharedPointer &, const QString & ) > filePathProvider = nullptr;

    void setFilePathProviderToDefaultDir();

    void setFilePathProviderToDir(const QDir &dir);
};

class JQNetworkConnect: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkConnect )

private:
    struct ReceivedCallbackPackage
    {
        qint64 sendTime;
        JQNetworkConnectPointerAndPackageSharedPointerFunction succeedCallback;
        JQNetworkConnectPointerFunction failCallback;
    };

private:
    JQNetworkConnect(const JQNetworkConnectSettingsSharedPointer &connectSettings);

public:
    ~JQNetworkConnect() = default;

    static void createConnect(
            const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
            const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
            const JQNetworkConnectSettingsSharedPointer &connectSettings,
            const QString &hostName,
            const quint16 &port
        );

    static void createConnect(
            const std::function< void(const JQNetworkConnectSharedPointer &) > &onConnectCreatedCallback,
            const std::function< void( std::function< void() > ) > &runOnConnectThreadCallback,
            const JQNetworkConnectSettingsSharedPointer &connectSettings,
            const qintptr &socketDescriptor
        );

    inline bool onceConnectSucceed() const;

    inline bool isAbandonTcpSocket() const;

    inline qint64 connectCreateTime() const;

    inline qint64 connectSucceedTime() const;

    inline qint64 waitForSendBytes() const;

    inline qint64 alreadyWrittenBytes() const;

    inline qint64 connectSucceedElapsed() const;

    void close();

    qint32 sendPayloadData(
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendPayloadData(
            const QByteArray &payloadData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 sendVariantMapData(
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendVariantMapData(
            const QVariantMap &variantMap,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 sendFileData(
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    inline qint32 sendFileData(
            const QFileInfo &fileInfo,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback = nullptr,
            const JQNetworkConnectPointerFunction &failCallback = nullptr
        );

    qint32 replyPayloadData(
            const qint32 &receivedPackageRandomFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData = QVariantMap()
        );

    qint32 replyVariantMapData(
            const qint32 &receivedPackageRandomFlag,
            const QVariantMap &variantMap,
            const QVariantMap &appendData = QVariantMap()
        );

    qint32 replyFile(
            const qint32 &receivedPackageRandomFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData = QVariantMap()
        );

    bool putPayloadData(
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData = QVariantMap()
        );

    inline bool putPayloadData(
            const QByteArray &payloadData,
            const QVariantMap &appendData = QVariantMap()
        );

    bool putVariantMapData(
            const QString &targetActionFlag,
            const QVariantMap &variantMap,
            const QVariantMap &appendData = QVariantMap()
        );

    inline bool putVariantMapData(
            const QVariantMap &variantMap,
            const QVariantMap &appendData = QVariantMap()
        );

    bool putFile(
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData = QVariantMap()
        );

    inline bool putFile(
            const QFileInfo &fileInfo,
            const QVariantMap &appendData = QVariantMap()
        );

private Q_SLOTS:
    void onTcpSocketStateChanged();

    void onTcpSocketBytesWritten(const qint64 &bytes);

    void onTcpSocketReadyRead();

    void onTcpSocketConnectToHostTimeOut();

    void onSendPackageCheck();

private:
    void startTimerForConnectToHostTimeOut();

    void startTimerForSendPackageCheck();

    void onDataTransportPackageReceived(const JQNetworkPackageSharedPointer &package);

    bool onFileDataTransportPackageReceived(
            const JQNetworkPackageSharedPointer &package,
            const bool &callbackOnFinish
        );

    void onReadyToDelete();

    qint32 nextRandomFlag();

    inline bool needCompressionPayloadData(const int &dataSize);

    bool readySendPayloadData(
            const qint32 &randomFlag,
            const QString &targetActionFlag,
            const QByteArray &payloadData,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
            const JQNetworkConnectPointerFunction &failCallback
        );

    bool readySendFileData(
            const qint32 &randomFlag,
            const QString &targetActionFlag,
            const QFileInfo &fileInfo,
            const QVariantMap &appendData,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
            const JQNetworkConnectPointerFunction &failCallback
        );

    void readySendPackages(
            const qint32 &randomFlag,
            QList< JQNetworkPackageSharedPointer > &packages,
            const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
            const JQNetworkConnectPointerFunction &failCallback
        );

    void sendDataRequestToRemote(const JQNetworkPackageSharedPointer &package);

    void sendPackageToRemote(const JQNetworkPackageSharedPointer &package);

private:
    // Settings
    JQNetworkConnectSettingsSharedPointer connectSettings_;
    std::function< void( std::function< void() > ) > runOnConnectThreadCallback_;

    // Socket
    QSharedPointer< QTcpSocket > tcpSocket_;
    bool onceConnectSucceed_ = false;
    bool isAbandonTcpSocket_ = false;
    QByteArray tcpSocketBuffer_;

    // Timer
    QSharedPointer< QTimer > timerForConnectToHostTimeOut_;
    QSharedPointer< QTimer > timerForSendPackageCheck_;

    // Package
    QMutex mutexForSend_;
    qint32 sendRandomFlagRotaryIndex_ = 0;
    QMap< qint32, ReceivedCallbackPackage > onReceivedCallbacks_; // randomFlag -> package

    // Payload
    QMap< qint32, QList< JQNetworkPackageSharedPointer > > sendPayloadPackagePool_; // randomFlag -> package
    QMap< qint32, JQNetworkPackageSharedPointer > receivePayloadPackagePool_; // randomFlag -> package

    // File
    QMap< qint32, QSharedPointer< QFile > > waitForSendFiles_; // randomFlag -> file
    QMap< qint32, QPair< JQNetworkPackageSharedPointer, QSharedPointer< QFile > > > receivedFilePackagePool_; // randomFlag -> { package, file }

    // Statistics
    qint64 connectCreateTime_ = 0;
    qint64 connectSucceedTime_ = 0;
    qint64 waitForSendBytes_ = 0;
    qint64 alreadyWrittenBytes_ = 0;
};

// inc import
#include "jqnetwork_connect.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECT_H_
