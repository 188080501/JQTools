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

// JQFoundation header include
#include "JQFoundation.h"

// C++ lib import
#include <iostream>

// Qt lib import
#include <QDebug>
#include <QSharedMemory>
#include <QHash>
#include <QBuffer>
#include <QMetaMethod>
#include <QImage>
#include <QTextCursor>
#include <QPalette>
#include <QFileInfo>
#include <QDir>
#include <QProcess>
#include <QUuid>
#include <QTimer>
#include <QTime>
#include <QDateTime>
#include <QTextStream>
#include <QMutex>
#include <QThread>

// Windows lib import
#ifdef Q_OS_WIN
#   include <Windows.h>
#endif

QString JQFoundation::hashString(const QByteArray &key, const QCryptographicHash::Algorithm &algorithm)
{
    return QCryptographicHash::hash( key, algorithm ).toHex();
}

QString JQFoundation::variantToString(const QVariant &value)
{
    QString result;

    if ( ( value.type() == 31 ) || ( value.type() == 51 ) || ( value.type() == QVariant::Invalid ) ) { return "NULL"; }

    switch ( value.type() )
    {
        case QVariant::Bool:
        {
            result = ( ( value.toBool() ) ? ( "1" ) : ( "0" ) );
            break;
        }
        case QVariant::ByteArray:
        {
            result = QString( "\\x" );
            result += value.toByteArray().toHex();
            break;
        }
        case QVariant::String:
        {
            result = value.toString();
            break;
        }
        case QVariant::Int:
        case QVariant::Double:
        {
            result = QString::number( value.toDouble(), 'f', 8 );
            while ( result.endsWith( '0' ) )
            {
                result = result.mid( 0, result.size() - 1 );
            }
            if ( result.endsWith( '.' ) )
            {
                result = result.mid( 0, result.size() - 1 );
            }
            if ( result == "" )
            {
                result = "0";
            }

            break;
        }
        default:
        {
            if ( value.type() == QVariant::nameToType( "QJsonValue" ) )
            {
                const auto &&jsonValue = value.toJsonValue();

                switch ( jsonValue.type() )
                {
                    case QJsonValue::Null:
                    {
                        result = "NULL";
                        break;
                    }
                    case QJsonValue::Bool:
                    {
                        result = ( ( jsonValue.toBool() ) ? ( "1" ) : ( "0" ) );
                        break;
                    }
                    case QJsonValue::String:
                    {
                        result = jsonValue.toString();
                        break;
                    }
                    case QJsonValue::Double:
                    {
                        result = QString::number( jsonValue.toDouble(), 'f', 8 );
                        while ( result.endsWith( '0' ) )
                        {
                            result = result.mid( 0, result.size() - 1 );
                        }
                        if ( result.endsWith( '.' ) )
                        {
                            result = result.mid( 0, result.size() - 1 );
                        }
                        if ( result == "" )
                        {
                            result = "0";
                        }

                        break;
                    }
                    default:
                    {
                        qDebug() << "JQFoundation::variantToString: unexpected json type:" << jsonValue;
                        result = jsonValue.toString();
                        break;
                    }
                }
            }
            else
            {
                qDebug() << "JQFoundation::variantToString: unexpected type:" << value;
                result = value.toString();
            }
            break;
        }
    }

    return result;
}

QString JQFoundation::createUuidString()
{
    return QUuid::createUuid().toString().mid( 1, 36 );
}

