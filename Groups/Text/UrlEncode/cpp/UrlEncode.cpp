#include "UrlEncode.h"

// Qt lib import
#include <QColor>
#include <QUrl>
#include <QClipboard>
#include <QApplication>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace UrlEncode;

QString Manage::encode(const QString &string)
{
    return QUrl( string ).toEncoded();
}

QString Manage::decode(const QString &string)
{
    return QUrl::fromEncoded( string.toUtf8() ).toString();
}

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
