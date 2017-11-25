/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_RANDOMUUID_CPP_RANDOMUUID_H_
#define GROUP_TEXTGROUP_RANDOMUUID_CPP_RANDOMUUID_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define RANDOMUUID_INITIALIZA                                                       \
{                                                                                   \
    qmlRegisterType<RandomUuid::Manage>("RandomUuid", 1, 0, "RandomUuidManage");    \
}

namespace RandomUuid
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    QString randomUuid(const bool &includeParantheses);
};

}

#endif//GROUP_TEXTGROUP_RANDOMUUID_CPP_RANDOMUUID_H_
