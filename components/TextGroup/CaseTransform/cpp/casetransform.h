/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TEXTGROUP_CASETRANSFORM_CPP_CASETRANSFORM_H__
#define __GROUP_TEXTGROUP_CASETRANSFORM_CPP_CASETRANSFORM_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define CASETRANSFORM_INITIALIZA                                                             \
{                                                                                           \
    qmlRegisterType<CaseTransform::Manage>("CaseTransform", 1, 0, "CaseTransformManage");   \
}

namespace CaseTransform
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString upper(const QString &string);

    QString lower(const QString &string);
};

}

#endif//__GROUP_TEXTGROUP_CASETRANSFORM_CPP_CASETRANSFORM_H__