QJsonObject JQFoundation::jsonFilter(const QJsonObject &source, const QStringList &leftKey, const QJsonObject &mix)
{
    QJsonObject result;

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

QJsonObject JQFoundation::jsonFilter(const QJsonObject &source, const char *leftKey, const QJsonObject &mix)
{
    return JQFoundation::jsonFilter( source, QStringList( { leftKey } ), mix );
}

QVariantList JQFoundation::listVariantMapToVariantList(const QList< QVariantMap > &source)
{
    QVariantList result;

    for ( const auto &data: source )
    {
        result.push_back( data );
    }

    return result;
}

QList< QVariantMap > JQFoundation::variantListToListVariantMap(const QVariantList &source)
{
    QList< QVariantMap > result;

    for ( const auto &item: source )
    {
        result.push_back( item.toMap() );
    }

    return result;
}

QVariantMap JQFoundation::mapKeyTranslate(const QVariantMap &source, const QMap< QString, QString > &keyMap)
{
   QVariantMap result;

    for ( auto sourceIt = source.begin(); sourceIt != source.end(); ++sourceIt )
    {
        const auto &&keyMapIt = keyMap.find( sourceIt.key() );
        if ( keyMapIt == keyMap.end() ) { continue; }

        result[ keyMapIt.value() ] = sourceIt.value();
    }

    return result;
}

QVariantList JQFoundation::listKeyTranslate(const QVariantList &source, const QMap< QString, QString > &keyMap)
{
    QVariantList result;

    for ( const auto &data: source )
    {
        result.push_back( mapKeyTranslate( data.toMap(), keyMap ) );
    }

    return result;
}

QList< QVariantMap > JQFoundation::listKeyTranslate(const QList< QVariantMap > &source, const QMap<QString, QString> &keyMap)
{
    QList< QVariantMap > result;

    for ( const auto &data: source )
    {
        result.push_back( mapKeyTranslate( data, keyMap ) );
    }

    return result;
}

QSharedPointer< QTimer > JQFoundation::setTimerCallback(const int &interval, const std::function<void (bool &continueFlag)> &callback, const bool &callbackOnStart)
{
    QSharedPointer< QTimer > timer( new QTimer );

    QObject::connect( timer.data(), &QTimer::timeout, [ timer, callback ]()
    {
        bool continueFlag = true;
        callback( continueFlag );
        if ( continueFlag )
        {
            timer->start();
        }
    } );

    timer->setInterval( interval );
    timer->setSingleShot( true );

    if ( callbackOnStart )
    {
        bool continueFlag = true;
        callback( continueFlag );
        if ( continueFlag )
        {
            timer->start();
        }
    }
    else
    {
        timer->start();
    }

    return timer;
}

void JQFoundation::setDebugOutput(const QString &rawTargetFilePath_, const bool &argDateFlag_)
{
    static QString rawTargetFilePath;
    static bool argDateFlag;

    rawTargetFilePath = rawTargetFilePath_;
    argDateFlag = argDateFlag_;

    class HelperClass
    {
    public:
        static void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &message_)
        {
            QString message;

            switch ( type )
            {
                case QtDebugMsg:
                {
                    message = message_;
                    break;
                }
                case QtWarningMsg:
                {
                    message.append( "Warning: " );
                    message.append( message_ );
                    break;
                }
                case QtCriticalMsg:
                {
                    message.append( "Critical: " );
                    message.append( message_ );
                    break;
                }
                case QtFatalMsg:
                {
                    message.append( "Fatal: " );
                    message.append( message_ );
                    break;
                }
                default: { break; }
            }

            QString currentTargetFilePath;

            if ( argDateFlag )
            {
                currentTargetFilePath = rawTargetFilePath.arg( ( ( argDateFlag ) ? ( QDateTime::currentDateTime().toString("yyyy_MM_dd") ) : ( "" ) ) );
            }
            else
            {
                currentTargetFilePath = rawTargetFilePath;
            }

            if ( !QFileInfo::exists( currentTargetFilePath ) )
            {
                QDir().mkpath( QFileInfo( currentTargetFilePath ).path() );
            }

            QFile file( currentTargetFilePath );
            file.open( QIODevice::WriteOnly | QIODevice::Append );

            QTextStream textStream( &file );
            textStream << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ) << ": " << message << endl;
        }
    };

    qInstallMessageHandler( HelperClass::messageHandler );
}

void JQFoundation::openDebugConsole()
{
#ifdef Q_OS_WIN
    class HelperClass
    {
    public:
        static void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &message_)
        {
            QString message;

            switch ( type )
            {
                case QtDebugMsg:
                {
                    message = message_;
                    break;
                }
                case QtWarningMsg:
                {
                    message.append( "Warning: " );
                    message.append( message_ );
                    break;
                }
                case QtCriticalMsg:
                {
                    message.append( "Critical: " );
                    message.append( message_ );
                    break;
                }
                case QtFatalMsg:
                {
                    message.append( "Fatal: " );
                    message.append( message_ );
                    break;
                }
                default: { break; }
            }

            std::cout << QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss" ).toUtf8().data()
                      << ": " << message.toUtf8().data() << std::endl;
        }
    };

    qInstallMessageHandler( HelperClass::messageHandler );

    AllocConsole();
#endif
}

