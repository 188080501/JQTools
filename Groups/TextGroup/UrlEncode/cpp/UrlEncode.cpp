#include "UrlEncode.h"

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
