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
#include <QEventLoop>
#include <QMetaObject>
#include <QtConcurrent>
#include <QDir>

// JQToolsLibrary import
#include <JQToolsLibrary>

using namespace BatchReplacement;

QJsonObject Manage::startBatchReplacement(
        const QJsonArray &suffixes,
        const QString &sourceKey,
        const QString &targetKey,
        const bool multiCase
    )
{
    auto fileCount = 0;
    auto replacementCount = 0;

    auto currentPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "ba0f41c3-0d36-454a-8e79-7728738c9309" ),
                u8"请选择目标目录"
            );
    if ( currentPath.isEmpty() )
    {
        return
            { {
                { "cancel", true }
            } };
    }

    QSet< QString > availableSuffixes;

    for ( const auto suffix: suffixes )
    {
        availableSuffixes.insert( suffix.toString().toLower() );
    }

    QEventLoop eventLoop;

    QtConcurrent::run( [ & ]()
    {
        auto batchReplacement = [ &fileCount, &replacementCount, currentPath, availableSuffixes ](
                const QString &currentSourceKey,
                const QString &currentTargetKey
            )
        {
            AbstractTool::foreachFileFromDirectory( { currentPath }, [ & ](const QFileInfo &info)
            {
                if ( info.suffix().isEmpty() )
                {
                    if ( !availableSuffixes.contains( "nosuffixfile" ) )
                    {
                        return;
                    }
                }
                else
                {
                    if ( !availableSuffixes.contains( info.suffix().toLower() ) )
                    {
                        return;
                    }
                }

                QByteArray fileAllData;

                {
                    QFile file( info.filePath() );
                    if ( !file.open( QIODevice::ReadOnly ) ) { return; }

                    fileAllData = file.readAll();
                }

                if ( fileAllData.isEmpty() ) { return; }

                const auto matchCount = fileAllData.count( currentSourceKey.toUtf8() );

                if ( !matchCount ) { return; }

                ++fileCount;
                replacementCount += matchCount;

                AbstractTool::writeFile( QFileInfo( info.filePath() ), fileAllData.replace( currentSourceKey.toUtf8(), currentTargetKey.toUtf8() ) );
            }, true );

            if ( availableSuffixes.contains( "filenameanddirname" ) )
            {
                QFileInfoList fileNameList;
                QList< QDir > dirNameList;

                AbstractTool::foreachFileFromDirectory( { currentPath }, [ & ](const QFileInfo &info)
                {
                    if ( info.suffix().isEmpty() )
                    {
                        if ( !availableSuffixes.contains( "nosuffixfile" ) )
                        {
                            return;
                        }
                    }
                    else
                    {
                        if ( !availableSuffixes.contains( info.suffix().toLower() ) )
                        {
                            return;
                        }
                    }

                    const auto matchCount = info.fileName().count( currentSourceKey.toUtf8() );

                    if ( !matchCount ) { return; }

                    ++fileCount;
                    replacementCount += matchCount;

                    fileNameList.push_back( info );
                }, true );

                AbstractTool::foreachDirectoryFromDirectory( { currentPath }, [ & ](const QDir &dir)
                {
                    const auto matchCount = dir.dirName().count( currentSourceKey );

                    if ( !matchCount ) { return; }

                    ++fileCount;
                    replacementCount += matchCount;

                    dirNameList.push_back( dir );
                }, true );

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
                    const QString targetFilePath = QString( "%1/%2" ).arg( info.path(), info.fileName().replace( currentSourceKey, currentTargetKey ) );

                    QFile::rename( info.filePath(), targetFilePath );
                }

                for ( const auto &dir: dirNameList )
                {
                    const QString targetDir = QString( "%1/%2" ).arg( QFileInfo( dir.path() ).path(), dir.dirName().replace( currentSourceKey, currentTargetKey ) );

                    QDir().rename( dir.path(), targetDir );
                }
            }
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

        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();

    return
        { {
            { "fileCount", fileCount },
            { "replacementCount", replacementCount }
        } };
}
