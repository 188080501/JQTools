/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TOOLSGROUP_JPGOPTIMIZE_CPP_JPGOPTIMIZE_H__
#define __GROUP_TOOLSGROUP_JPGOPTIMIZE_CPP_JPGOPTIMIZE_H__

// C++ lib import
#include <functional>

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define JPGOPTIMIZE_INITIALIZA                                                      \
{                                                                                   \
    qmlRegisterType<JpgOptimize::Manage>("JpgOptimize", 1, 0, "JpgOptimizeManage"); \
}

namespace JpgOptimize
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString optimizeJpgByFilePaths(const bool &coverOldFile, const QJsonArray &filePaths);

    QString optimizeJpgByOpenFiles(const bool &coverOldFile);

    QString optimizeJpgByOpenDirectory(const bool &coverOldFile);

    void startOptimize(const QString &currentFilePath);

    QString urlToLocalPngOrJpgFilePath(const QVariant &url);

private:
    QString optimizeJpg(const bool &coverOldFile, const QStringList &filePaths);

signals:
    void optimizeStart(const QJsonArray fileList);

    void optimizeJpgStart(const QString currentFilePath);

    void optimizeJpgFinish(const QString currentFilePath, const QJsonObject optimizeResult);

    void optimizeEnd();

private:
    QMap< QString, std::function< void() > > waitOptimizeQueue_; // fileName -> package
};

}

#endif//__GROUP_TOOLSGROUP_JPGOPTIMIZE_CPP_JPGOPTIMIZE_H__
