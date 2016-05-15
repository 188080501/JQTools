#ifndef __Utf16Transform_h__
#define __Utf16Transform_h__

// Qt lib import
#include <QObject>

#define UTF16TRANSFORMINITIALIZA                                                                \
{                                                                                               \
    qmlRegisterType<Utf16Transform::Manage>("Utf16Transform", 1, 0, "Utf16TransformManage");    \
}

namespace Utf16Transform
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage();

public slots:
    QString toUtf16(const QString &string);

    QString fromUtf16(const QString &string);

    QString clipboardText();

    void setClipboardText(const QString &string);
};

}

#endif//__Utf16Transform_h__
