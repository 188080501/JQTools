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

#include "JQFilePack.h"

// Qt lib import
#include <QDebug>

using namespace JQFilePack;

FileNode::FileNode(const QString &fullFilePath_,
                   const QString &filePath_,
                   const quint32 &lastRead_, const quint32 &lastModified_,
                   const quint32 &originalFileSize_, const quint32 &currentFileSize_,
                   const quint32 &permissions_)
{
    memset(flags, 0, sizeof(flags));

    fullFilePath = fullFilePath_;
    relativelyFilePath = filePath_;
    lastRead = lastRead_;
    lastModified = lastModified_;
    originalFileSize = originalFileSize_;
    currentFileSize = currentFileSize_;
    permissions = permissions_;
}

QPair<int, qint64> JQFilePack::getFileTotalAndSizeTotalFromFile(const QFileInfo &file_)
{
    QFile file(file_.filePath());
    if (!file.open(QIODevice::ReadOnly)) { return { 0, 0 }; }

    auto information(QJsonDocument::fromJson(file.readLine()).object());

    if (!information.contains("fileTotal") || !information.contains("sizeTotal")) { return { 0, 0 }; }

    return { information["fileTotal"].toInt(), information["sizeTotal"].toString().toLongLong() };
}

QPair< bool, ErrorEnum > JQFilePack::pack(const QFileInfoList &sources, QIODevice &targetDevice,
                                                const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor,
                                                const int &progressMonitorMinimumInterval)
{
    int fileIndex = 0, fileTotal = 0;
    qint64 sizeIndex = 0, sizeTotal = 0, timeFlag = 0;

    // Ready source files
    QVector< FileNode > sourceFiles;

    for (const auto &source: sources)
    {
        if (source.isDir())
        {
            const auto &sourceDirLength = source.path().size();

            JQFile::foreachFileFromDirectory(source.filePath(), [&](const QFileInfo &fileInfo)
            {
                sizeTotal += fileInfo.size();
                sourceFiles.push_back( {
                                           fileInfo.filePath(),
                                           fileInfo.filePath().mid(sourceDirLength),
                                           fileInfo.lastRead().toTime_t(),
                                           fileInfo.lastModified().toTime_t(),
                                           0,
                                           0
                                       } );
            }, true);
            fileTotal += sourceFiles.size();
        }
        else if (source.isFile())
        {
            sizeTotal += source.size();
            sourceFiles.push_back( {
                                       source.filePath(),
                                       "/" + source.fileName(),
                                       source.lastRead().toTime_t(),
                                       source.lastModified().toTime_t(),
                                       0,
                                       0
                                   } );
            fileTotal++;
        }
    }

    // Write information
    QJsonObject information;

    information["version"] = 1;
    information["fileTotal"] = sourceFiles.size();
    information["sizeTotal"] = QString::number(sizeTotal);

    targetDevice.write(QJsonDocument(information).toJson(QJsonDocument::Compact));
    targetDevice.write("\n");

    // Write file
    QByteArray fileDataBuf;

    for (auto &node: sourceFiles)
    {
        QFile file(node.fullFilePath);
        if (!file.open(QIODevice::ReadOnly)) { return { false, SourceFileOpenError }; }

        fileDataBuf = file.readAll();
        file.close();

        sizeIndex += fileDataBuf.size();

        node.originalFileSize = fileDataBuf.size();
        node.currentFileSize = fileDataBuf.size();
        node.permissions = file.permissions();

        targetDevice.write((const char *)node.flags, sizeof(node.flags));
        targetDevice.write(node.relativelyFilePath.toUtf8());
        targetDevice.write("\n");

        targetDevice.write(fileDataBuf);


        if (progressMonitor)
        {
            if (progressMonitorMinimumInterval != -1)
            {
                const auto &&currentTime = QDateTime::currentMSecsSinceEpoch();
                if ((currentTime - timeFlag) > progressMonitorMinimumInterval)
                {
                    timeFlag = currentTime;
                    progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, node.relativelyFilePath);
                }
            }
            else
            {
                progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, node.relativelyFilePath);
            }
        }

        fileIndex++;


        if (!(fileIndex % 200))
        {
            targetDevice.waitForBytesWritten(30 * 1000);
        }
    }

    if (progressMonitor)
    {
        progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, "");
    }

    targetDevice.waitForBytesWritten(30 * 1000);

    return { true, NoError };
}

