/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_STRINGSORT_CPP_STRINGSORT_H_
#define GROUP_TEXTGROUP_STRINGSORT_CPP_STRINGSORT_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define STRINGSORT_INITIALIZA                                                       \
{                                                                                   \
    qmlRegisterType<StringSort::Manage>("StringSort", 1, 0, "StringSortManage");    \
}

namespace StringSort
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString sort(const QString &string, const bool &descOrder);
};

}

#endif//GROUP_TEXTGROUP_STRINGSORT_CPP_STRINGSORT_H_
