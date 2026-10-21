/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools
*/

#ifndef GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENTUTILS_H_
#define GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENTUTILS_H_

// STL import
#include <algorithm>

// Qt lib import
#include <QByteArray>
#include <QList>
#include <QPair>
#include <QString>

namespace BatchReplacement
{
namespace Detail
{

typedef QPair< QString, QString > CaseVariant;
typedef QList< CaseVariant > CaseVariants;

inline CaseVariants makeCaseVariants(
        const QString &sourceKey,
        const QString &targetKey,
        const bool multiCase
    )
{
    CaseVariants caseVariants;

    auto addCaseVariant = [ &caseVariants ](
            const QString &currentSourceKey,
            const QString &currentTargetKey
        )
    {
        // Ignore no-op mappings before deduplication so they cannot shadow a useful mapping.
        if ( currentSourceKey.isEmpty() || ( currentSourceKey == currentTargetKey ) ) { return; }

        for ( const auto &caseVariant: caseVariants )
        {
            if ( caseVariant.first == currentSourceKey ) { return; }
        }

        caseVariants.push_back( { currentSourceKey, currentTargetKey } );
    };

    // The explicitly entered mapping wins if generated case forms collide.
    addCaseVariant( sourceKey, targetKey );

    if ( !multiCase ) { return caseVariants; }

    const auto lowerSourceKey = sourceKey.toLower();
    const auto upperSourceKey = sourceKey.toUpper();
    const auto lowerTargetKey = targetKey.toLower();
    const auto upperTargetKey = targetKey.toUpper();

    addCaseVariant( lowerSourceKey, lowerTargetKey );
    addCaseVariant( upperSourceKey, upperTargetKey );

    if ( ( sourceKey.size() > 1 ) && ( targetKey.size() > 1 ) )
    {
        auto sourceKey2 = sourceKey;
        auto targetKey2 = targetKey;

        sourceKey2[ 0 ] = lowerSourceKey[ 0 ];
        targetKey2[ 0 ] = lowerTargetKey[ 0 ];
        addCaseVariant( sourceKey2, targetKey2 );

        sourceKey2[ 0 ] = upperSourceKey[ 0 ];
        targetKey2[ 0 ] = upperTargetKey[ 0 ];
        addCaseVariant( sourceKey2, targetKey2 );
    }

    return caseVariants;
}

// Match the original input once so inserted target text is not processed again.
template< typename StringType >
StringType replaceCaseVariants(
        const StringType &source,
        const QList< QPair< StringType, StringType > > &caseVariants,
        const bool applyChanges,
        int &replacementCount
    )
{
    if ( caseVariants.isEmpty() ) { return source; }

    StringType result;
    if ( applyChanges ) { result.reserve( source.size() ); }

    auto position = 0;

    while ( position < source.size() )
    {
        const QPair< StringType, StringType > *matchedVariant = nullptr;

        for ( const auto &caseVariant: caseVariants )
        {
            const auto &currentSourceKey = caseVariant.first;
            if ( currentSourceKey.isEmpty() ) { continue; }

            if ( matchedVariant && ( currentSourceKey.size() <= matchedVariant->first.size() ) ) { continue; }
            if ( currentSourceKey.size() > ( source.size() - position ) ) { continue; }
            if ( !std::equal( currentSourceKey.constBegin(), currentSourceKey.constEnd(), source.constBegin() + position ) ) { continue; }

            matchedVariant = &caseVariant;
        }

        if ( matchedVariant )
        {
            ++replacementCount;
            if ( applyChanges ) { result.append( matchedVariant->second ); }
            position += matchedVariant->first.size();
        }
        else
        {
            if ( applyChanges ) { result.append( source.at( position ) ); }
            ++position;
        }
    }

    return applyChanges ? result : source;
}

}
}

#endif//GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENTUTILS_H_
