/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "pngoptimize.h"

// C++ lib import
#include <functional>

// Qt lib import
#include <QStandardPaths>
#include <QtConcurrent>

// JQToolsLibrary import
#include "JQZopfli.h"
#include <JQToolsLibrary>

using namespace PngOptimize;

QString Manage::optimizePngByFilePaths(const bool coverOldFile, const QJsonArray &filePaths_)
{
    QStringList filePaths;

    for ( const auto &filePath: filePaths_ )
    {
        filePaths.push_back( filePath.toString() );
    }

    return this->optimizePng( coverOldFile, filePaths );
}

QString Manage::optimizePngByOpenFiles(const bool coverOldFile)
{
    const auto filePaths = AbstractTool::getOpenFileNames(
                QStringLiteral( "c0b3998b-3a24-4bd5-beeb-735ffd2c0b65" ),
                QStringLiteral( "\u8BF7\u9009\u62E9PNG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                "*.png"
            );

    if ( filePaths.isEmpty() ) { return "cancel"; }

    return this->optimizePng( coverOldFile, filePaths );
}

QString Manage::optimizePngByOpenDirectory(const bool coverOldFile)
{
    QStringList filePaths;

    const auto directoryPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "c459a40b-f704-47da-ad7c-8245b654403b" ),
                QStringLiteral( "\u8BF7\u9009\u62E9\u5305\u542BPNG\u56FE\u7247\u7684\u6587\u4EF6\u5939" )
            );

    if ( directoryPath.isEmpty() ) { return "cancel"; }

    AbstractTool::foreachFileFromDirectory(
                directoryPath,
                [ &filePaths ]
                (const QFileInfo &fileInfo)
                {
                    if ( fileInfo.suffix().toLower() != "png" ) { return; }

                    filePaths.push_back( fileInfo.filePath() );
                },
                true
            );

    if ( filePaths.isEmpty() ) { return "empty"; }

    return this->optimizePng( coverOldFile, filePaths );
}

void Manage::startOptimize(const QString &currentFilePath)
{
    if ( !waitOptimizeQueue_.contains( currentFilePath ) ) { return; }

    QtConcurrent::run( waitOptimizeQueue_[ currentFilePath ] );

    waitOptimizeQueue_.remove( currentFilePath );
}

QString Manage::urlToLocalPngFilePath(const QVariant &url)
{
    QFileInfo fileInfo( url.toUrl().toLocalFile() );
    if ( !fileInfo.isFile() ) { return { }; }
    if ( !fileInfo.filePath().toLower().endsWith( ".png" ) ) { return { }; }
    return fileInfo.filePath();
}

QString Manage::optimizePng(const bool coverOldFile, const QStringList &filePaths)
{
    QString targetDir;

    if ( !coverOldFile )
    {
        targetDir = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) + "/JQTools_OptimizePngResult/";

        if ( !QDir( targetDir ).exists() && !QDir().mkdir( targetDir ) )
        {
            return "mkdir error";
        }
    }

    QJsonArray fileList;

    static auto packageCount = 0;
    static QMutex mutex;

    for ( const auto &filePath: filePaths )
    {
        QFileInfo fileInfo( filePath );

        fileList.push_back( QJsonObject( { {
                                               { "fileName", fileInfo.fileName() },
                                               { "filePath", filePath },
                                               { "originalSize", AbstractTool::fileSizeString( fileInfo.size() ) }
                                           } } ) );

        ++packageCount;

        waitOptimizeQueue_[ filePath ] = [
                this,
                filePath,
                fileName = fileInfo.fileName(),
                originalFilePath = filePath,
                resultFilePath = ( targetDir.isEmpty() ) ? ( filePath ) : ( targetDir + "/" + fileInfo.fileName() )
                ]()
        {
            emit this->optimizePngStart( filePath );

            auto optimizeResult = JQZopfli::optimize( originalFilePath, resultFilePath );

            emit this->optimizePngFinish(
                        filePath,
                        { {
                              { "optimizeSucceed", optimizeResult.optimizeSucceed },
                              { "resultSize", AbstractTool::fileSizeString( optimizeResult.resultSize ) },
                              { "compressionRatio", QString( "%1%2%" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "-" ) : ( "" )  ).
                                arg( 100 - (int)(optimizeResult.compressionRatio * 100) ) },
                              { "compressionRatioColor", QString( "%1" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "#64dd17" ) : ( "#f44336" )  ) },
                              { "timeConsuming", QString( "%1ms" ).arg( optimizeResult.timeConsuming ) }
                          } }
                    );

            mutex.lock();

            --packageCount;

            if ( packageCount <= 0 )
            {
                emit this->optimizeEnd();
            }

            mutex.unlock();
        };
    }

    emit this->optimizeStart( fileList );

    return "OK";
}