#if !(defined Q_OS_IOS) && !(defined Q_OS_ANDROID) && !(defined Q_OS_WINPHONE)
bool JQFoundation::singleApplication(const QString &flag)
{
    static QSharedMemory *shareMem = nullptr;

    if (shareMem)
    {
        return true;
    }

    shareMem = new QSharedMemory( "JQFoundationSingleApplication_" + flag );

    for ( auto count = 0; count < 2; ++count )
    {
        if (shareMem->attach( QSharedMemory::ReadOnly ))
        {
            shareMem->detach();
        }
    }

    if ( shareMem->create( 1 ) )
    {
        return true;
    }

    return false;
}
#else
bool JQFoundation::singleApplication(const QString &)
{
    return true;
}
#endif

#if !(defined Q_OS_IOS) && !(defined Q_OS_ANDROID) && !(defined Q_OS_WINPHONE)
bool JQFoundation::singleApplicationExist(const QString &flag)
{
    QSharedMemory shareMem( "JQFoundationSingleApplication_" + flag );

    for ( auto count = 0; count < 2; ++count )
    {
        if (shareMem.attach( QSharedMemory::ReadOnly ))
        {
            shareMem.detach();
        }
    }

    if ( shareMem.create( 1 ) )
    {
        return false;
    }

    return true;
}
#else
bool JQFoundation::singleApplicationExist(const QString &)
{
    return false;
}
#endif

QByteArray JQFoundation::pixmapToByteArray(const QPixmap &pixmap, const QString &format, int quality)
{
    QByteArray bytes;
    QBuffer buffer( &bytes );

    buffer.open( QIODevice::WriteOnly );
    pixmap.save( &buffer, format.toLatin1().data(), quality );

    return bytes;
}

QByteArray JQFoundation::imageToByteArray(const QImage &image, const QString &format, int quality)
{
    static QMap< QThread *, QByteArray * > cacheMap; // thread -> QByteArray
    static QMutex cacheMutex;

    QByteArray *bytes = nullptr;

    cacheMutex.lock();

    {
        auto it = cacheMap.find( QThread::currentThread() );
        if ( ( it == cacheMap.end() ) || !*it )
        {
            bytes = new QByteArray;
            cacheMap[ QThread::currentThread() ] = bytes;
        }
        else
        {
            bytes = *it;
        }
    }

    cacheMutex.unlock();

    if ( bytes->capacity() <= 0 )
    {
        bytes->reserve( 512 * 1024 );
    }

//    qDebug() << reinterpret_cast< const void * >( bytes->constData() ) << bytes->size() << bytes->capacity();

    QBuffer buffer( bytes );

    buffer.open( QIODevice::WriteOnly );
    image.save( &buffer, format.toLatin1().data(), quality );

//    qDebug() << reinterpret_cast< const void * >( bytes->constData() ) << bytes->size() << bytes->capacity();

    return *bytes;
}

QString JQFoundation::snakeCaseToCamelCase(const QString &source, const bool &firstCharUpper)
{
    const auto &&splitList = source.split( '_', QString::SkipEmptyParts );
    QString result;

    for ( const auto &splitTag: splitList )
    {
        if ( splitTag.size() == 1 )
        {
            if ( result.isEmpty() )
            {
                if ( firstCharUpper )
                {
                    result += splitTag[ 0 ].toUpper();
                }
                else
                {
                    result += splitTag;
                }
            }
            else
            {
                result += splitTag[ 0 ].toUpper();
            }
        }
        else
        {
            if ( result.isEmpty() )
            {
                if ( firstCharUpper )
                {
                    result += splitTag[ 0 ].toUpper();
                    result += splitTag.midRef( 1 );
                }
                else
                {
                    result += splitTag;
                }
            }
            else
            {
                result += splitTag[ 0 ].toUpper();
                result += splitTag.midRef( 1 );
            }
        }
    }

    return result;
}

QRect JQFoundation::scaleRect(const QRect &rect, const qreal &scale)
{
    return scaleRect( rect, scale, scale );
}

QRect JQFoundation::scaleRect(const QRect &rect, const qreal &horizontalScale, const qreal &verticalScale)
{
    return {
        static_cast< int >( rect.x() * horizontalScale ),
        static_cast< int >( rect.y() * verticalScale ),
        static_cast< int >( rect.width() * horizontalScale ),
        static_cast< int >( rect.height() * verticalScale )
    };
}

