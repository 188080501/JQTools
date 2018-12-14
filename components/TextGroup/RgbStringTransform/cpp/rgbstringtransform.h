/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_RGBSTRINGTRANSFORM_CPP_RGBSTRINGTRANSFORM_H_
#define GROUP_TEXTGROUP_RGBSTRINGTRANSFORM_CPP_RGBSTRINGTRANSFORM_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

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
    QString getHexString(QColor color);

    QString getRed(const QString &hexString);

    QString getGreen(const QString &hexString);

    QString getBlue(const QString &hexString);
};

}

#endif//GROUP_TEXTGROUP_RGBSTRINGTRANSFORM_CPP_RGBSTRINGTRANSFORM_H_
