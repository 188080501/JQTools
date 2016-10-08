/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "jsonformat.h"

// Qt lib import
#include <QJsonObject>
#include <QJsonDocument>

using namespace JsonFormat;

bool Manage::check(const QString &string)
{
    return !QJsonDocument::fromJson( string.toUtf8() ).isNull();
}

QString Manage::format(const QString &string, const bool &compact)
{
    return QJsonDocument::fromJson( string.toUtf8() ).toJson( ( compact ) ? ( QJsonDocument::Compact ) : ( QJsonDocument::Indented ) );
}
