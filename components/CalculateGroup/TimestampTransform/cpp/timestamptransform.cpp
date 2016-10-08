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
