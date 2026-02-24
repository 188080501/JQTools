/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H_
#define GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define TIMESTAMPTRANSFORM_INITIALIZA                                                                        \
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
    QString currentSecondsTimestampString();

    QString currentMillisecondsTimestampString();

    QString currentDateTimeString();

    QString dateTimeStringFromTimestampString(const QString &timestampString);

    QString timestampStringFromDateTimeString(
            const QString &dateTimeString,
            const bool milliseconds
        );
};

}

#endif//GROUP_CALCULATEGROUP_TIMESTAMPTRANSFORM_CPP_TIMESTAMPTRANSFORM_H_
