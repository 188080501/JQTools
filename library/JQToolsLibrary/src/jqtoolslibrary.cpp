/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "jqtoolslibrary.h"

// Qt lib import
#include <QApplication>
#include <QClipboard>
#include <QDate>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QLocale>
#include <QSettings>
#include <QStandardPaths>
#include <QDebug>

void AbstractTool::foreachFileFromDirectory(
        const QDir &directory,
        const std::function< void(const QFileInfo &) > &each,
        const bool recursion
    )
{
    for ( const auto &fileInfo: directory.entryInfoList( QDir::Files ) )
    {
        each( fileInfo );
    }

    if ( recursion )
    {
        for ( const auto &fileInfo: directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) )
        {
            AbstractTool::foreachFileFromDirectory( fileInfo.filePath(), each, recursion );
        }
    }
}

void AbstractTool::foreachDirectoryFromDirectory(
        const QDir &directory,
        const std::function< void(const QDir &) > &each,
        const bool recursion
    )
{
    for ( const auto &fileInfo: directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) )
    {
        each( fileInfo.filePath() );
    }

    if ( recursion )
    {
        for ( const auto &fileInfo: directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) )
        {
            AbstractTool::foreachDirectoryFromDirectory( fileInfo.filePath(), each, recursion );
        }
    }
}

bool AbstractTool::writeFile(
        const QFileInfo &targetFilePath,
        const QByteArray &data,
        const bool cover
    )
{
    if ( !targetFilePath.dir().isReadable() )
    {
        if ( !QDir().mkpath( targetFilePath.path() ) )
        {
            return false;
        }
    }

    if ( targetFilePath.isFile() && !cover )
    {
        return true;
    }

    QFile file( targetFilePath.filePath() );
    if ( !file.open( QIODevice::WriteOnly ) )
    {
        return false;
    }

    file.write( data );
    file.waitForBytesWritten( 15 * 1000 );

    return true;
}

QPair< bool, QByteArray > AbstractTool::readFile(const QFileInfo &filePath)
{
    QFile file( filePath.filePath() );

    if ( !file.open( QIODevice::ReadOnly ) ) { return { false, { } }; }

    return { true, file.readAll() };
}

QString AbstractTool::fileSizeString(const qint64 size)
{
    if ( size < 1024 )
    {
        return QString( "%1 Byte" ).arg( size );
    }
    else if ( size < ( 1024 * 1024 ) )
    {
        return QString( "%1 KB" ).arg( QString::number( size / 1024.0, 'f', 2 ) );
    }

    return QString( "%1 MB" ).arg( QString::number( size / 1024.0 / 1024.0, 'f', 2 ) );
}

QString AbstractTool::getDialogPath(
        const QString &dialogName,
        const QString &defaultPath
    )
{
#ifndef Q_OS_WASM
    QSettings settings( QSettings::NativeFormat, QSettings::UserScope, "JQTools", "JQTools" );
    settings.beginGroup( "dialog" );

    const auto fallbackPath = ( defaultPath.isEmpty() ) ? ( QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) ) : ( defaultPath );
    auto result = settings.value( dialogName, fallbackPath ).toString();

    // 如果初始路径存在，直接返回
    if ( QDir( result ).exists() )
    {
        return result;
    }

    QFileInfo fileInfo( result );

    // 逐级向上查找存在的父目录（包含根目录）
    while ( true )
    {
        if ( fileInfo.exists() )
        {
            return ( fileInfo.isDir() ) ? ( fileInfo.absoluteFilePath() ) : ( fileInfo.absolutePath() );
        }

        const auto parentPath = fileInfo.path();
        if ( parentPath.isEmpty() || parentPath == fileInfo.filePath() )
        {
            break;
        }

        fileInfo = QFileInfo( parentPath );
    }

    return ( QDir( fallbackPath ).exists() ) ? ( fallbackPath ) : ( QDir::homePath() );
#else
    Q_UNUSED( dialogName );
    Q_UNUSED( defaultPath );

    return { };
#endif
}

QString AbstractTool::getOpenFileName(
        const QString &dialogName,
        const QString &caption,
        const QString &filter
    )
{
#ifndef Q_OS_WASM
    const auto filePath = QFileDialog::getOpenFileName(
                nullptr,
                caption,
                AbstractTool::getDialogPath( dialogName ),
                filter
            );
    if ( filePath.isEmpty() ) { return { }; }

    QSettings settings( QSettings::NativeFormat, QSettings::UserScope, "JQTools", "JQTools" );
    settings.beginGroup( "dialog" );
    settings.setValue( dialogName, QFileInfo( filePath ).path() );

    return filePath;
#else
    Q_UNUSED( dialogName );
    Q_UNUSED( caption );
    Q_UNUSED( filter );

    return { };
#endif
}

QString AbstractTool::getExistingDirectory(
        const QString &dialogName,
        const QString &caption
    )
{
#ifndef Q_OS_WASM
    const auto dir = QFileDialog::getExistingDirectory(
                nullptr,
                caption,
                AbstractTool::getDialogPath( dialogName )
            );
    if ( dir.isEmpty() ) { return { }; }

    QSettings settings( QSettings::NativeFormat, QSettings::UserScope, "JQTools", "JQTools" );
    settings.beginGroup( "dialog" );
    settings.setValue( dialogName, dir );

    return dir;
#else
    Q_UNUSED( dialogName );
    Q_UNUSED( caption );

    return { };
#endif
}

QStringList AbstractTool::getOpenFileNames(
        const QString &dialogName,
        const QString &caption,
        const QString &filter
    )
{
#ifndef Q_OS_WASM
    const auto filePathList = QFileDialog::getOpenFileNames(
                nullptr,
                caption,
                AbstractTool::getDialogPath( dialogName ),
                filter
            );
    if ( filePathList.isEmpty() ) { return { }; }

    QSettings settings( QSettings::NativeFormat, QSettings::UserScope, "JQTools", "JQTools" );
    settings.beginGroup( "dialog" );
    settings.setValue( dialogName, QFileInfo( filePathList.first() ).path() );

    return filePathList;
#else
    Q_UNUSED( dialogName );
    Q_UNUSED( caption );
    Q_UNUSED( filter );

    return { };
#endif
}

QString AbstractTool::getSaveFileName(
        const QString &dialogName,
        const QString &caption,
        const QString &fileName,
        const QString &filter
    )
{
#ifndef Q_OS_WASM
    const auto filePath = QFileDialog::getSaveFileName(
                nullptr,
                caption,
                QDir( AbstractTool::getDialogPath( dialogName ) ).filePath( fileName ),
                filter
            );
    if ( filePath.isEmpty() ) { return { }; }

    QSettings settings( QSettings::NativeFormat, QSettings::UserScope, "JQTools", "JQTools" );
    settings.beginGroup( "dialog" );
    settings.setValue( dialogName, QFileInfo( filePath ).path() );

    return filePath;
#else
    Q_UNUSED( dialogName );
    Q_UNUSED( caption );
    Q_UNUSED( fileName );
    Q_UNUSED( filter );

    return { };
#endif
}

QString AbstractTool::jqToolsVersionString()
{
    const auto compileDateText = QStringLiteral( __DATE__ ).simplified();
    const auto compileDate = QLocale( QLocale::English ).toDate( compileDateText, "MMM d yyyy" );

    if ( compileDate.isValid() )
    {
        return compileDate.toString( "yy.M.d" );
    }

    return compileDateText;
}

QString AbstractTool::clipboardText()
{
    return qApp->clipboard()->text();
}

void AbstractTool::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
