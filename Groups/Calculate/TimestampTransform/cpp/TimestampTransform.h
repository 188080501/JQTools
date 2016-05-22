#ifndef __TimestampTransform_h__
#define __TimestampTransform_h__

// Qt lib import
#include <QObject>

#define TTIMESTAMPTRANSFORMINITIALIZA                                                                       \
{                                                                                                           \
    qmlRegisterType<TimestampTransform::Manage>("TimestampTransform", 1, 0, "TimestampTransformManage");    \
}

namespace TimestampTransform
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString currentDateTimeTimestampString();

    QString dateTimeStringFromTimestampString(const QString &timestampString);

    QString clipboardText();

    void setClipboardText(const QString &string);
};

}

#endif//__TimestampTransform_h__
