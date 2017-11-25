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

// JQLibrary lib import
#include "JQFoundation.h"

using namespace RandomUuid;

Manage::Manage()
{
    srand( QDateTime::currentDateTime().toTime_t() + qApp->applicationFilePath().size() );
}

QString Manage::randomUuid(const bool &includeParantheses)
{
    if ( includeParantheses )
    {
        return "{" + JQFoundation::createUuidString() + "}";
    }
    else
    {
        return JQFoundation::createUuidString();
    }
}
