/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "rgbstringtransform.h"

// Qt lib import
#include <QColor>

using namespace RgbStringTransform;

QString Manage::getHexStringFromColorName(const QString &colorName)
{
    return QColor( colorName ).name();
}

QString Manage::getHexString(const QString &red, const QString &green, const QString &blue)
{
    QColor color( red.toInt(), green.toInt(), blue.toInt() );
    return color.name();
}

QString Manage::getHexString(QColor color)
{
    return color.name();
}

QString Manage::getRed(const QString &hexString)
{
    QColor color( hexString );
    return QString::number( color.red() );
}

QString Manage::getGreen(const QString &hexString)
{
    QColor color( hexString );
    return QString::number( color.green() );
}

QString Manage::getBlue(const QString &hexString)
{
    QColor color( hexString );
    return QString::number( color.blue() );
}
