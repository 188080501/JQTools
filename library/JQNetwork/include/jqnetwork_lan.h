/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_LAN_H_
#define JQNETWORK_INCLUDE_JQNETWORK_LAN_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

struct JQNetworkLanSettings
{
    QString dutyMark;

    QHostAddress multicastGroupAddress;
    quint16 bindPort = 0;

    int checkLoopInterval = 10 * 1000;
    int lanNodeTimeoutInterval = 60 * 1000;

    std::function< void( const JQNetworkLanNode & ) > lanNodeOnlineCallback;
    std::function< void( const JQNetworkLanNode & ) > lanNodeActiveCallback;
    std::function< void( const JQNetworkLanNode & ) > lanNodeOfflineCallback;
    std::function< void() > lanNodeListChangedCallback;

    int globalProcessorThreadCount = 1;
};

struct JQNetworkLanNode
{
    QString nodeMarkSummary;
    QString dutyMark;
    int dataPackageIndex = 0;
    qint64 lastActiveTime = 0;
    QList< QHostAddress > ipList;
    QVariant appendData;
    QHostAddress matchAddress;
    bool isSelf = false;
};

struct JQNetworkLanAddressEntries
{
    QHostAddress ip;
    QHostAddress netmask;
    QHostAddress ipSegment;
    bool isVmAddress;
};

class JQNetworkLan: public QObject
{
    Q_OBJECT

public:
    JQNetworkLan(const JQNetworkLanSettingsSharedPointer &lanSettings);

    ~JQNetworkLan();

    JQNetworkLan(const JQNetworkLan &) = delete;

    JQNetworkLan &operator =(const JQNetworkLan &) = delete;

    static JQNetworkLanSharedPointer createLan(
            const QHostAddress &multicastGroupAddress,
            const quint16 &bindPort,
            const QString &dutyMark = ""
        );

    static QList< JQNetworkLanAddressEntries > lanAddressEntries();

    inline JQNetworkLanSettingsSharedPointer lanSettings();

    inline QString nodeMarkSummary() const;

    inline void setAppendData(const QVariant &appendData);

    bool begin();

    QHostAddress matchLanAddressEntries(const QList< QHostAddress > &ipList);

    QList< JQNetworkLanNode > availableLanNodes();

    void sendOnline();

    void sendOffline();

private:
    void refreshLanAddressEntries();

    bool refreshUdp();

    void checkLoop();

    QByteArray makeData(const bool &requestOffline, const bool &requestFeedback);

    void onUdpSocketReadyRead();

    inline void onLanNodeStateOnline(const JQNetworkLanNode &lanNode);

    inline void onLanNodeStateActive(const JQNetworkLanNode &lanNode);

    inline void onLanNodeStateOffline(const JQNetworkLanNode &lanNode);

    inline void onLanNodeListChanged();

private:
    // Thread pool
    static QWeakPointer< JQNetworkThreadPool > globalProcessorThreadPool_;
    QSharedPointer< JQNetworkThreadPool > processorThreadPool_;

    // Settings
    JQNetworkLanSettingsSharedPointer lanSettings_;

    // Socket
    QSharedPointer< QUdpSocket > udpSocket_;

    // Data
    QList< JQNetworkLanAddressEntries > lanAddressEntries_;
    QMap< QString, JQNetworkLanNode > availableLanNodes_;

    // Other
    QString nodeMarkSummary_;
    QMutex mutex_;
    QVariant appendData_;
    QSharedPointer< QTimer > timerForCheckLoop_;
    int checkLoopCounting_ = -1;
    int nextDataPackageIndex_ = 0;
};

// inc import
#include "jqnetwork_lan.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_LAN_H_
