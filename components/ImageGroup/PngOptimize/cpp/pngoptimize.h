/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TOOLSGROUP_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H_
#define GROUP_TOOLSGROUP_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define PNGOPTIMIZE_INITIALIZA                                                      \
{                                                                                   \
    qmlRegisterType<PngOptimize::Manage>("PngOptimize", 1, 0, "PngOptimizeManage"); \
}

namespace PngOptimize
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString optimizePngByFilePaths(const bool &coverOldFile, const QJsonArray &filePaths);

    QString optimizePngByOpenFiles(const bool &coverOldFile);

    QString optimizePngByOpenDirectory(const bool &coverOldFile);

    void startOptimize(const QString &currentFilePath);

    QString urlToLocalPngFilePath(const QVariant &url);

private:
    QString optimizePng(const bool &coverOldFile, const QStringList &filePaths);

signals:
    void optimizeStart(const QJsonArray fileList);

    void optimizePngStart(const QString currentFilePath);

    void optimizePngFinish(const QString currentFilePath, const QJsonObject optimizeResult);

    void optimizeEnd();

private:
    QMap< QString, std::function< void() > > waitOptimizeQueue_; // fileName -> package
};

}

#endif//GROUP_TOOLSGROUP_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H_
