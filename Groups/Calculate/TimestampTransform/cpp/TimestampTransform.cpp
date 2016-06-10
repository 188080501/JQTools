#include "TimestampTransform.h"

// Qt lib import
#include <QDateTime>
#include <QCryptographicHash>

using namespace TimestampTransform;

QString Manage::currentDateTimeTimestampString()
{
    return QString::number( QDateTime::currentDateTime().toTime_t() );
}

QString Manage::dateTimeStringFromTimestampString(const QString &timestampString)
{
    if ( timestampString.size() == 13 )
    {
        return QDateTime::fromMSecsSinceEpoch( timestampString.toLongLong() ).toString( "yyyy-MM-dd hh:mm:ss" );
    }
    else if ( timestampString.size() == 10 )
    {
        return QDateTime::fromTime_t( timestampString.toInt() ).toString( "yyyy-MM-dd hh:mm:ss" );
    }

    return { };
}
