#ifndef __GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__
#define __GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__

// C++ lib import
#include <functional>

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

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
    QString optimizePng(const bool &coverOldFile);

    void startOptimize(const QString &currentFileName);

signals:
    void optimizeStart(const QJsonArray fileList);

    void optimizePngStart(const QString currentFileName);

    void optimizePngFinish(const QString currentFileName, const QJsonObject optimizeResult);

    void optimizeEnd();

private:
    QMap< QString, std::function< void() > > waitOptimizeQueue_; // fileName -> package
};

}

#endif//__GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__
