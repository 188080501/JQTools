#ifndef __CaseTransform_h__
#define __CaseTransform_h__

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

#endif//__CaseTransform_h__
