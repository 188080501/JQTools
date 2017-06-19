/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_H_
#define JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_H_

// C++ lib import
#include <functional>
#include <vector>
#include <memory>

// Qt lib import
#include <QObject>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QPointer>
#include <QMutex>
#include <QVariant>
#include <QHostAddress>

#define JQNETWORK_VERSIONNUMBER QVersionNumber::fromString( JQNETWORK_VERSIONSTRING )

#define JQNETWORKPACKAGE_BOOTFLAG qint8( 0x7d )
#define JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG qint8( 0x1 )
#define JQNETWORKPACKAGE_PAYLOADDATAREQUESTPACKGEFLAG qint8( 0x2 )
#define JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG qint8( 0x3 )
#define JQNETWORKPACKAGE_FILEDATAREQUESTPACKGEFLAG qint8( 0x4 )
#define JQNETWORKPACKAGE_UNCOMPRESSEDFLAG qint8( 0x1 )
#define JQNETWORKPACKAGE_COMPRESSEDFLAG qint8( 0x2 )

#if ( defined Q_OS_IOS ) || ( defined Q_OS_ANDROID )
#   define JQNETWORK_ADVISE_THREADCOUNT 1
#   define JQNETWORKPACKAGE_ADVISE_CUTPACKAGESIZE qint64( 512 * 1024 )
#else
#   define JQNETWORK_ADVISE_THREADCOUNT 2
#   define JQNETWORKPACKAGE_ADVISE_CUTPACKAGESIZE qint64( 2 * 1024 * 1024 )
#endif

#define JQNETWORK_NULLPTR_CHECK( ptr, ... ) \
    if ( !ptr ) { qDebug( "%s: %s is null", __func__, # ptr ); return __VA_ARGS__; }

#define JQNETWORK_THISNULL_CHECK( message, ... )                \
    {                                                           \
        auto this_ = this;                                      \
        if ( !this_ )                                           \
        {                                                       \
            qDebug( "%s: this is null", message );              \
            return __VA_ARGS__;                                 \
        }                                                       \
    }

class QSemaphore;
class QMutex;
class QTimer;
class QThreadPool;
class QEventLoop;
class QJsonObject;
class QJsonArray;
class QJsonValue;
class QJsonDocument;
class QFile;
class QDir;
class QFileInfo;
class QTcpSocket;
class QTcpServer;
class QUdpSocket;

template < typename T > class QVector;
template < typename T > class QSet;

class JQNetworkPackage;
class JQNetworkConnect;
class JQNetworkConnectPool;
class JQNetworkServer;
class JQNetworkProcessor;
class JQNetworkClient;
class JQNetworkLan;

struct JQNetworkConnectSettings;
struct JQNetworkConnectPoolSettings;
struct JQNetworkServerSettings;
struct JQNetworkClientSettings;
struct JQNetworkLanSettings;
struct JQNetworkLanNode;

typedef QPointer< JQNetworkPackage > JQNetworkPackagePointer;
typedef QPointer< JQNetworkConnect > JQNetworkConnectPointer;
typedef QPointer< JQNetworkConnectPool > JQNetworkConnectPoolPointer;
typedef QPointer< JQNetworkServer > JQNetworkServerPointer;
typedef QPointer< JQNetworkProcessor > JQNetworkProcessorPointer;
typedef QPointer< JQNetworkClient > JQNetworkClientPointer;
typedef QPointer< JQNetworkLan > JQNetworkLanPointer;

typedef std::shared_ptr< void > JQNetworkVoidSharedPointer;

typedef QSharedPointer< JQNetworkPackage > JQNetworkPackageSharedPointer;
typedef QSharedPointer< JQNetworkConnect > JQNetworkConnectSharedPointer;
typedef QSharedPointer< JQNetworkConnectPool > JQNetworkConnectPoolSharedPointer;
typedef QSharedPointer< JQNetworkServer > JQNetworkServerSharedPointer;
typedef QSharedPointer< JQNetworkProcessor > JQNetworkProcessorSharedPointer;
typedef QSharedPointer< JQNetworkClient > JQNetworkClientSharedPointer;
typedef QSharedPointer< JQNetworkLan > JQNetworkLanSharedPointer;

typedef QSharedPointer< JQNetworkConnectSettings > JQNetworkConnectSettingsSharedPointer;
typedef QSharedPointer< JQNetworkConnectPoolSettings > JQNetworkConnectPoolSettingsSharedPointer;
typedef QSharedPointer< JQNetworkServerSettings > JQNetworkServerSettingsSharedPointer;
typedef QSharedPointer< JQNetworkClientSettings > JQNetworkClientSettingsSharedPointer;
typedef QSharedPointer< JQNetworkLanSettings > JQNetworkLanSettingsSharedPointer;

typedef std::function< void(const JQNetworkConnectPointer &connect ) > JQNetworkConnectPointerFunction;
typedef std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package ) > JQNetworkConnectPointerAndPackageSharedPointerFunction;

struct JQNetworkOnReceivedCallbackPackage
{
    std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &) > succeedCallback = nullptr;
    std::function< void(const JQNetworkConnectPointer &connect) > failCallback = nullptr;
};

class JQNetworkThreadPoolHelper: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkThreadPoolHelper )

public:
    JQNetworkThreadPoolHelper();

    ~JQNetworkThreadPoolHelper() = default;

    void run(const std::function< void() > &callback);

public Q_SLOTS:
    void onRun();

private:
    QMutex mutex_;
    QSharedPointer< std::vector< std::function< void() > > > waitForRunCallbacks_;
    bool alreadyCall_ = false;
    qint64 lastRunTime_ = 0;
    int lastRunCallbackCount_ = 0;
};

class JQNetworkThreadPool: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkThreadPool )

public:
    JQNetworkThreadPool(const int &threadCount);

    ~JQNetworkThreadPool();

    inline int nextRotaryIndex();

    int run(const std::function< void() > &callback, const int &threadIndex = -1);

    inline void runEach(const std::function< void() > &callback);

    int waitRun(const std::function< void() > &callback, const int &threadIndex = -1);

    inline void waitRunEach(const std::function< void() > &callback);

private:
    QSharedPointer< QThreadPool > threadPool_;
    QSharedPointer< QVector< QPointer< QEventLoop > > > eventLoops_;
    QSharedPointer< QVector< QPointer< JQNetworkThreadPoolHelper > > > helpers_;
    int rotaryIndex_ = -1;
};

class JQNetworkNodeMark
{
public:
    JQNetworkNodeMark(const QString &dutyMark);

    ~JQNetworkNodeMark() = default;

    static QString calculateNodeMarkSummary(const QString &dutyMark);

    inline qint64 applicationStartTime() const;

    inline QString applicationFilePath() const;

    inline QString localHostName() const;

    inline qint64 nodeMarkCreatedTime() const;

    inline QString nodeMarkClassAddress() const;

    inline QString dutyMark() const;

    inline QString nodeMarkSummary() const;

private:
    static qint64 applicationStartTime_;
    static QString applicationFilePath_;
    static QString localHostName_;
    qint64 nodeMarkCreatedTime_;
    QString nodeMarkClassAddress_;
    QString dutyMark_;
    QString nodeMarkSummary_;
};

namespace JQNetwork
{

void printVersionInformation(const char *jqNetworkCompileModeString = JQNETWORK_COMPILE_MODE_STRING);

}

// inc import
#include "jqnetwork_foundation.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_H_
