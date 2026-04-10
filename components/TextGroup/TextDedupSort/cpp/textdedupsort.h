/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_TEXTDEDUPSORT_CPP_TEXTDEDUPSORT_H_
#define GROUP_TEXTGROUP_TEXTDEDUPSORT_CPP_TEXTDEDUPSORT_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define TEXTDEDUPSORT_INITIALIZA                                                               \
{                                                                                              \
    qmlRegisterType<TextDedupSort::Manage>("TextDedupSort", 1, 0, "TextDedupSortManage");    \
}

namespace TextDedupSort
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString deduplicateAndSort(const QString &string, const bool outputWrap);
};

}

#endif//GROUP_TEXTGROUP_TEXTDEDUPSORT_CPP_TEXTDEDUPSORT_H_
