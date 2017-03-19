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

using namespace JQFile;

void JQFile::foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool &recursion)
{
    for (const auto &now: directory.entryInfoList(QDir::Files))
    {
        each(now);
    }

    if (recursion)
    {
        for (const auto &now: directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot))
        {
            JQFile::foreachFileFromDirectory(now.filePath(), each, recursion);
        }
    }
}

void JQFile::foreachDirectoryFromDirectory(const QDir &directory, const std::function<void (const QDir &)> &each, const bool &recursion)
{
    for (const auto &now: directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot))
    {
        each(now.filePath());
    }

    if (recursion)
    {
        for (const auto &now: directory.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot))
        {
            JQFile::foreachDirectoryFromDirectory(now.filePath(), each, recursion);
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

QPair<bool, QByteArray> JQFile::readFile(const QFileInfo &filePath)
{
    QFile file(filePath.filePath());

    if (!file.open(QIODevice::ReadOnly)) { return { false, "Open file error" }; }

    return { true, file.readAll() };
}

bool JQFile::copyFile(const QFileInfo &sourcePath, const QFileInfo &targetPath, const bool &cover)
{
    if (sourcePath.filePath()[sourcePath.filePath().size() - 1] == '/')
    {
        return false;
    }

    if (targetPath.filePath()[targetPath.filePath().size() - 1] == '/')
    {
        return false;
    }

    if (!targetPath.dir().isReadable())
    {
        if (!QDir().mkpath(targetPath.path()))
        {
            return false;
        }
    }

    if (targetPath.isFile())
    {
        if (!cover)
        {
            return false;
        }
        else
        {
            if (!QFile(targetPath.filePath()).remove())
            {
                return false;
            }
        }
    }

    return QFile::copy(sourcePath.filePath(), targetPath.filePath());
}

bool JQFile::copyDirectory(const QDir &sourceDirectory, const QDir &targetDirectory, const bool &cover)
{
    try
    {
        JQFile::foreachFileFromDirectory(sourceDirectory, [&](const QFileInfo &info)
        {
            const auto &&path = info.path().mid(sourceDirectory.path().size());
            if (!JQFile::copyFile(info, targetDirectory.path() + "/" + ((path.isEmpty()) ? ("") : (path + "/")) + info.fileName(), cover))
            {
                throw false;
            }
        }, true);
    }
    catch(const bool &error)
    {
        return error;
    }

    return true;
}

bool JQFile::copy(const QFileInfo &source, const QFileInfo &target, const bool &cover)
{
    if (source.isFile())
    {
        return JQFile::copyFile(source, target, cover);
    }
    else if (source.isDir())
    {
        return JQFile::copyDirectory(QDir(source.filePath()), QDir(target.filePath()), cover);
    }

    return false;
}

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
bool JQFile::setFileLastReadAndLastModifiedTime(const char *fileName, const quint32 &lastRead, const quint32 &lastModified)
{
    utimbuf buf( { (time_t)lastRead, (time_t)lastModified } );
    return !utime(fileName, &buf);
}
#endif
