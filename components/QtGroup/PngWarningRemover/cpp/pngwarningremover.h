/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_QTGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H__
#define __GROUP_QTGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H__

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

    inline QString lastErrorFileName() { return lastErrorFileName_; }

private:
    QString lastErrorFileName_;
};

}

#endif//__GROUP_QTGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H__
