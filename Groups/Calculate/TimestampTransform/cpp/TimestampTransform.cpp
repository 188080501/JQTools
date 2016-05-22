#include "TimestampTransform.h"

// Qt lib import
#include <QDateTime>
#include <QApplication>
#include <QClipboard>
#include <QCryptographicHash>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

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

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
