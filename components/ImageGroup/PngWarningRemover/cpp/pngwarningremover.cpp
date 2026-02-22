/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "pngwarningremover.h"

// Qt lib import
#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtConcurrent>
#include <QFileInfo>

using namespace PngWarningRemover;

QString Manage::conversationPng()
{
    const auto filePaths = QFileDialog::getOpenFileNames(
                    nullptr,
                    QStringLiteral( "\u8BF7\u9009\u62E9PNG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                    QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                    "*.png"
                );

    return this->conversationPng( filePaths );
}

QString Manage::conversationPngByOpenDirectory()
{
    QStringList filePaths;

    const auto directoryPath = QFileDialog::getExistingDirectory(
                nullptr,
                QStringLiteral( "\u8BF7\u9009\u62E9\u5305\u542BPNG\u56FE\u7247\u7684\u6587\u4EF6\u5939" ),
                QStandardPaths::writableLocation( QStandardPaths::DesktopLocation )
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

    return this->conversationPng( filePaths );
}

QString Manage::conversationPng(const QStringList &filePaths)
{
    QEventLoop eventLoop;
    QString reply;

    this->lastErrorFileName_.clear();

    QtConcurrent::run( [ this, &eventLoop, &reply, filePaths ]()
    {
        if ( filePaths.isEmpty() )
        {
            reply = "cancel";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        for ( const auto &filePath: filePaths )
        {
            QImage image( filePath, "PNG" );

            if ( image.isNull() )
            {
                reply = "openSourceError";
                this->lastErrorFileName_ = QFileInfo( filePath ).fileName();
                QMetaObject::invokeMethod( &eventLoop, "quit" );
                return;
            }

            const auto image2 = image.convertToFormat( QImage::Format_ARGB32 );

            if ( image2.isNull() || !image2.save( filePath, "PNG" ) )
            {
                reply = "saveTargetError";
                this->lastErrorFileName_ = QFileInfo( filePath ).fileName();
                QMetaObject::invokeMethod( &eventLoop, "quit" );
                return;
            }
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();

    return reply;
}
