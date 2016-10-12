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

#ifndef __JQFilePack_h__
#define __JQFilePack_h__

// C lib import
#include "utime.h"

// C++ lib import
#include "JQFile.h"

// Qt lib import
#include <QJsonObject>
#include <QJsonDocument>
#include <QDateTime>
#include <QBuffer>

namespace JQFilePack
{

enum ErrorEnum
{
    NoError,
    SourceFileError,
    TargetDirError,
    TargetFileOpenError,
    SourceFileOpenError,
    PackDataError
};

struct FileNode
{
    QString fullFilePath;
    QString relativelyFilePath;
    union
    {
        struct
        {
            quint32 lastRead;
            quint32 lastModified;
            quint32 originalFileSize;
            quint32 currentFileSize;
            quint32 permissions;
            quint8 retention[10];
        };
        quint8 flags[30];
    };

    FileNode(const QString &fullFilePath = QString(),
             const QString &relativelyFilePath = QString(),
             const quint32 &lastRead = 0, const quint32 &lastModified = 0,
             const quint32 &originalFileSize = 0, const quint32 &currentFileSize = 0,
             const quint32 &permissions = 0);
};

QPair< int, qint64 > getFileTotalAndSizeTotalFromFile(const QFileInfo &file);

QPair< bool, ErrorEnum > pack(const QFileInfoList &sources, QIODevice &targetDevice,
                              const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor = NULL,
                              const int &progressMonitorMinimumInterval = 100);

QPair< bool, ErrorEnum > pack(const QFileInfoList &sources, const QFileInfo &targetFilePath,
                              const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor = NULL,
                              const int &progressMonitorMinimumInterval = 100);

QPair< bool, ErrorEnum > pack(const QFileInfoList &sources, QByteArray &targetBuffer,
                              const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &cusrrentFile) > &progressMonitor = NULL,
                              const int &progressMonitorMinimumInterval = 100);

QPair< bool, ErrorEnum > unpack(QIODevice &sourceDeivce, const QFileInfo &targetDir,
                                const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor = NULL,
                                const int &progressMonitorMinimumInterval = 100);

QPair< bool, ErrorEnum > unpack(const QFileInfo &sourceFilePath, const QFileInfo &targetDir,
                                const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor = NULL,
                                const int &progressMonitorMinimumInterval = 100);

QPair< bool, ErrorEnum > unpack(const QByteArray &sourceBuffer, const QFileInfo &targetDir,
                                const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor = NULL,
                                const int &progressMonitorMinimumInterval = 100);

}

#endif//__JQFilePack_h__
