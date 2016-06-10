#ifndef __PngWarningRemover_h__
#define __PngWarningRemover_h__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define PNGWARNINGREMOVER_INITIALIZA                                                                     \
{                                                                                                       \
    qmlRegisterType<PngWarningRemover::Manage>("PngWarningRemover", 1, 0, "PngWarningRemoverManage");   \
}

namespace PngWarningRemover
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString conversationPng();
};

}

#endif//__PngWarningRemover_h__
