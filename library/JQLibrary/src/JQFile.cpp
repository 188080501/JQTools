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

QPair< bool, QByteArray > JQFile::readFile(const QFileInfo &filePath)
{
    QFile file( filePath.filePath() );

    if ( !file.open( QIODevice::ReadOnly ) ) { return { false, { } }; }

    return { true, file.readAll() };
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
