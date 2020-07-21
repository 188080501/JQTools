/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef JQLIBRARY_INCLUDE_JQFOUNDATION_H_
#define JQLIBRARY_INCLUDE_JQFOUNDATION_H_

#if ((__cplusplus < 201103) && !(defined _MSC_VER)) || ((defined _MSC_VER) && (_MSC_VER < 1800))
#   error("Please add c++11 config on pro file")
#endif

#ifndef QT_CORE_LIB
#   error("Please add core in pro file")
#endif

#ifndef QT_GUI_LIB
#   error("Please add gui in pro file")
#endif

// C++ lib import
#include <functional>

// Qt lib import
#include <QCoreApplication>
#include <QSharedPointer>
#include <QCryptographicHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageLogContext>
#include <QMap>
#include <QVector>
#include <QSize>
#include <QMutex>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QThreadPool>

// JQLibrary lib import
#include <JQDeclare>

enum JQDebugEnum
{
    JQDebugUnknown,

    JQDebugForceConsoleMode,
    JQDebugReset,

    JQDebugBlue,
    JQDebugGreen,
    JQDebugRed,
    JQDebugYellow,
    JQDebugPurple,
    JQDebugCyan,
    JQDebugBlack,
    JQDebugWhite,
};

QDebug operator<<(QDebug dbg, const QPair< QDateTime, QDateTime > &data);

QDebug operator<<(QDebug dbg, const JQDebugEnum &debugConfig);

std::ostream &operator<<(std::ostream &dbg, const JQDebugEnum &debugConfig);

namespace JQFoundation
{

QString hashString(const QByteArray &key, const QCryptographicHash::Algorithm &algorithm = QCryptographicHash::Sha1);

QString variantToString(const QVariant &value);

QString createUuidString();

QJsonObject jsonFilter(const QJsonObject &source, const QStringList &leftKey, const QJsonObject &mix = QJsonObject());

QJsonObject jsonFilter(const QJsonObject &source, const char *leftKey, const QJsonObject &mix = QJsonObject());

template< class Key, class T >
QMap< Key, T > mapFilter(const QMap< Key, T > &source, const QStringList &leftKey, const QMap< Key, T > &mix = QMap< Key, T >());

template< class Key, class T >
QMap< Key, T > mapFilter(const QMap< Key, T > &source, const char *leftKey, const QMap< Key, T > &mix = QMap< Key, T >());

template< class Key, class T >
QMap< Key, T > mapMix(const QMap< Key, T > &source, const QMap< Key, T > &mix);

QVariantList listVariantMapToVariantList(const QList< QVariantMap > &source);

QList< QVariantMap > variantListToListVariantMap(const QVariantList &source);

QVariantMap mapKeyTranslate(const QVariantMap &source, const QMap< QString, QString > &keyMap);

QVariantList listKeyTranslate(const QVariantList &source, const QMap< QString, QString > &keyMap);

QList< QVariantMap > listKeyTranslate(const QList< QVariantMap > &source, const QMap< QString, QString > &keyMap);

QSharedPointer< QTimer > JQLIBRARY_EXPORT setTimerCallback(
        const int &interval,
        const std::function< void(bool &continueFlag) > &callback,
        const bool &callbackOnStart = false
    );

#if ( defined QT_CONCURRENT_LIB ) && ( QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0 ) )
void JQLIBRARY_EXPORT setTimerCallback(
        const QDateTime &dateTime,
        const std::function< void() > &callback,
        const QSharedPointer< QThreadPool > &threadPool = nullptr
    );

void JQLIBRARY_EXPORT setTimerCallback(
        const std::function< QDateTime() > &nextTime,
        const std::function< void() > &callback,
        const QSharedPointer< QThreadPool > &threadPool = nullptr
    );
#endif

void JQLIBRARY_EXPORT setDebugOutput(
        const QString &targetFilePath,
        const bool &argDateFlag = false,
        const std::function< void(const QMessageLogContext &context, const QString &) > &warningMessageCallback = nullptr
    );

void openDebugConsole();

bool JQLIBRARY_EXPORT singleApplication(const QString &flag);

bool JQLIBRARY_EXPORT singleApplicationExist(const QString &flag);

QByteArray pixmapToByteArray(const QPixmap &pixmap, const QString &format, int quality = -1);

QByteArray imageToByteArray(const QImage &image, const QString &format, int quality = -1);

QString snakeCaseToCamelCase(const QString &source, const bool &firstCharUpper = false);

int rectOverflow(const QSize &frameSize, const QRect &rect, const int &redundancy = 0);

QRect scaleRect(const QRect &rect, const qreal &scale);

QRect scaleRect(const QRect &rect, const qreal &horizontalScale, const qreal &verticalScale);

QPoint scalePoint(const QPoint &point, const qreal &horizontalScale, const qreal &verticalScale);

QPointF scalePoint(const QPointF &point, const qreal &horizontalScale, const qreal &verticalScale);

QPoint pointFToPoint(const QPointF &point, const QSize &size);

QPointF pointToPointF(const QPoint &point, const QSize &size);

QLine pointFToLine(const QPointF &point1, const QPointF &point2, const QSize &size);

QRect rectFToRect(const QRectF &rect, const QSize &size);

QRectF rectToRectF(const QRect &rect, const QSize &size);

QLine lineFToLine(const QLineF &line, const QSize &size);

QRect cropRect(const QRect &rect, const QRect &bigRect);

QImage imageCopy(const QImage &image, const QRect &rect);

QImage removeImageColor(const QImage &image, const QColor &color);

QList< QPair< QDateTime, QDateTime > > extractTimeRange(const QDateTime &startTime, const QDateTime &endTime, const qint64 &interval);

void waitFor(const std::function< bool() > &predicate, const int &timeout);

#if ( ( defined Q_OS_MAC ) && !( defined Q_OS_IOS ) ) || ( defined Q_OS_WIN ) || ( defined Q_OS_LINUX )
QPair< int, QByteArray > JQLIBRARY_EXPORT startProcessAndReadOutput(const QString &program, const QStringList &arguments, const int &maximumTime = 5 * 1000);
#endif

template< class Key, class T >
QMap< Key, T > mapFilter(const QMap< Key, T > &source, const QStringList &leftKey, const QMap< Key, T > &mix)
{
    QMap< Key, T > result;

    for ( const auto &key: leftKey )
    {
        auto buf = source.find( key );
        if ( buf != source.end() )
        {
            result[ buf.key() ] = buf.value();
        }
    }

    if ( !mix.isEmpty() )
    {
        for ( auto it = mix.begin(); it != mix.end(); ++it )
        {
            result.insert( it.key(), it.value() );
        }
    }

    return result;
}

template< class Key, class T >
QMap< Key, T > mapFilter(const QMap< Key, T > &source, const char *leftKey, const QMap< Key, T > &mix)
{
    return JQFoundation::mapFilter( source, QStringList( { leftKey } ), mix );
}

template< class Key, class T >
QMap< Key, T > mapMix(const QMap< Key, T > &source, const QMap< Key, T > &mix)
{
    QMap< Key, T > result = source;

    for ( auto it = mix.begin(); it != mix.end(); ++it )
    {
        result[ it.key() ] = it.value();
    }

    return result;
}

}

