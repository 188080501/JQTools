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

#ifndef JQLIBRARY_INCLUDE_JQFILE_H_
#define JQLIBRARY_INCLUDE_JQFILE_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QByteArray>
#include <QPair>
#include <QDir>
#include <QCryptographicHash>

// JQLibrary lib import
#include <JQDeclare>

class QFileInfo;
class QDir;

class JQLIBRARY_EXPORT JQFile
{
public:
    static void foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &)> &each, const bool &recursion = false);

    static bool foreachFileFromDirectory(const QDir &directory, const std::function<void(const QFileInfo &, bool &)> &each, const bool &recursion = false);

    static void foreachDirectoryFromDirectory(const QDir &directory, const std::function<void(const QDir &)> &each, const bool &recursion = false);

    static QString tempFilePath(const QString &fileName);

    static bool writeFile(const QFileInfo &targetFilePath, const QByteArray &data, const bool &cover = true);

    static bool writeFileToDesktop(const QString &fileName, const QByteArray &data, const bool &cover = true);

    static bool writeFileToTemp(const QString &fileName, const QByteArray &data, const bool &cover = true);

    static bool appendFile(const QFileInfo &targetFilePath, const QByteArray &data);

    static QPair< bool, QByteArray > readFile(const QFileInfo &filePath);

    static QPair< bool, QByteArray > readFileFromDesktop(const QString &fileName);

    static QPair< bool, QByteArray > readFileFromTemp(const QString &fileName);

    static bool copyFile(const QFileInfo &sourceFileInfo, const QFileInfo &targetFileInfo, const bool &cover = true);

    static bool copyFileToTemp(const QFileInfo &sourceFileInfo, const QString &fileName);

    static QPair< bool, QString > copyFileToTemp(const QFileInfo &sourceFileInfo, const QCryptographicHash::Algorithm &fileNameHashAlgorithm = QCryptographicHash::Sha1, const QString &salt = "");

    static bool copyDirectory(const QDir &sourceDirectory, const QDir &targetDirectory, const bool &cover = true);

    static bool copy(const QFileInfo &source, const QFileInfo &target, const bool &cover = true);

    static QString md5(const QFileInfo &fileInfo);

#if ( defined Q_OS_MAC ) || ( defined __MINGW32__ ) || ( defined Q_OS_LINUX )
    static bool setFileLastReadAndLastModifiedTime(const char *fileName, const quint32 &lastRead, const quint32 &lastModified);
#endif
};

#endif//JQLIBRARY_INCLUDE_JQFILE_H_