QPoint JQFoundation::scalePoint(const QPoint &point, const qreal &horizontalScale, const qreal &verticalScale)
{
    return {
        static_cast< int >( point.x() * horizontalScale ),
        static_cast< int >( point.y() * verticalScale )
    };
}

QPointF JQFoundation::scalePoint(const QPointF &point, const qreal &horizontalScale, const qreal &verticalScale)
{
    return {
        static_cast< qreal >( point.x() * horizontalScale ),
        static_cast< qreal >( point.y() * verticalScale )
    };
}

QPoint JQFoundation::pointFToPoint(const QPointF &point, const QSize &size)
{
    return {
        static_cast< int >( point.x() * size.width() ),
        static_cast< int >( point.y() * size.height() )
    };
}

QLine JQFoundation::pointFToLine(const QPointF &point1, const QPointF &point2, const QSize &size)
{
    return {
        JQFoundation::pointFToPoint( point1, size ),
        JQFoundation::pointFToPoint( point2, size )
    };
}

QRect JQFoundation::rectFToRect(const QRectF &rect, const QSize &size)
{
    return {
        static_cast< int >( rect.x() * size.width() ),
        static_cast< int >( rect.y() * size.height() ),
        static_cast< int >( rect.width() * size.width() ),
        static_cast< int >( rect.height() * size.height() )
    };
}

QRectF JQFoundation::rectToRectF(const QRect &rect, const QSize &size)
{
    return {
        static_cast< qreal >( rect.x() ) / size.width(),
        static_cast< qreal >( rect.y() ) / size.height(),
        static_cast< qreal >( rect.width() ) / size.width(),
        static_cast< qreal >( rect.height() ) / size.height()
    };
}

QImage JQFoundation::imageCopy(const QImage &image, const QRect &rect)
{
    const auto &&unitedRect = QRect( 0, 0, image.width(), image.height() ).united( rect );

    if ( ( unitedRect.width() > image.width() ) || ( unitedRect.height() > image.height() ) )
    {
        qDebug() << "JQFoundation::imageCopy: error:" << image.size() << rect << unitedRect;
        return { };
    }

    if ( image.format() != QImage::Format_RGB888 )
    {
        qDebug() << "JQFoundation::format: error:" <<image.format();
        return { };
    }

    auto rgbData = JQMemoryPool::requestMemory( static_cast< size_t >( rect.width() * rect.height() * 3 ) );
    QImage result(
                reinterpret_cast< unsigned char * >( rgbData ),
                rect.width(),
                rect.height(),
                rect.width() * 3,
                QImage::Format_RGB888,
                JQMemoryPool::recoverMemory,
                rgbData
           );

    for ( auto y = rect.y(); y < ( rect.y() + rect.height() ); ++y )
    {
        auto source = image.bits() + image.bytesPerLine() * y + rect.x() * 3 - 1;
        auto target = result.bits() + result.bytesPerLine() * ( y - rect.y() ) - 1;
        auto sourceEnd = source + rect.width() * 3 + 1;

        while ( source < sourceEnd )
        {
            *( ++target ) = *( ++source );
        }
    }

    return result;
}

#if ( ( defined Q_OS_MAC ) && !( defined Q_OS_IOS ) ) || ( defined Q_OS_WIN ) || ( defined Q_OS_LINUX )
QPair< int, QByteArray > JQFoundation::startProcessAndReadOutput(const QString &program, const QStringList &arguments, const int &maximumTime)
{
    QPair< int, QByteArray > reply;

    QProcess process;
    process.setProgram( program );
    process.setArguments( arguments );
    process.start();

    QObject::connect( &process, static_cast< void(QProcess::*)(int) >( &QProcess::finished ), [ &reply ](const int &exitCode)
    {
        reply.first = exitCode;
    } );
    QObject::connect( &process, &QIODevice::readyRead, [ &process, &reply ]()
    {
        reply.second.append( process.readAll() );
    } );

    process.waitForFinished( maximumTime );

    return reply;
}
#endif

JQTickCounter::JQTickCounter(const qint64 &timeRange):
    timeRange_( timeRange ),
    mutex_( new QMutex )
{ }

void JQTickCounter::tick()
{
    mutex_->lock();

    const auto &&currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();

    while ( ( !tickRecord_.isEmpty() ) && ( qAbs( currentMSecsSinceEpoch - tickRecord_.first() ) > timeRange_ ) )
    {
        tickRecord_.pop_front();
    }

    tickRecord_.push_back( currentMSecsSinceEpoch );

    mutex_->unlock();
}

