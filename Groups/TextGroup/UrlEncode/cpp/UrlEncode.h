#ifndef __GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H__
#define __GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define URLENCODE_INITIALIZA                                                     \
{                                                                               \
    qmlRegisterType<UrlEncode::Manage>("UrlEncode", 1, 0, "UrlEncodeManage");   \
}

namespace UrlEncode
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString encode(const QString &string);

    QString decode(const QString &string);
};

}

#endif//__GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H__
