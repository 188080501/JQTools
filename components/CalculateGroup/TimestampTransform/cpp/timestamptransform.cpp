/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "timestamptransform.h"

// Qt lib import
#include <QDateTime>
#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
#include <QTimeZone>
#endif
#include <QRegularExpression>

using namespace TimestampTransform;

namespace
{

bool parseTimestampString(const QString &timestampString, qint64 &msecsSinceEpoch)
{
    const auto trimmedString = timestampString.trimmed();
    if ( trimmedString.isEmpty() ) { return false; }

    static const QRegularExpression timestampPattern( QStringLiteral( "^[+-]?\\d+$" ) );
    if ( !timestampPattern.match( trimmedString ).hasMatch() ) { return false; }

    bool convertOk = false;
    const auto timestampValue = trimmedString.toLongLong( &convertOk );
    if ( !convertOk ) { return false; }

    auto digitsCount = trimmedString.size();
    if ( ( trimmedString.startsWith( '+' ) ) || ( trimmedString.startsWith( '-' ) ) )
    {
        --digitsCount;
    }

    if ( ( digitsCount != 10 ) && ( digitsCount != 13 ) )
    {
        return false;
    }

    if ( digitsCount == 13 )
    {
        msecsSinceEpoch = timestampValue;
    }
    else
    {
        msecsSinceEpoch = timestampValue * 1000;
    }

    return true;
}

bool parseDateTimeString(
        const QString &dateTimeString,
        QDateTime &dateTime
    )
{
    const auto trimmedString = dateTimeString.trimmed();
    if ( trimmedString.isEmpty() ) { return false; }

    QDateTime parsedDateTime;

    static const QStringList formatList {
        QStringLiteral( "yyyy-MM-dd hh:mm:ss.zzz" ),
        QStringLiteral( "yyyy-MM-dd hh:mm:ss" ),
        QStringLiteral( "yyyy/MM/dd hh:mm:ss.zzz" ),
        QStringLiteral( "yyyy/MM/dd hh:mm:ss" )
    };

    for ( const auto &format: formatList )
    {
        parsedDateTime = QDateTime::fromString( trimmedString, format );
        if ( !parsedDateTime.isValid() ) { continue; }

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
        dateTime = QDateTime(
                    parsedDateTime.date(),
                    parsedDateTime.time(),
                    QTimeZone::LocalTime
                );
#else
        dateTime = QDateTime(
                    parsedDateTime.date(),
                    parsedDateTime.time(),
                    Qt::LocalTime
                );
#endif
        return true;
    }

    return false;
}

QString toDisplayDateTimeString(const QDateTime &dateTime)
{
    if ( !dateTime.isValid() ) { return { }; }

    return dateTime.toString( "yyyy-MM-dd hh:mm:ss.zzz" );
}

}

QString Manage::currentSecondsTimestampString()
{
    return QString::number( QDateTime::currentSecsSinceEpoch() );
}

QString Manage::currentMillisecondsTimestampString()
{
    return QString::number( QDateTime::currentMSecsSinceEpoch() );
}

QString Manage::currentDateTimeString()
{
    return QDateTime::currentDateTime().toString( "yyyy-MM-dd hh:mm:ss.zzz" );
}

QString Manage::dateTimeStringFromTimestampString(const QString &timestampString)
{
    qint64 msecsSinceEpoch = 0;
    if ( !parseTimestampString( timestampString, msecsSinceEpoch ) )
    {
        return { };
    }

#if QT_VERSION >= QT_VERSION_CHECK(6, 5, 0)
    return toDisplayDateTimeString( QDateTime::fromMSecsSinceEpoch( msecsSinceEpoch, QTimeZone::LocalTime ) );
#else
    return toDisplayDateTimeString( QDateTime::fromMSecsSinceEpoch( msecsSinceEpoch, Qt::LocalTime ) );
#endif
}

QString Manage::timestampStringFromDateTimeString(
        const QString &dateTimeString,
        const bool milliseconds
    )
{
    QDateTime dateTime;
    if ( !parseDateTimeString( dateTimeString, dateTime ) )
    {
        return { };
    }

    if ( milliseconds )
    {
        return QString::number( dateTime.toMSecsSinceEpoch() );
    }

    return QString::number( dateTime.toSecsSinceEpoch() );
}

