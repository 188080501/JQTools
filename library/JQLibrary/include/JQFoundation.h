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
#include <QMap>
#include <QVector>
#include <QSize>

class QTableWidget;
class QTreeWidget;
class QTextEdit;
class QLineEdit;
class QTimer;
class QMutex;

// Macro define
#define PropertyDeclare(Type, name, setName, ...)                                           \
    private:                                                                                \
    Type name ## _ __VA_ARGS__;                                                             \
    public:                                                                                 \
    inline const Type &name() const { return name ## _; }                                   \
    inline void setName(const Type &name) { name ## _ = name; }                             \
    private:

#define PropertyDeclareWithSlot(Type, name, setName, ...)                                   \
    private:                                                                                \
    Type name ## _ __VA_ARGS__;                                                             \
    public Q_SLOTS:                                                                         \
    Type name() const { return name ## _; }                                                 \
    void setName(const Type &name) { name ## _ = name; }                                    \
    private:

#define PtrPropertyDeclare(Type, name, setName, ...)                                        \
    private:                                                                                \
    Type *name ## _ __VA_ARGS__;                                                            \
    public:                                                                                 \
    inline const Type *name() const                                                         \
        { return name ## _; }                                                               \
    inline void setName(const Type &name)                                                   \
        { if ( name ## _ ) { delete name ## _; }                                            \
        name ## _ = new Type( name ); }                                                     \
    private:

#define RUNONOUTRANGEHELPER2( x, y ) x ## y
#define RUNONOUTRANGEHELPER( x, y ) RUNONOUTRANGEHELPER2( x, y )
#define RUNONOUTRANGE( ... )                                                                \
    auto RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) = __VA_ARGS__;              \
    QSharedPointer< int > RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ )(                   \
        new int,                                                                            \
        [ RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ ) ](int *data)               \
    {                                                                                       \
        RUNONOUTRANGEHELPER( runOnOutRangeCallback, __LINE__ )();                           \
        delete data;                                                                        \
    } );                                                                                    \
    if ( RUNONOUTRANGEHELPER( runOnOutRange, __LINE__ ).data() == nullptr ) { exit( -1 ); }

#define rforeach (variable, container)                                                      \
for (RforeachContainer<__typeof__((container))> _container_((container));                   \
    _container_.__howMuch__; _container_.__howMuch__--)                                     \
    for (variable = *(--_container_.__now__); ; __extension__ ({ break;}))

#define JQCONST( property ) \
    static_cast< const decltype( property ) >( property )

template < typename T >
class RforeachContainer {
public:
    inline RforeachContainer(const T& t) : __now__(t.end()), __howMuch__(t.size()) { }
    typename T::const_iterator __now__;
    int __howMuch__;
};

template < typename T >
inline typename std::enable_if< !std::is_pod< T >::value >::type
memset( T*, int, size_t )
{
    static_assert( std::is_pod< T >::value, "memset error: target not pod" );
}

template < typename T >
inline typename std::enable_if< !std::is_pod< T >::value >::type
memcpy( T*, int, size_t )
{
    static_assert( std::is_pod< T >::value, "memcpy error: target not pod" );
}

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

QVariantMap mapKeyTranslate(const QVariantMap &source, const QMap< QString, QString > &keyMap);

QVariantList listKeyTranslate(const QVariantList &source, const QMap< QString, QString > &keyMap);

QList< QVariantMap > listKeyTranslate(const QList< QVariantMap > &source, const QMap< QString, QString > &keyMap);

QSharedPointer< QTimer > setTimerCallback(const int &interval, const std::function< void(bool &continueFlag) > &callback, const bool &callbackOnStart = false);

void setDebugOutput(const QString &targetFilePath, const bool &argDateFlag = false);

void openDebugConsole();

bool singleApplication(const QString &flag);

bool singleApplicationExist(const QString &flag);

QByteArray pixmapToByteArray(const QPixmap &pixmap, const QString &format, int quality = -1);

QByteArray imageToByteArray(const QImage &image, const QString &format, int quality = -1);

QString snakeCaseToCamelCase(const QString &source, const bool &firstCharUpper = false);

QRect scaleRect(const QRect &rect, const qreal &scale);

QRect scaleRect(const QRect &rect, const qreal &horizontalScale, const qreal &verticalScale);

#if ( ( defined Q_OS_MAC ) && !( defined Q_OS_IOS ) ) || ( defined Q_OS_WIN ) || ( defined Q_OS_LINUX )
QPair< int, QByteArray > startProcessAndReadOutput(const QString &program, const QStringList &arguments, const int &maximumTime = 5 * 1000);
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

class JQTickCounter
{
public:
    explicit JQTickCounter(const qint64 &timeRange = 3 * 1000);

    ~JQTickCounter() = default;

public:
    void tick();

    qreal tickPerSecond();

private:
    qint64 timeRange_;
    QVector< qint64 > tickRecord_;
    QSharedPointer< QMutex > mutex_;
};

#endif//JQLIBRARY_INCLUDE_JQFOUNDATION_H_
