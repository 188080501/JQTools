/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "randomuuid.h"

// Qt lib import
#include <QCoreApplication>
#include <QDateTime>
#include <QUuid>

using namespace RandomUuid;

Manage::Manage()
{
    srand( QDateTime::currentMSecsSinceEpoch() + qApp->applicationFilePath().size() );
}

QString Manage::randomUuid(const bool includeBraces)
{
    return QUuid::createUuid().toString( ( includeBraces ) ? ( QUuid::WithBraces ) : ( QUuid::WithoutBraces ) );
}
