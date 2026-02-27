/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "batchreplacement.h"

// STL import
#include <algorithm>

// Qt lib import
#include <QSet>
#include <QJsonArray>
#include <QDir>

// JQToolsLibrary import
#include <JQToolsLibrary>

using namespace BatchReplacement;

namespace
{

QSet< QString > makeAvailableSuffixes(const QJsonArray &suffixes)
{
    QSet< QString > availableSuffixes;

    for ( const auto &suffix: suffixes )
    {
        availableSuffixes.insert( suffix.toString().toLower() );
    }

    return availableSuffixes;
}

bool isMatchedSuffix(
        const QFileInfo &info,
        const QSet< QString > &availableSuffixes
    )
{
    if ( info.suffix().isEmpty() )
    {
        return availableSuffixes.contains( "nosuffixfile" );
    }

    return availableSuffixes.contains( info.suffix().toLower() );
}

void collectReplacementBySingleCase(
        const QString &directoryPath,
        const QSet< QString > &availableSuffixes,
        const QString &sourceKey,
        const QString &targetKey,
        const bool applyChanges,
        int &fileCount,
        int &replacementCount
    )
{
    if ( sourceKey.isEmpty() ) { return; }

    const auto sourceKeyData = sourceKey.toUtf8();
    const auto targetKeyData = targetKey.toUtf8();

    AbstractTool::foreachFileFromDirectory( { directoryPath }, [ & ](const QFileInfo &info)
    {
        if ( !isMatchedSuffix( info, availableSuffixes ) ) { return; }

        QByteArray fileAllData;

        {
            QFile file( info.filePath() );
            if ( !file.open( QIODevice::ReadOnly ) ) { return; }

            fileAllData = file.readAll();
        }

        if ( fileAllData.isEmpty() ) { return; }

        const auto matchCount = fileAllData.count( sourceKeyData );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( !applyChanges ) { return; }

        AbstractTool::writeFile(
                    QFileInfo( info.filePath() ),
                    fileAllData.replace( sourceKeyData, targetKeyData )
                );
    }, true );

    if ( !availableSuffixes.contains( "filenameanddirname" ) ) { return; }

    QFileInfoList fileNameList;
    QList< QDir > dirNameList;

    AbstractTool::foreachFileFromDirectory( { directoryPath }, [ & ](const QFileInfo &info)
    {
        if ( !isMatchedSuffix( info, availableSuffixes ) ) { return; }

        const auto matchCount = info.fileName().count( sourceKey );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( applyChanges )
        {
            fileNameList.push_back( info );
        }
    }, true );

    AbstractTool::foreachDirectoryFromDirectory( { directoryPath }, [ & ](const QDir &dir)
    {
        const auto matchCount = dir.dirName().count( sourceKey );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( applyChanges )
        {
            dirNameList.push_back( dir );
        }
    }, true );

    if ( !applyChanges ) { return; }

    // 目录改名需要先子后父，避免父目录先改名导致子目录路径失效
    std::sort( dirNameList.begin(), dirNameList.end(), [ ](const QDir &left, const QDir &right)
    {
        const auto leftPath = QDir::cleanPath( left.path() );
        const auto rightPath = QDir::cleanPath( right.path() );
        const auto leftDepth = leftPath.count( '/' );
        const auto rightDepth = rightPath.count( '/' );

        if ( leftDepth == rightDepth )
        {
            return leftPath.size() > rightPath.size();
        }

        return leftDepth > rightDepth;
    } );

    for ( const auto &info: fileNameList )
    {
        const auto targetFilePath = QString( "%1/%2" ).arg(
                    info.path(),
                    info.fileName().replace( sourceKey, targetKey )
                );

        QFile::rename( info.filePath(), targetFilePath );
    }

    for ( const auto &dir: dirNameList )
    {
        const auto targetDir = QString( "%1/%2" ).arg(
                    QFileInfo( dir.path() ).path(),
                    dir.dirName().replace( sourceKey, targetKey )
                );

        QDir().rename( dir.path(), targetDir );
    }
}

QJsonObject runBatchReplacement(
        const QString &directoryPath,
        const QJsonArray &suffixes,
        const QString &sourceKey,
        const QString &targetKey,
        const bool multiCase,
        const bool applyChanges
    )
{
    auto fileCount = 0;
    auto replacementCount = 0;

    const auto availableSuffixes = makeAvailableSuffixes( suffixes );
    auto batchReplacement = [ & ](
            const QString &currentSourceKey,
            const QString &currentTargetKey
        )
    {
        collectReplacementBySingleCase(
                    directoryPath,
                    availableSuffixes,
                    currentSourceKey,
                    currentTargetKey,
                    applyChanges,
                    fileCount,
                    replacementCount
                );
    };

    if ( multiCase )
    {
        batchReplacement( sourceKey.toLower(), targetKey.toLower() );
        batchReplacement( sourceKey.toUpper(), targetKey.toUpper() );

        if ( ( sourceKey.size() > 1 ) && ( targetKey.size() > 1 ) )
        {
            auto sourceKey2 = sourceKey;
            auto targetKey2 = targetKey;

            sourceKey2[ 0 ] = sourceKey.toLower()[ 0 ];
            targetKey2[ 0 ] = targetKey.toLower()[ 0 ];

            batchReplacement( sourceKey2, targetKey2 );

            sourceKey2[ 0 ] = sourceKey.toUpper()[ 0 ];
            targetKey2[ 0 ] = targetKey.toUpper()[ 0 ];

            batchReplacement( sourceKey2, targetKey2 );
        }
        else
        {
            batchReplacement( sourceKey, targetKey );
        }
    }
    else
    {
        batchReplacement( sourceKey, targetKey );
    }

    return
        { {
            { "fileCount", fileCount },
            { "replacementCount", replacementCount }
        } };
}

}

QJsonObject Manage::previewBatchReplacement(
        const QJsonArray &suffixes,
        const QString &sourceKey,
        const bool multiCase
    )
{
    if ( sourceKey.isEmpty() )
    {
        return
            { {
                { "error", "empty source key" }
            } };
    }

    const auto directoryPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "ba0f41c3-0d36-454a-8e79-7728738c9309" ),
                u8"请选择目标目录"
            );
    if ( directoryPath.isEmpty() )
    {
        return
            { {
                { "cancel", true }
            } };
    }

    auto result = runBatchReplacement(
                directoryPath,
                suffixes,
                sourceKey,
                QString(),
                multiCase,
                false
            );
    result[ "directoryPath" ] = directoryPath;

    return result;
}

QJsonObject Manage::startBatchReplacement(
        const QString &directoryPath,
        const QJsonArray &suffixes,
        const QString &sourceKey,
        const QString &targetKey,
        const bool multiCase
    )
{
    if ( directoryPath.isEmpty() )
    {
        return
            { {
                { "error", "empty directory path" }
            } };
    }

    if ( sourceKey.isEmpty() )
    {
        return
            { {
                { "error", "empty source key" }
            } };
    }

    return runBatchReplacement(
                directoryPath,
                suffixes,
                sourceKey,
                targetKey,
                multiCase,
                true
            );
}
