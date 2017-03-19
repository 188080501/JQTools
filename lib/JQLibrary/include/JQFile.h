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

#ifndef __JQFile_h__
#define __JQFile_h__

// C++ lib import
#include <functional>

// Qt lib import
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

namespace JQFile
{

void foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool &recursion = false);

void foreachDirectoryFromDirectory(const QDir &directory, const std::function<void(const QDir &)> &each, const bool &recursion = false);

bool writeFile(const QFileInfo &targetFilePath, const QByteArray &data, const bool &cover = true);

QPair<bool, QByteArray> readFile(const QFileInfo &filePath);

bool copyFile(const QFileInfo &sourcePath, const QFileInfo &targetPath, const bool &cover = true);

bool copyDirectory(const QDir &sourceDirectory, const QDir &targetDirectory, const bool &cover = true);

bool copy(const QFileInfo &source, const QFileInfo &target, const bool &cover = true);

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
bool setFileLastReadAndLastModifiedTime(const char *fileName, const quint32 &lastRead, const quint32 &lastModified);
#endif

}

#endif//__JQFile_h__
