/*
    This file is part of JQLibrary

    Copyright: Jason and others

    Contact email: 188080501@qq.com

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "JQFile.h"

// C lib import
#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
#   include <utime.h>
#endif

// Qt lib import
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QStandardPaths>
#include <QCoreApplication>

// JQLibrary lib import
#include "JQFoundation.h"

void JQFile::foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool &recursion)
{
    for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::Files ) ) )
    {
        each( fileInfo );
    }

    if ( recursion )
    {
        for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) ) )
        {
            JQFile::foreachFileFromDirectory( fileInfo.filePath(), each, recursion );
        }
    }
}

bool JQFile::foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &, bool &)> &each, const bool &recursion)
{
    bool continueFlag = true;

    for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::Files ) ) )
    {
        each( fileInfo, continueFlag );
        if ( !continueFlag ) { return false; }
    }

    if ( recursion )
    {
        for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) ) )
        {
            continueFlag = JQFile::foreachFileFromDirectory( fileInfo.filePath(), each, recursion );
            if ( !continueFlag ) { return false; }
        }
    }

    return true;
}

void JQFile::foreachDirectoryFromDirectory(const QDir &directory, const std::function<void (const QDir &)> &each, const bool &recursion)
{
    for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) ) )
    {
        each( fileInfo.filePath() );
    }

    if ( recursion )
    {
        for ( const auto &fileInfo: JQCONST( directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) ) )
        {
            JQFile::foreachDirectoryFromDirectory( fileInfo.filePath(), each, recursion );
        }
    }
}

QString JQFile::tempFilePath(const QString &fileName)
{
    if ( qApp->applicationName().isEmpty() )
    {
        return QString( "%1/%2" ).arg( QStandardPaths::writableLocation( QStandardPaths::TempLocation ), fileName );
    }
    else
    {
        return QString( "%1/%2/%3" ).arg( QStandardPaths::writableLocation( QStandardPaths::TempLocation ), qApp->applicationName(), fileName );
    }
}

bool JQFile::writeFile(const QFileInfo &targetFilePath, const QByteArray &data, const bool &cover)
{
    if ( !targetFilePath.dir().isReadable() )
    {
        if ( !QDir().mkpath( targetFilePath.path() ))
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

bool JQFile::writeFileToDesktop(const QString &fileName, const QByteArray &data, const bool &cover)
{
    return writeFile(
                { QString( "%1/%2" ).arg( QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ), fileName ) },
                data,
                cover
                );
}

bool JQFile::writeFileToTemp(const QString &fileName, const QByteArray &data, const bool &cover)
{
    const QFileInfo fileInfo( tempFilePath( fileName ) );

    if ( !QDir().exists( fileInfo.path() ) && !QDir().mkpath( fileInfo.path() ) )
    {
        return false;
    }

    return writeFile( fileInfo, data, cover );
}

bool JQFile::appendFile(const QFileInfo &targetFilePath, const QByteArray &data)
{
    if ( !targetFilePath.dir().isReadable() )
    {
        if ( !QDir().mkpath( targetFilePath.path() ))
        {
            return false;
        }
    }

    QFile file( targetFilePath.filePath() );
    if ( !file.open( QIODevice::Append ) )
    {
        return false;
    }

    file.write( data );
    file.waitForBytesWritten( 15 * 1000 );

    return true;
}

QPair< bool, QByteArray > JQFile::readFile(const QFileInfo &filePath)
{
    QFile file( filePath.filePath() );

    if ( !file.open( QIODevice::ReadOnly ) ) { return { false, { } }; }

    return { true, file.readAll() };
}

QPair< bool, QByteArray > JQFile::readFileFromDesktop(const QString &fileName)
{
    return readFile(
                { QString( "%1/%2" ).arg( QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ), fileName ) }
            );
}

QPair< bool, QByteArray > JQFile::readFileFromTemp(const QString &fileName)
{
    return readFile( tempFilePath( fileName ) );
}

bool JQFile::copyFile(const QFileInfo &sourceFileInfo, const QFileInfo &targetFileInfo, const bool &cover)
{
    const auto &&sourceFilePath = sourceFileInfo.filePath();
    const auto &&targetFilePath = targetFileInfo.filePath();

    if ( sourceFilePath.isEmpty() || ( sourceFilePath[ sourceFileInfo.filePath().size() - 1 ] == '/' ) )
    {
        return false;
    }

    if ( targetFilePath.isEmpty() || ( targetFilePath[ targetFileInfo.filePath().size() - 1 ] == '/' ) )
    {
        return false;
    }

    if ( !targetFileInfo.dir().isReadable() )
    {
        if ( !QDir().mkpath( targetFileInfo.path() ) )
        {
            return false;
        }
    }

    if ( targetFileInfo.isFile() )
    {
        if ( !cover )
        {
            return false;
        }
        else
        {
            if ( !QFile( targetFilePath ).remove() )
            {
                return false;
            }
        }
    }

    return QFile::copy( sourceFilePath, targetFilePath );
}

bool JQFile::copyFileToTemp(const QFileInfo &sourceFileInfo, const QString &fileName)
{
    if ( !sourceFileInfo.exists() ) { return false; }

    const QFileInfo tempFileInfo( tempFilePath( fileName ) );

    if ( !QDir().exists( tempFileInfo.path() ) && !QDir().mkpath( tempFileInfo.path() ) )
    {
        return false;
    }

    return QFile::copy( sourceFileInfo.filePath(), tempFileInfo.filePath() );
}

QPair< bool, QString > JQFile::copyFileToTemp(const QFileInfo &sourceFileInfo, const QCryptographicHash::Algorithm &fileNameHashAlgorithm, const QString &salt)
{
    if ( !sourceFileInfo.exists() ) { return { false, { } }; }

    const QFileInfo tempFileInfo( tempFilePath( JQFoundation::hashString( ( sourceFileInfo.filePath() + salt ).toUtf8(), fileNameHashAlgorithm ) ) );

    if ( !QDir().exists( tempFileInfo.path() ) && !QDir().mkpath( tempFileInfo.path() ) )
    {
        return { false, { } };
    }

    return { QFile::copy( sourceFileInfo.filePath(), tempFileInfo.filePath() ), tempFileInfo.filePath() };
}

bool JQFile::copyDirectory(const QDir &sourceDirectory, const QDir &targetDirectory, const bool &cover)
{
    bool(*fun)(const QDir &directory, const std::function<void(const QFileInfo &, bool &)> &each, const bool &recursion) = foreachFileFromDirectory;

    return fun( sourceDirectory, [ & ](const QFileInfo &info, bool &continueFlag)
    {
        const auto &&path = info.path().mid( sourceDirectory.path().size() );
        if ( !JQFile::copyFile( info, targetDirectory.path() + "/" + ( ( path.isEmpty() ) ? ( "" ) : ( path + "/" ) ) + info.fileName(), cover ) )
        {
            continueFlag = false;
        }
    }, true );
}

bool JQFile::copy(const QFileInfo &source, const QFileInfo &target, const bool &cover)
{
    if ( source.isFile() )
    {
        return JQFile::copyFile( source, target, cover );
    }
    else if ( source.isDir() )
    {
        return JQFile::copyDirectory( QDir( source.filePath() ), QDir( target.filePath() ), cover );
    }

    return false;
}

QString JQFile::md5(const QFileInfo &fileInfo)
{
    QFile file( fileInfo.filePath() );
    if ( !file.open( QIODevice::ReadOnly ) ) { return "00000000000000000000000000000000"; }

    return QCryptographicHash::hash( file.readAll(), QCryptographicHash::Md5 ).toHex();
}

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
bool JQFile::setFileLastReadAndLastModifiedTime(const char *fileName, const quint32 &lastRead, const quint32 &lastModified)
{
    utimbuf buf( { static_cast< time_t >( lastRead ), static_cast< time_t >( lastModified ) } );
    return !utime(fileName, &buf);
}
#endif
