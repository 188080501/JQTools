/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "linesstatistics.h"

// Qt lib import
#include <QSet>
#include <QFileDialog>
#include <QStandardPaths>
#include <QJsonArray>
#include <QEventLoop>
#include <QMetaObject>
#include <QtConcurrent>

// JQToolsLibrary import
#include <JQToolsLibrary>

using namespace LinesStatistics;

QJsonObject Manage::collectLineStatistics(const QJsonArray &suffixes)
{
    auto fileCount = 0;
    auto lineCount = 0;

    auto currentPath = QFileDialog::getExistingDirectory( nullptr,
                                                          u8"请选择代码目录",
                                                          QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) );
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
        static QSet< QString > imageSuffixes;
        if ( imageSuffixes.isEmpty() )
        {
            imageSuffixes.insert( "png" );
            imageSuffixes.insert( "jpg" );
            imageSuffixes.insert( "jpeg" );
            imageSuffixes.insert( "bmp" );
            imageSuffixes.insert( "gif" );
            imageSuffixes.insert( "svg" );
            imageSuffixes.insert( "psd" );
            imageSuffixes.insert( "ai" );
        }

        AbstractTool::foreachFileFromDirectory( { currentPath }, [ & ](const QFileInfo &info)
        {
            if ( !availableSuffixes.contains( info.suffix().toLower() ) ) { return; }

            QFile file( info.filePath() );
            if ( !file.open( QIODevice::ReadOnly ) ) { return; }

            fileCount++;

            const auto fileAllData = file.readAll();

            if ( fileAllData.isEmpty() ) { return; }

            if ( imageSuffixes.contains( info.suffix().toLower() ) ) { return; }

            lineCount += fileAllData.count('\n') + 1;
        }, true );

        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();

    return
        { {
            { "fileCount", fileCount },
            { "lineCount", lineCount }
        } };
}