QPair< bool, ErrorEnum > JQFilePack::pack(const QFileInfoList &sources, const QFileInfo &targetFilePath,
                                                const std::function<void (const int &, const int &, const qint64 &, const qint64 &, const QString &)> &progressMonitor,
                                                const int &progressMonitorMinimumInterval)
{
    // Ready target file
    QFile targetFile(targetFilePath.filePath());

    if (!targetFile.open(QIODevice::WriteOnly)) { return { false, TargetFileOpenError }; }
    targetFile.resize(0);

    return JQFilePack::pack(sources, targetFile, progressMonitor, progressMonitorMinimumInterval);
}

QPair< bool, ErrorEnum > JQFilePack::pack(const QFileInfoList &sources, QByteArray &targetBuffer,
                                                const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor,
                                                const int &progressMonitorMinimumInterval)
{
    QBuffer buffer(&targetBuffer);

    buffer.open(QIODevice::Append);

    return JQFilePack::pack(sources, buffer, progressMonitor, progressMonitorMinimumInterval);
}

QPair< bool, ErrorEnum > JQFilePack::unpack(QIODevice &sourceDeivce, const QFileInfo &targetDir,
                                                  const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor,
                                                  const int &progressMonitorMinimumInterval)
{
    int fileIndex = 0, fileTotal = 0;
    qint64 sizeIndex = 0, sizeTotal = 0, timeFlag = 0;

    // Read information
    auto information(QJsonDocument::fromJson(sourceDeivce.readLine()).object());

    if (!information.contains("fileTotal") || !information.contains("sizeTotal")) { return { false, PackDataError }; }

    auto filePathBase = targetDir.filePath() + "/" + information["dirName"].toString();

    fileTotal = information["fileTotal"].toInt();
    sizeTotal = information["sizeTotal"].toString().toLongLong();

    // Write files
    FileNode node;
    QByteArray buf;

    while (!sourceDeivce.atEnd())
    {
        buf = sourceDeivce.read(sizeof(node.flags));
        memcpy(node.flags, buf.data(), sizeof(node.flags));

        sizeIndex += node.currentFileSize;

        node.relativelyFilePath = sourceDeivce.readLine();
        node.relativelyFilePath.remove(node.relativelyFilePath.size() - 1, 1);

        buf = sourceDeivce.read(node.currentFileSize);

        const auto &&fullFilePath = filePathBase + node.relativelyFilePath;

        if (progressMonitor)
        {
            if (progressMonitorMinimumInterval != -1)
            {
                const auto &&currentTime = QDateTime::currentMSecsSinceEpoch();
                if ((currentTime - timeFlag) > progressMonitorMinimumInterval)
                {
                    timeFlag = currentTime;
                    progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, node.relativelyFilePath);
                }
            }
            else
            {
                progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, node.relativelyFilePath);
            }
        }

        fileIndex++;


        JQFile::writeFile(fullFilePath, buf);
        QFile::setPermissions(fullFilePath, (QFile::Permissions)node.permissions);

        JQFile::setFileLastReadAndLastModifiedTime(fullFilePath.toLatin1().data(), node.lastRead, node.lastModified);
    }

    if (progressMonitor)
    {
        progressMonitor(fileIndex, fileTotal, sizeIndex, sizeTotal, "");
    }

    return { true, NoError };
}

QPair< bool, ErrorEnum > JQFilePack::unpack(const QFileInfo &sourceFilePath, const QFileInfo &targetDir,
                                                  const std::function< void(const int &, const int &, const qint64 &, const qint64 &, const QString &) > &progressMonitor,
                                                  const int &progressMonitorMinimumInterval)
{
    if (!sourceFilePath.isFile()) { return { false, SourceFileError }; }

    // Ready source file
    QFile sourceFile(sourceFilePath.filePath());

    if (!sourceFile.open(QIODevice::ReadOnly)) { return { false, SourceFileOpenError }; }

    return JQFilePack::unpack(sourceFile, targetDir, progressMonitor, progressMonitorMinimumInterval);
}

QPair< bool, ErrorEnum > JQFilePack::unpack(const QByteArray &sourceBuffer, const QFileInfo &targetDir,
                                                  const std::function< void(const int &fileIndex, const int &fileTotal, const qint64 &sizeIndex, const qint64 &sizeTotal, const QString &currentFile) > &progressMonitor,
                                                  const int &progressMonitorMinimumInterval)
{
    QBuffer buffer((QByteArray *)&sourceBuffer);

    buffer.open(QIODevice::ReadOnly);

    return JQFilePack::unpack(buffer, targetDir, progressMonitor, progressMonitorMinimumInterval);
}
