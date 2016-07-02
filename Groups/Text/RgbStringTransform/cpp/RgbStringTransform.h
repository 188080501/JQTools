#ifndef __RgbStringTransform_h__
#define __RgbStringTransform_h__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define RGBSTRINGTRANSFORM_INITIALIZA                                                                    \
{                                                                                                       \
    qmlRegisterType<RgbStringTransform::Manage>("RgbStringTransform", 1, 0, "RgbStringTransformManage");\
}

namespace RgbStringTransform
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString getHexStringFromColorName(const QString &colorName);

    QString getHexString(const QString &red, const QString &green, const QString &blue);

    QString getRed(const QString &hexString);

    QString getGreen(const QString &hexString);

    QString getBlue(const QString &hexString);
};

}

#endif//__RgbStringTransform_h__
