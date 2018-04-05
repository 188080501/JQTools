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

#ifndef JQLIBRARY_INCLUDE_JQFILE_H_
#define JQLIBRARY_INCLUDE_JQFILE_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QByteArray>
#include <QPair>
#include <QDir>

class QFileInfo;
class QDir;

class JQFile
{
public:
    static void foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool &recursion = false);

    static bool foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &, bool &)> &each, const bool &recursion = false);

    static void foreachDirectoryFromDirectory(const QDir &directory, const std::function<void(const QDir &)> &each, const bool &recursion = false);

    static bool writeFile(const QFileInfo &targetFilePath, const QByteArray &data, const bool &cover = true);

    static QPair< bool, QByteArray > readFile(const QFileInfo &filePath);

    static bool copyFile(const QFileInfo &sourceFileInfo, const QFileInfo &targetFileInfo, const bool &cover = true);

    static bool copyDirectory(const QDir &sourceDirectory, const QDir &targetDirectory, const bool &cover = true);

    static bool copy(const QFileInfo &source, const QFileInfo &target, const bool &cover = true);

    static QString md5(const QFileInfo &fileInfo);

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
    static bool setFileLastReadAndLastModifiedTime(const char *fileName, const quint32 &lastRead, const quint32 &lastModified);
#endif
};

#endif//JQLIBRARY_INCLUDE_JQFILE_H_
