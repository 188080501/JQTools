#ifndef __UrlEncode_h__
#define __UrlEncode_h__

// Qt lib import
#include <QObject>

#define URLENCODE_INITIALIZA                                                     \
{                                                                               \
    qmlRegisterType<UrlEncode::Manage>("UrlEncode", 1, 0, "UrlEncodeManage");   \
}

namespace UrlEncode
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString encode(const QString &string);

    QString decode(const QString &string);

    QString clipboardText();

    void setClipboardText(const QString &string);
};

}

#endif//__UrlEncode_h__
