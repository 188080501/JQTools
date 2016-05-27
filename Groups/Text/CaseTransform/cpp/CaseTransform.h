#ifndef __CaseTransform_h__
#define __CaseTransform_h__

// Qt lib import
#include <QObject>

#define CASETRANSFORM_INITIALIZA                                                             \
{                                                                                           \
    qmlRegisterType<CaseTransform::Manage>("CaseTransform", 1, 0, "CaseTransformManage");   \
}

namespace CaseTransform
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString upper(const QString &string);

    QString lower(const QString &string);

    QString clipboardText();

    void setClipboardText(const QString &string);
};

}

#endif//__CaseTransform_h__
