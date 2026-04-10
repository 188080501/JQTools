/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "textdedupsort.h"

// C++ lib import
#include <algorithm>

// Qt lib import
#include <QSet>
#include <QVector>

using namespace TextDedupSort;

QString Manage::deduplicateAndSort(const QString &string, const bool outputWrap)
{
    QSet<uint> uniqueCodes;
    QVector<uint> uniqueChars;
    const auto unicodeCodePoints = string.toUcs4();

    uniqueChars.reserve( unicodeCodePoints.size() );

    for ( const auto unicode: unicodeCodePoints )
    {
        if ( uniqueCodes.contains( unicode ) )
        {
            continue;
        }

        uniqueCodes.insert( unicode );
        uniqueChars.push_back( unicode );
    }

    std::sort( uniqueChars.begin(), uniqueChars.end() );

    if ( !outputWrap || uniqueChars.isEmpty() )
    {
        return QString::fromUcs4( uniqueChars.constData(), uniqueChars.size() );
    }

    QVector<uint> wrappedChars;
    wrappedChars.reserve( uniqueChars.size() + ( uniqueChars.size() / 80 ) );

    auto currentLineLength = 0;

    for ( int index = 0; index < uniqueChars.size(); ++index )
    {
        wrappedChars.push_back( uniqueChars.at( index ) );
        ++currentLineLength;

        if ( ( currentLineLength >= 80 ) && ( index + 1 < uniqueChars.size() ) )
        {
            wrappedChars.push_back( '\n' );
            currentLineLength = 0;
        }
    }

    return QString::fromUcs4( wrappedChars.constData(), wrappedChars.size() );
}
