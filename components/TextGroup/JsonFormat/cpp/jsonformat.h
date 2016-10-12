/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TEXTGROUP_JSONFORMAT_CPP_JSONFORMAT_H__
#define __GROUP_TEXTGROUP_JSONFORMAT_CPP_JSONFORMAT_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define JSONFORMAT_INITIALIZA                                                       \
{                                                                                   \
    qmlRegisterType<JsonFormat::Manage>("JsonFormat", 1, 0, "JsonFormatManage");    \
}

namespace JsonFormat
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    bool check(const QString &string);

    QString format(const QString &string, const bool &compact);
};

}

#endif//__GROUP_TEXTGROUP_JSONFORMAT_CPP_JSONFORMAT_H__