inline bool operator <(const QSize &a, const QSize &b)
{
    if ( a.width() != b.width() ) { return a.width() < b.width(); }
    return a.height() < b.height();
}

class JQLIBRARY_EXPORT JQTickCounter
{
public:
    explicit JQTickCounter(const qint64 &timeRange = 5 * 1000); // 此变量影响tick计算精准度，可能会导致tick值不可靠，若非必要请勿修改

    ~JQTickCounter() = default;

public:
    void tick(const int &count = 1);

    qreal tickPerSecond();

    QString tickPerSecondDisplayString();

private:
    qint64 timeRange_;
    QList< qint64 > tickRecord_;
    QSharedPointer< QMutex > mutex_;
};

class JQLIBRARY_EXPORT JQFpsControl
{
public:
    JQFpsControl(const qreal &fps = 15);

    ~JQFpsControl() = default;

    void setFps(const qreal &fps);

    void waitNextFrame();

    bool readyNextFrame();

private:
    qreal fps_;
    qint64 lastTriggeredTime_ = 0;
};

class JQLIBRARY_EXPORT JQMemoryPool
{
private:
    struct JQMemoryPoolNodeHead
    {
        qint32 flag = 0x3519;
        QThread *mallocThread = nullptr;
        qint64 mallocTime = 0;
        size_t requestSize = 0;
        void *memory = nullptr;
    };

private:
    JQMemoryPool() = default;

public:
    ~JQMemoryPool() = default;

    static void initReleaseThreshold(const qreal &percentage = 0.2);

    static qint64 realTotalMallocSize();

    static qint64 totalMallocSize();

    static qint64 totalMallocCount();

    static void *requestMemory(const size_t &requestSize);

    static void recoverMemory(void *memory);

private:
    static JQMemoryPoolNodeHead makeNode(const size_t &requestSize);

private:
    static QMutex mutex_;
    static QMap< size_t, QVector< JQMemoryPoolNodeHead > > nodeMap_;

    static QAtomicInteger< qint64 > realTotalMallocSize_;
    static QAtomicInteger< qint64 > totalMallocSize_;
    static QAtomicInteger< qint64 > totalMallocCount_;
    static qint64 releaseThreshold_;
};

#endif//JQLIBRARY_INCLUDE_JQFOUNDATION_H_
