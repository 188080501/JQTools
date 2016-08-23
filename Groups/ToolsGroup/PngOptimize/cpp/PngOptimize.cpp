#include "PngOptimize.h"

// C++ lib import
#include <functional>

// Qt lib import
#include <QFileDialog>
#include <QStandardPaths>
#include <QtConcurrent>

// JQLibrary import
#include "JQZopfli.h"

using namespace PngOptimize;

QString Manage::optimizePng(const bool &coverOldFile, const QJsonArray &filePaths_)
{
    QStringList filePaths;

    if ( filePaths_.isEmpty() )
    {
        filePaths = QFileDialog::getOpenFileNames(
                            nullptr,
                            QStringLiteral( "\u8BF7\u9009\u62E9PNG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                            QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                            "*.png"
                        );

        if ( filePaths.isEmpty() ) { return "cancel"; }
    }
    else
    {
        for ( const auto &filePath: filePaths_ )
        {
            filePaths.push_back( filePath.toString() );
        }
    }

    QString targetDir;

    if ( coverOldFile )
    {
        targetDir = QFileInfo( filePaths.first() ).path();
    }
    else
    {
        targetDir = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) + "/JQTools_OptimizePngResult/";

        if ( !QDir( targetDir ).exists() && !QDir().mkdir( targetDir ) )
        {
            return "mkdir error";
        }
    }

    QJsonArray fileList;

    auto makeSizeString = [](const int &size)
    {
        if ( size < 1024 )
        {
            return QString( "%1 byte" ).arg( size );
        }
        else if ( size < ( 1024 * 1024 ) )
        {
            return QString( "%1 kb" ).arg( size / 1024 );
        }
        else
        {
            return QString( "%1.%2 mb" ).arg( size / 1024 / 1024 ).arg( size / 1024 % 1024 );
        }
    };

    static auto packageCount = 0;
    static QMutex mutex;

    for ( const auto &filePath: filePaths )
    {
        QFileInfo fileInfo( filePath );

        fileList.push_back( QJsonObject( { {
                                               { "fileName", fileInfo.fileName() },
                                               { "originalSize", makeSizeString( fileInfo.size() ) }
                                           } } ) );

        ++packageCount;

        waitOptimizeQueue_[ fileInfo.fileName() ] = [
                this,
                makeSizeString,
                fileName = fileInfo.fileName(),
                originalFilePath = filePath,
                resultFilePath = targetDir + "/" + fileInfo.fileName()
                ]()
        {
            emit this->optimizePngStart( fileName );

            auto optimizeResult = JQZopfli::optimize( originalFilePath, resultFilePath );

            emit this->optimizePngFinish(
                        fileName,
                        { {
                              { "optimizeSucceed", optimizeResult.optimizeSucceed },
                              { "resultSize", makeSizeString( optimizeResult.resultSize ) },
                              { "compressionRatio", QString( "%1%2%" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "-" ) : ( "" )  ).
                                arg( 100 - (int)(optimizeResult.compressionRatio * 100) ) },
                              { "compressionRatioColor", QString( "%1" ).
                                arg( ( optimizeResult.compressionRatio < 1 ) ? ( "#64dd17" ) : ( "#f44336" )  ) }
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

void Manage::startOptimize(const QString &currentFileName)
{
    if ( !waitOptimizeQueue_.contains( currentFileName ) ) { return; }

    QtConcurrent::run( waitOptimizeQueue_[ currentFileName ] );

    waitOptimizeQueue_.remove( currentFileName );
}