qreal JQTickCounter::tickPerSecond()
{
    qreal result = 0;

    mutex_->lock();

    const auto &&currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();

    while ( ( !tickRecord_.isEmpty() ) && ( qAbs( currentMSecsSinceEpoch - tickRecord_.first() ) > timeRange_ ) )
    {
        tickRecord_.pop_front();
    }

    if ( !tickRecord_.isEmpty() )
    {
        result = static_cast< qreal >( tickRecord_.size() ) / ( timeRange_ / 1000.0 );
    }

    mutex_->unlock();

    return result;
}

// JQMemoryPool
QMutex JQMemoryPool::mutex_;
QMap< size_t, QVector< JQMemoryPool::JQMemoryPoolNodeHead > > JQMemoryPool::nodeMap_;

QAtomicInteger< qint64 > JQMemoryPool::totalMallocSize_ = 0;
qint64 JQMemoryPool::releaseThreshold_ = -1;

void JQMemoryPool::initReleaseThreshold()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof( statex );
    GlobalMemoryStatusEx( &statex );
    releaseThreshold_ = statex.ullAvailPhys / 2;
#else
    releaseThreshold_ = static_cast< qint64 >( 8 ) * 1024 * 1024 * 1024;
#endif

    qDebug() << "JQMemoryPool: Release threshold set to:" << ( releaseThreshold_ / 1024 / 1024 ) << "MB";
}

qint64 JQMemoryPool::totalMallocSize()
{
    return totalMallocSize_;
}

void *JQMemoryPool::requestMemory(const size_t &requestSize)
{
    mutex_.lock();

    if ( releaseThreshold_ <= 0 )
    {
        initReleaseThreshold();
    }

    auto it = nodeMap_.find( requestSize );

    if ( ( it == nodeMap_.end() ) || it->isEmpty() )
    {
        mutex_.unlock();

        return makeNode( requestSize ).memory;
    }
    else
    {
        auto node = it->takeLast();
        it = { };
        mutex_.unlock();

        return node.memory;
    }
}

void JQMemoryPool::recoverMemory(void *memory)
{
    auto node = reinterpret_cast< JQMemoryPoolNodeHead * >( reinterpret_cast< qint8 * >( memory ) - sizeof( JQMemoryPoolNodeHead ) );

    if ( node->flag != 0x3519 )
    {
        qDebug() << "JQMemoryPool::recoverMemory: error: flag not match:" << memory << node->flag;
        return;
    }

    if ( ( totalMallocSize_ > releaseThreshold_ ) ||
         ( node->requestSize < 128 ) )
    {
        totalMallocSize_ -= node->requestSize;
        if ( totalMallocSize_ < 0 )
        {
            qDebug() << "JQMemoryPool::recoverMemory: error:" << totalMallocSize_ << node->requestSize;
        }

        free( reinterpret_cast< qint8 * >( memory ) - sizeof( JQMemoryPoolNodeHead ) );
    }
    else
    {
        mutex_.lock();
        nodeMap_[ node->requestSize ].push_back( *node );
        mutex_.unlock();
    }
}

JQMemoryPool::JQMemoryPoolNodeHead JQMemoryPool::makeNode(const size_t &requestSize)
{
    static qint64 lastPrintSize = 0;

    totalMallocSize_ += static_cast< qint64 >( requestSize );
    if ( ( totalMallocSize_ - lastPrintSize ) > ( 256 * 1024 * 1024 ) )
    {
        lastPrintSize = totalMallocSize_;
        qDebug() << "JQMemoryPool::makeNode: totalMallocSize:" << ( totalMallocSize_ / 1024 / 1024 ) << "MB";
    }

    auto buffer = malloc( sizeof( JQMemoryPoolNodeHead ) + requestSize + 100 );
    auto node = reinterpret_cast< JQMemoryPoolNodeHead * >( buffer );

    node->flag = 0x3519;
    node->mallocThread = QThread::currentThread();
    node->mallocTime = QDateTime::currentMSecsSinceEpoch();
    node->requestSize = requestSize;
    node->memory = reinterpret_cast< qint8 * >( buffer ) + sizeof( JQMemoryPoolNodeHead );

    return *node;
}
