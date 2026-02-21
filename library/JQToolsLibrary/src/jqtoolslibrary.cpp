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
#include <QFileInfo>
#include <QLocale>
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
