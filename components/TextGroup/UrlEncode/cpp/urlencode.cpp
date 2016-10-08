/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "urlencode.h"

// Qt lib import
#include <QColor>
#include <QUrl>

using namespace UrlEncode;

QString Manage::encode(const QString &string)
{
    return QUrl( string ).toEncoded();
}

QString Manage::decode(const QString &string)
{
    return QUrl::fromEncoded( string.toUtf8() ).toString();
}
