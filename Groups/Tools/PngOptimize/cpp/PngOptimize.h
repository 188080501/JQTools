#ifndef __GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__
#define __GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>

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

signals:
    void optimizeStart(const QJsonArray fileList);

    void optimizePngFinish(const QString currentFileName, const QJsonObject optimizeResult);

    void optimizeEnd();
};

}

#endif//__GROUP_TOOLS_PNGOPTIMIZE_CPP_PNGOPTIMIZE_H__
