/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "webpmaker.h"

// C++ lib import
#include <functional>

// Qt lib import
#include <QStandardPaths>
#include <QtConcurrent>
#include <QImage>

// JQToolsLibrary import
#include "JQZopfli.h"
#include <JQToolsLibrary>

using namespace WebPMaker;

QString Manage::makeWebPByFilePaths(const bool coverOldFile, const QJsonArray &filePaths_)
{
    QStringList filePaths;

    for ( const auto &filePath: filePaths_ )
    {
        filePaths.push_back( filePath.toString() );
    }

    return this->makeWebP( coverOldFile, filePaths );
}

QString Manage::makeWebPByOpenFiles(const bool coverOldFile)
{
    const auto filePaths = AbstractTool::getOpenFileNames(
                QStringLiteral( "fa20a092-2936-4d14-8996-dacdd2c1f7bd" ),
                QStringLiteral( "\u8BF7\u9009\u62E9PNG/JPG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                "Images (*.png *.jpg)"
            );

    if ( filePaths.isEmpty() ) { return "cancel"; }

    return this->makeWebP( coverOldFile, filePaths );
}

QString Manage::makeWebPByOpenDirectory(const bool coverOldFile)
{
    QStringList filePaths;

    const auto directoryPath = AbstractTool::getExistingDirectory(
                QStringLiteral( "1aca401b-7f11-4c42-8327-cdfb33ac5f89" ),
                QStringLiteral( "\u8BF7\u9009\u62E9\u5305\u542BPNG/JPG\u56FE\u7247\u7684\u6587\u4EF6\u5939" )
            );

    if ( directoryPath.isEmpty() ) { return "cancel"; }

    AbstractTool::foreachFileFromDirectory(
                directoryPath,
                [ &filePaths ]
                (const QFileInfo &fileInfo)
                {
                    if ( ( fileInfo.suffix().toLower() != "png" ) && ( fileInfo.suffix().toLower() != "jpg" ) ) { return; }

                    filePaths.push_back( fileInfo.filePath() );
                },
                true
            );

    if ( filePaths.isEmpty() ) { return "empty"; }

    return this->makeWebP( coverOldFile, filePaths );
}

void Manage::startMake(const QString &currentFilePath)
{
    if ( !waitMakeQueue_.contains( currentFilePath ) ) { return; }

    QtConcurrent::run( waitMakeQueue_[ currentFilePath ] );

    waitMakeQueue_.remove( currentFilePath );
}

QString Manage::urlToLocalPngOrJpgFilePath(const QVariant &url)
{
    QFileInfo fileInfo( url.toUrl().toLocalFile() );
    if ( !fileInfo.isFile() ) { return { }; }
    if ( !fileInfo.filePath().toLower().endsWith( ".png" ) && !fileInfo.filePath().toLower().endsWith( ".jpg" ) ) { return { }; }
    return fileInfo.filePath();
}

QString Manage::makeWebP(const bool coverOldFile, const QStringList &filePaths)
{
    QString targetDir;

    if ( !coverOldFile )
    {
        targetDir = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) + "/JQTools_MakeWebPResult/";

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

        waitMakeQueue_[ filePath ] = [
                this,
                filePath,
                fileName = fileInfo.fileName(),
                originalFilePath = filePath,
                resultFilePath = ( targetDir.isEmpty() ) ? ( fileInfo.path() + "/" + fileInfo.completeBaseName() + ".webp" ) : ( targetDir + "/" + fileInfo.completeBaseName() + ".webp" )
                ]()
        {
            emit this->makeWebPStart( filePath );

            QElapsedTimer timer;
            timer.start();

            const auto saveSucceed = QImage( filePath ).save( resultFilePath, "WEBP", 100 );
            const auto targetFileInfo = QFileInfo( resultFilePath );
            const auto compressionRatio = static_cast< qreal >( targetFileInfo.size() ) / static_cast< qreal >( QFile( filePath ).size() );

            emit this->makeWebPFinish(
                        filePath,
                        { {
                              { "makeSucceed", saveSucceed },
                              { "resultSize", AbstractTool::fileSizeString( targetFileInfo.size() ) },
                              { "compressionRatio", QString( "%1%2%" ).
                                arg( ( compressionRatio < 1 ) ? ( "-" ) : ( "" )  ).
                                arg( 100 - (int)(compressionRatio * 100) ) },
                              { "compressionRatioColor", QString( "%1" ).
                                arg( ( compressionRatio < 1 ) ? ( "#64dd17" ) : ( "#f44336" )  ) },
                              { "timeConsuming", QString( "%1ms" ).arg( timer.elapsed() ) }
                          } }
                    );

            mutex.lock();

            --packageCount;

            if ( packageCount <= 0 )
            {
                emit this->makeEnd();
            }

            mutex.unlock();
        };
    }

    emit this->makeStart( fileList );

    return "OK";
}
