#include "JsonFormat.h"

// Qt lib import
#include <QClipboard>
#include <QApplication>
#include <QJsonObject>
#include <QJsonDocument>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace JsonFormat;

bool Manage::check(const QString &string)
{
    return !QJsonDocument::fromJson( string.toUtf8() ).isNull();
}

QString Manage::format(const QString &string, const bool &compact)
{
    return QJsonDocument::fromJson( string.toUtf8() ).toJson( ( compact ) ? ( QJsonDocument::Compact ) : ( QJsonDocument::Indented ) );
}

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
