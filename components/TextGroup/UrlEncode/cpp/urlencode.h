/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H_
#define GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define URLENCODE_INITIALIZA                                                    \
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
    QString encode(const QString &string, const QString &exclude);

    QString decode(const QString &string);
};

}

#endif//GROUP_TEXTGROUP_URLENCODE_CPP_URLENCODE_H_
