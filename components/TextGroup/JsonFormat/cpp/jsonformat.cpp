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
#include <QJsonParseError>

using namespace JsonFormat;

bool Manage::check(const QString &string)
{
    QJsonParseError parseError;
    QJsonDocument::fromJson( string.toUtf8(), &parseError );

    return parseError.error == QJsonParseError::NoError;
}

QString Manage::parseErrorString(const QString &string)
{
    const auto jsonData = string.toUtf8();

    QJsonParseError parseError;
    QJsonDocument::fromJson( jsonData, &parseError );

    if ( parseError.error == QJsonParseError::NoError )
    {
        return { };
    }

    const auto parsedPrefixString = QString::fromUtf8( jsonData.left( static_cast< int >( parseError.offset ) ) );
    const auto lineNumber = parsedPrefixString.count( '\n' ) + 1;
    const auto lastNewLineIndex = parsedPrefixString.lastIndexOf( '\n' );
    const auto columnNumber = ( lastNewLineIndex < 0 ) ?
                                  ( parsedPrefixString.size() + 1 ) :
                                  ( parsedPrefixString.size() - lastNewLineIndex );

    return QStringLiteral( "JSON 错误（第 %1 行，第 %2 列）：%3" ).arg(
                QString::number( lineNumber ),
                QString::number( columnNumber ),
                parseError.errorString()
            );
}

QString Manage::format(const QString &string, const bool compact)
{
    return QJsonDocument::fromJson( string.toUtf8() ).toJson( ( compact ) ? ( QJsonDocument::Compact ) : ( QJsonDocument::Indented ) );
}
