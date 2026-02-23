/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "jpgoptimize.h"

// C++ lib import
#include <functional>

// Qt lib import
#include <QAtomicInt>
#include <QStandardPaths>
#include <QtConcurrent>
#include <QSharedPointer>

// JQGuetzli import
#include "JQGuetzli.h"
#include <JQToolsLibrary>

using namespace JpgOptimize;

QString Manage::optimizeJpgByFilePaths(const bool coverOldFile, const QJsonArray &filePaths_)
{
    QStringList filePaths;

    for ( const auto &filePath: filePaths_ )
    {
        filePaths.push_back( filePath.toString() );
    }

    return this->optimizeJpg( coverOldFile, filePaths );
}

QString Manage::optimizeJpgByOpenFiles(const bool coverOldFile)
{
    const auto filePaths = AbstractTool::getOpenFileNames(
                QStringLiteral( "d0247a92-ad1d-41f6-b13a-6f767990872c" ),
                QStringLiteral( "\u8BF7\u9009\u62E9JPG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                "*.jpg"
            );

    if ( filePaths.isEmpty() ) { return "cancel"; }

    return this->optimizeJpg( coverOldFile, filePaths );
}

QString Manage::optimizeJpgByOpenDirectory(const bool coverOldFile)
{
    QStringList filePaths;

    const auto directoryPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "c302cf0a-390f-4e7c-943a-fa8fcc812eb5" ),
                QStringLiteral( "\u8BF7\u9009\u62E9\u5305\u542BJPG\u56FE\u7247\u7684\u6587\u4EF6\u5939" )
            );

    if ( directoryPath.isEmpty() ) { return "cancel"; }

    AbstractTool::foreachFileFromDirectory(
                directoryPath,
                [ &filePaths ]
                (const QFileInfo &fileInfo)
                {
                    if ( fileInfo.suffix().toLower() != "jpg" ) { return; }

                    filePaths.push_back( fileInfo.filePath() );
                },
                true
            );

    if ( filePaths.isEmpty() ) { return "empty"; }

    return this->optimizeJpg( coverOldFile, filePaths );
}

void Manage::startOptimize(const QString &currentFilePath)
{
    if ( !waitOptimizeQueue_.contains( currentFilePath ) ) { return; }

    QtConcurrent::run( waitOptimizeQueue_[ currentFilePath ] );

    waitOptimizeQueue_.remove( currentFilePath );
}

QString Manage::urlToLocalJpgFilePath(const QVariant &url)
{
    QFileInfo fileInfo( url.toUrl().toLocalFile() );
    if ( !fileInfo.isFile() ) { return { }; }
    if ( !fileInfo.filePath().toLower().endsWith( ".jpg" ) ) { return { }; }
    return fileInfo.filePath();
}

QString Manage::optimizeJpg(const bool coverOldFile, const QStringList &filePaths)
{
    QString targetDir;

    if ( !coverOldFile )
    {
        targetDir = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) + "/JQTools_OptimizeJpgResult/";

        if ( !QDir( targetDir ).exists() && !QDir().mkdir( targetDir ) )
        {
            return "mkdir error";
        }
    }

    QJsonArray fileList;

    auto packageCount = QSharedPointer< QAtomicInt >::create( 0 );

    for ( const auto &filePath: filePaths )
    {
        QFileInfo fileInfo( filePath );

        fileList.push_back( QJsonObject( { {
                                               { "fileName", fileInfo.fileName() },
                                               { "filePath", filePath },
                                               { "originalSize", AbstractTool::fileSizeString( fileInfo.size() ) }
                                           } } ) );

        packageCount->fetchAndAddOrdered( 1 );

        waitOptimizeQueue_[ filePath ] = [
                this,
                filePath,
                packageCount,
                fileName = fileInfo.fileName(),
                originalFilePath = filePath,
                resultFilePath = ( targetDir.isEmpty() ) ? ( filePath ) : ( targetDir + "/" + fileInfo.fileName() )
                ]()
        {
            emit this->optimizeJpgStart( filePath );

            auto optimizeResult = JQGuetzli::process( originalFilePath, resultFilePath );

            emit this->optimizeJpgFinish(
                        filePath,
                        { {
                              { "optimizeSucceed", optimizeResult.processSucceed },
                              { "resultSize", AbstractTool::fileSizeString( optimizeResult.resultSize ) },
                              { "compressionRatio", QString( "%1%2%" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "-" ) : ( "" )  ).
                                arg( 100 - (int)(optimizeResult.compressionRatio * 100) ) },
                              { "compressionRatioColor", QString( "%1" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "#64dd17" ) : ( "#f44336" )  ) },
                              { "timeConsuming", QString( "%1ms" ).arg( optimizeResult.timeConsuming ) }
                          } }
                    );

            if ( packageCount->fetchAndSubOrdered( 1 ) == 1 )
            {
                emit this->optimizeEnd();
            }
        };
    }

    emit this->optimizeStart( fileList );

    return "OK";
}
