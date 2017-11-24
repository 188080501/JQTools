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

#ifdef QT_WIDGETS_LIB
#   include <QWidget>
#   include <QLineEdit>
#   include <QTextEdit>
#   include <QLabel>
#   include <QDesktopWidget>
#   include <QAbstractButton>
#   include <QTabWidget>
#   include <QTabBar>
#   include <QTableWidget>
#   include <QTreeWidget>
#   include <QMessageBox>
#endif

// Windows lib import
#ifdef Q_OS_WIN
#   include <windows.h>
#endif

using namespace JQFoundation;

void JQFoundation::setRenderLoop()
{
#ifdef Q_OS_WIN
    qputenv( "QSG_RENDER_LOOP", "basic" );
#endif
}

QString JQFoundation::hashString(const QString &key, const QCryptographicHash::Algorithm &algorithm)
{
    return hashString(key.toLatin1(), algorithm);
}

QString JQFoundation::hashString(const QByteArray &key, const QCryptographicHash::Algorithm &algorithm)
{
    return QCryptographicHash::hash( key, algorithm ).toHex();
}

QString JQFoundation::hashStringWithSalt(const QString &key)
{
    if ( key.isEmpty() )
    {
        return "1234567890123456789012345678901234567890";
    }

    const auto &&buf1( QString( "%1(%2)%3.%4" ).
        arg( key.size() ).
        arg( key).
        arg( key.size() ).
        arg( QString().append( key.at( 0 ) ) ) );
    const auto &&buf2( JQFoundation::hashString( buf1 + "Sha1", QCryptographicHash::Sha1) );
    const auto &&buf3( JQFoundation::hashString( buf1 + "Md5", QCryptographicHash::Md5) );
    const auto &&buf4( JQFoundation::hashString( buf3 + "Sha1", QCryptographicHash::Sha1) );
    const auto &&buf5( JQFoundation::hashString( buf2 + "Md5", QCryptographicHash::Md5) );
    const auto &&buf6( JQFoundation::hashString( buf4 + "+" + buf5, QCryptographicHash::Sha1) );

    return buf6;
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
            qDebug() << "JQFoundation::variantToString: unexpected type:" << value;
            result = value.toString();
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

QSharedPointer< QTimer > JQFoundation::setTimerCallback(const int &interval, const std::function<void (const QPointer< QTimer > &)> &callback, const bool &callbackOnStart)
{
    QSharedPointer< QTimer > timer( new QTimer );

    QObject::connect( timer.data(), &QTimer::timeout, [ timer, callback ]()
    {
        callback( { timer.data() } );
        timer->start();
    } );

    timer->setInterval( interval );
    timer->setSingleShot( true );

    if ( callbackOnStart )
    {
        callback( { timer.data() } );
    }

    timer->start();

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

#ifdef Q_OS_WIN
void JQFoundation::openDebugConsole()
{
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
}
#endif

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

QString JQFoundation::byteArrayToHexString(const QByteArray &data)
{
    QString buf( data.toHex() );

    for ( auto c = 1; c < data.size(); ++c )
    {
        buf.insert( c * 2 + c - 1, ' ' );
    }

    return buf;
}

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
    QByteArray bytes;
    QBuffer buffer( &bytes );

    buffer.open( QIODevice::WriteOnly );
    image.save( &buffer, format.toLatin1().data(), quality );

    return bytes;
}

QPixmap JQFoundation::byteArrayToPixmap(const QByteArray &byteArray)
{
    QPixmap Pixmap;

    Pixmap.loadFromData(byteArray);

    return Pixmap;
}

#if ( ( defined Q_OS_MAC ) && !( defined Q_OS_IOS ) ) || ( defined Q_OS_WIN ) || ( defined Q_OS_LINUX )
QPair< int, QByteArray > JQFoundation::startProcessAndReadOutput(const QString &program, const QStringList &arguments, const int &maximumTime)
{
    QPair< int, QByteArray > reply;

    QProcess process;
    process.setProgram( program );
    process.setArguments( arguments );
    process.start();

    QObject::connect( &process, (void(QProcess::*)(int))&QProcess::finished, [ &reply ](const int &exitCode)
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

#ifdef QT_WIDGETS_LIB
void JQFoundation::tableWidgetSetHorizontalHeaderLabels(QTableWidget *tableWidget, const QStringList &stringList)
{
    tableWidget->setColumnCount(stringList.size());
    tableWidget->setHorizontalHeaderLabels(stringList);
}

void JQFoundation::tableWidgetSetColumnWidth(QTableWidget *tableWidget, const QVector<int> &columnWidth)
{
    int column = -1;
    foreach (auto &&now, columnWidth)
    {
        tableWidget->setColumnWidth(++column, now);
    }
}

void JQFoundation::tableWidgetAddString(QTableWidget *tableWidget, const QStringList &stringList)
{
    int x = 0, y = tableWidget->rowCount();
    tableWidget->setRowCount(y + 1);
    QTableWidgetItem *item;

    foreach (QString Now, stringList)
    {
        item = new QTableWidgetItem(Now);
        item->setSelected(false);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        tableWidget->setItem(y, x++, item);
    }
}

void JQFoundation::treeWidgetSetHorizontalHeaderLabels(QTreeWidget *treeWidget, const QStringList &stringList)
{
    treeWidget->setColumnCount(stringList.size());
    treeWidget->setHeaderLabels(stringList);
}

void JQFoundation::treeWidgetSetColumnWidth(QTreeWidget *treeWidget, const QVector<int> &columnWidth)
{
    int column = -1;
    foreach (auto &&now, columnWidth)
    {
        ++column;
        if (now > 0)
        {
            treeWidget->setColumnWidth(column, now);
        }
        else if (!now)
        {
            continue;
        }
        else
        {
            treeWidget->setColumnWidth(column, treeWidget->headerItem()->text(column).size() * abs(now));
        }
    }
}

void JQFoundation::setWidgetColor(QWidget *label, const QColor &color)
{
    QPalette palette;
    palette.setColor(QPalette::WindowText, color);
    label->setPalette(palette);
}

void JQFoundation::texetEditMoveCursorToEnd(QTextEdit *textEdit)
{
    QTextCursor cursor = textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    textEdit->setTextCursor(cursor);
}

void JQFoundation::textEditAppendTextToEnd(QTextEdit *textEdit, const QString &string)
{
    textEdit->append(string);
    JQFoundation::texetEditMoveCursorToEnd(textEdit);
}

QWidget *JQFoundation::topParentWidget(QWidget *widget)
{
    QWidget *parent = widget;

    while ( parent->parentWidget() )
    {
        parent = parent->parentWidget();
    }

    return parent;
}

const QWidget *JQFoundation::topParentWidget(const QWidget *widget)
{
    QWidget const *parent = widget;

    while (parent->parentWidget())
    {
        parent = parent->parentWidget();
    }

    return parent;
}

void JQFoundation::lineEditSetToIPLineEdit(QLineEdit *lineEdit)
{
    lineEdit->setValidator( new QRegExpValidator( QRegExp( "^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])[.](\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])[.](\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])[.](\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$" ) ) );
}

void JQFoundation::lineEditSetToazAZ09LineEdit(QLineEdit *lineEdit)
{
    lineEdit->setValidator( new QRegExpValidator( QRegExp( "[0-9a-zA-Z]+" ) ) );
}

void JQFoundation::lineEditSetTo09LineEdit(QLineEdit *lineEdit)
{
    lineEdit->setValidator( new QRegExpValidator( QRegExp( "[0-9]+" ) ) );
}

void JQFoundation::widgetSetToTransparent(QWidget *target)
{
    target->setAttribute( Qt::WA_TranslucentBackground, true );
    target->setAttribute( Qt::WA_NoSystemBackground, false );
    target->setWindowFlags( Qt::FramelessWindowHint );
    target->setStyleSheet( target->styleSheet() + QString( "\nQWidget#%1 { background-color: transparent; }" ).arg( target->objectName() ) );
    target->setUpdatesEnabled( true );
}
#endif
