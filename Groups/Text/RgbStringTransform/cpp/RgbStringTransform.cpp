#include "RgbStringTransform.h"

// Qt lib import
#include <QColor>
#include <QClipboard>
#include <QApplication>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

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

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
