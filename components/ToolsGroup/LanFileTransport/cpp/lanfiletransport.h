/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
#define __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__

// Qt lib import
#include <QJsonObject>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define LANFILETRANSPORT_INITIALIZA                                                             \
{                                                                                               \
    qmlRegisterType<LanFileTransport::Manage>("LanFileTransport", 1, 0, "LanFileTransportManage"); \
}

namespace LanFileTransport
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;
};

}

#endif//__GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
