/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "stringsort.h"

// C++ lib import
#include <algorithm>

using namespace StringSort;

QString Manage::sort(const QString &string, const bool &descOrder)
{
    auto list = string.split( "\n", QString::SkipEmptyParts );

    std::sort( list.begin(), list.end(), [ = ]( const QString &a, const QString &b )
    {
        if ( descOrder ) { return a > b; }
        return a < b;
    } );

    return list.join( "\n" );
}
