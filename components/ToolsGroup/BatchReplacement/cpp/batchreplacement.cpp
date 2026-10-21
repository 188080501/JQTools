/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "batchreplacement.h"
#include "batchreplacementutils.h"

// STL import
#include <algorithm>

// Qt lib import
#include <QSet>
#include <QPair>
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

void collectReplacement(
        const QString &directoryPath,
        const QSet< QString > &availableSuffixes,
        const BatchReplacement::Detail::CaseVariants &caseVariants,
        const bool applyChanges,
        int &fileCount,
        int &replacementCount,
        int &failedOperationCount,
        QJsonArray &failedPaths
    )
{
    if ( caseVariants.isEmpty() ) { return; }

    auto recordFailurePath = [ & ](const QString &path)
    {
        ++failedOperationCount;

        // 仅回传部分失败路径，避免结果过大
        if ( failedPaths.size() >= 20 ) { return; }
        failedPaths.push_back( path );
    };

    QList< QPair< QByteArray, QByteArray > > byteCaseVariants;
    for ( const auto &caseVariant: caseVariants )
    {
        byteCaseVariants.push_back( {
            caseVariant.first.toUtf8(),
            caseVariant.second.toUtf8()
        } );
    }

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

        auto matchCount = 0;
        const auto replacedData = BatchReplacement::Detail::replaceCaseVariants(
                    fileAllData,
                    byteCaseVariants,
                    applyChanges,
                    matchCount
                );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( !applyChanges ) { return; }

        if ( !AbstractTool::writeFile( QFileInfo( info.filePath() ), replacedData ) )
        {
            recordFailurePath( info.filePath() );
        }
    }, true );

    if ( !availableSuffixes.contains( "filenameanddirname" ) ) { return; }

    QList< QPair< QFileInfo, QString > > fileNameList;
    QList< QPair< QDir, QString > > dirNameList;

    AbstractTool::foreachFileFromDirectory( { directoryPath }, [ & ](const QFileInfo &info)
    {
        if ( !isMatchedSuffix( info, availableSuffixes ) ) { return; }

        auto matchCount = 0;
        const auto replacedFileName = BatchReplacement::Detail::replaceCaseVariants(
                    info.fileName(),
                    caseVariants,
                    applyChanges,
                    matchCount
                );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( applyChanges )
        {
            fileNameList.push_back( { info, replacedFileName } );
        }
    }, true );

    AbstractTool::foreachDirectoryFromDirectory( { directoryPath }, [ & ](const QDir &dir)
    {
        auto matchCount = 0;
        const auto replacedDirName = BatchReplacement::Detail::replaceCaseVariants(
                    dir.dirName(),
                    caseVariants,
                    applyChanges,
                    matchCount
                );
        if ( !matchCount ) { return; }

        ++fileCount;
        replacementCount += matchCount;

        if ( applyChanges )
        {
            dirNameList.push_back( { dir, replacedDirName } );
        }
    }, true );

    if ( !applyChanges ) { return; }

    // 目录改名需要先子后父，避免父目录先改名导致子目录路径失效
    std::sort( dirNameList.begin(), dirNameList.end(), [ ](
            const QPair< QDir, QString > &left,
            const QPair< QDir, QString > &right
        )
    {
        const auto leftPath = QDir::cleanPath( left.first.path() );
        const auto rightPath = QDir::cleanPath( right.first.path() );
        const auto leftDepth = leftPath.count( '/' );
        const auto rightDepth = rightPath.count( '/' );

        if ( leftDepth == rightDepth )
        {
            return leftPath.size() > rightPath.size();
        }

        return leftDepth > rightDepth;
    } );

    for ( const auto &rename: fileNameList )
    {
        const auto targetFilePath = QString( "%1/%2" ).arg(
                    rename.first.path(),
                    rename.second
                );

        if ( targetFilePath == rename.first.filePath() ) { continue; }

        if ( !QFile::rename( rename.first.filePath(), targetFilePath ) )
        {
            recordFailurePath( rename.first.filePath() );
        }
    }

    for ( const auto &rename: dirNameList )
    {
        const auto targetDir = QString( "%1/%2" ).arg(
                    QFileInfo( rename.first.path() ).path(),
                    rename.second
                );

        if ( targetDir == rename.first.path() ) { continue; }

        if ( !QDir().rename( rename.first.path(), targetDir ) )
        {
            recordFailurePath( rename.first.path() );
        }
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
    auto failedOperationCount = 0;
    QJsonArray failedPaths;

    const auto availableSuffixes = makeAvailableSuffixes( suffixes );

    const auto caseVariants = BatchReplacement::Detail::makeCaseVariants(
                sourceKey,
                targetKey,
                multiCase
            );

    collectReplacement(
                directoryPath,
                availableSuffixes,
                caseVariants,
                applyChanges,
                fileCount,
                replacementCount,
                failedOperationCount,
                failedPaths
            );

    return
        { {
            { "fileCount", fileCount },
            { "replacementCount", replacementCount },
            { "failedOperationCount", failedOperationCount },
            { "failedPaths", failedPaths }
        } };
}

}

QJsonObject Manage::previewBatchReplacement(
        const QJsonArray &suffixes,
        const QString &sourceKey,
        const QString &targetKey,
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
                targetKey,
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
