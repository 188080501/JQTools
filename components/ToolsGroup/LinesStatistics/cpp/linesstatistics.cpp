/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "linesstatistics.h"

// Qt lib import
#include <QDir>
#include <QFile>
#include <QSet>
#include <QJsonArray>
#include <QEventLoop>
#include <QMetaObject>
#include <QStringList>
#include <QtConcurrent>

// JQToolsLibrary import
#include <JQToolsLibrary>

using namespace LinesStatistics;

QJsonObject Manage::collectLineStatistics(const QJsonArray &suffixes, const QJsonArray &ignoredDirectoryNames)
{
    auto fileCount = 0;
    auto lineCount = 0;

    auto currentPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "5bf4742e-886d-4938-840f-3106416f9416" ),
                u8"请选择代码目录"
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

    QSet< QString > availableIgnoredDirectoryNames;

    for ( const auto directoryName: ignoredDirectoryNames )
    {
        const auto currentDirectoryName = directoryName.toString().trimmed().toLower();
        if ( currentDirectoryName.isEmpty() ) { continue; }

        availableIgnoredDirectoryNames.insert( currentDirectoryName );
    }

    QEventLoop eventLoop;

    QtConcurrent::run( [ & ]()
    {
        const QSet< QString > imageSuffixes
            {
                "png",
                "jpg",
                "jpeg",
                "bmp",
                "gif",
                "svg",
                "psd",
                "ai"
            };

        QStringList pendingDirectoryPaths;
        pendingDirectoryPaths.push_back( currentPath );

        while ( !pendingDirectoryPaths.isEmpty() )
        {
            const auto directoryPath = pendingDirectoryPaths.takeLast();
            const QDir directory( directoryPath );

            if ( !directory.exists() ) { continue; }
            if ( availableIgnoredDirectoryNames.contains( directory.dirName().toLower() ) ) { continue; }

            for ( const auto &fileInfo: directory.entryInfoList( QDir::Files ) )
            {
                const auto currentSuffix = fileInfo.suffix().toLower();
                if ( !availableSuffixes.contains( currentSuffix ) ) { continue; }

                QFile file( fileInfo.filePath() );
                if ( !file.open( QIODevice::ReadOnly ) ) { continue; }

                fileCount++;

                const auto fileAllData = file.readAll();
                if ( fileAllData.isEmpty() ) { continue; }
                if ( imageSuffixes.contains( currentSuffix ) ) { continue; }

                lineCount += fileAllData.count('\n') + 1;
            }

            for ( const auto &subDirectoryInfo: directory.entryInfoList( QDir::AllDirs | QDir::NoDotAndDotDot ) )
            {
                pendingDirectoryPaths.push_back( subDirectoryInfo.filePath() );
            }
        }

        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();

    return
        { {
            { "fileCount", fileCount },
            { "lineCount", lineCount }
        } };
}
