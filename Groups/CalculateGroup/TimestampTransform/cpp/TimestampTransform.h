#ifndef __GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H__
#define __GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define TTIMESTAMPTRANSFORM_INITIALIZA                                                                       \
{                                                                                                           \
    qmlRegisterType<TimestampTransform::Manage>("TimestampTransform", 1, 0, "TimestampTransformManage");    \
}

namespace TimestampTransform
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString currentDateTimeTimestampString();

    QString dateTimeStringFromTimestampString(const QString &timestampString);
};

}

#endif//__GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H__
