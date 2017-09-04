/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "batchreplacement.h"

// Qt lib import
#include <QSet>
#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonArray>
#include <QEventLoop>
#include <QtConcurrent>
#include <QDir>

// JQLibrary import
#include "JQFile.h"

using namespace BatchReplacement;

QJsonObject Manage::startBatchReplacement(
        const QJsonArray &suffixs,
        const QString &sourceKey,
        const QString &targetKey,
        const bool &multiCase
    )
{
    auto fileCount = 0;
    auto replacementCount = 0;

    static QString lastPath = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );

    auto currentPath = QFileDialog::getExistingDirectory( nullptr, "Please choose target dir", lastPath );
    if ( currentPath.isEmpty() )
    {
        return
            { {
                { "cancel", true }
            } };
    }

    lastPath = currentPath;

    QSet< QString > availableSuffixs;

    for ( const auto suffix: suffixs )
    {
        availableSuffixs.insert( suffix.toString().toLower() );
    }

    QEventLoop eventLoop;

    QtConcurrent::run( [ & ]()
    {
        auto batchReplacement = [ &fileCount, &replacementCount, currentPath, availableSuffixs ](
                const QString &currentSourceKey,
                const QString &currentTargetKey
            )
        {
            qDebug() << "batchReplacement:" << currentSourceKey << currentTargetKey;

            JQFile::foreachFileFromDirectory( { currentPath }, [ & ](const QFileInfo &info)
            {
                if ( info.suffix().isEmpty() )
                {
                    if ( !availableSuffixs.contains( "nosuffixfile" ) )
                    {
                        return;
                    }
                }
                else
                {
                    if ( !availableSuffixs.contains( info.suffix().toLower() ) )
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

                const auto &&matchCount = fileAllData.count( currentSourceKey.toUtf8() );

                if ( !matchCount ) { return; }

                qDebug() << "file data:" << info.filePath() << matchCount;

                ++fileCount;
                replacementCount += matchCount;

                JQFile::writeFile( info.filePath(), fileAllData.replace( currentSourceKey.toUtf8(), currentTargetKey.toUtf8() ) );
            }, true );

            if ( availableSuffixs.contains( "filenameanddirname" ) )
            {
                QFileInfoList fileNameList;
                QList< QDir > dirNameList;

                JQFile::foreachFileFromDirectory( { currentPath }, [ & ](const QFileInfo &info)
                {
                    if ( info.suffix().isEmpty() )
                    {
                        if ( !availableSuffixs.contains( "nosuffixfile" ) )
                        {
                            return;
                        }
                    }
                    else
                    {
                        if ( !availableSuffixs.contains( info.suffix().toLower() ) )
                        {
                            return;
                        }
                    }

                    const auto &&matchCount = info.fileName().count( currentSourceKey.toUtf8() );

                    if ( !matchCount ) { return; }

                    qDebug() << "file name:" << info.filePath() << matchCount;

                    ++fileCount;
                    replacementCount += matchCount;

                    fileNameList.push_back( info );
                }, true );

                JQFile::foreachDirectoryFromDirectory( { currentPath }, [ & ](const QDir &dir)
                {
                    const auto &&matchCount = dir.dirName().count( currentSourceKey );

                    if ( !matchCount ) { return; }

                    qDebug() << "dir path:" << dir.path() << matchCount;

                    ++fileCount;
                    replacementCount += matchCount;

                    dirNameList.push_back( dir );
                }, true );

                for ( const auto &info: fileNameList )
                {
                    const QString targetFilePath = QString( "%1/%2" ).arg( info.path(), info.fileName().replace( currentSourceKey, currentTargetKey ) );

                    qDebug() << "file:" << info.filePath() << "->" << targetFilePath;
                    QFile::rename( info.filePath(), targetFilePath );
                }

                for ( const auto &dir: dirNameList )
                {
                    const QString targetDir = QString( "%1/%2" ).arg( QFileInfo( dir.path() ).path(), dir.dirName().replace( currentSourceKey, currentTargetKey ) );

                    qDebug() << "dir:" << dir.path() << "->" << targetDir;
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

        eventLoop.quit();
    } );

    eventLoop.exec();

    return
        { {
            { "fileCount", fileCount },
            { "replacementCount", replacementCount }
        } };
}
