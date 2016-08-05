#include "PngWarningRemover.h"

// Qt lib import
#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtConcurrent>

using namespace PngWarningRemover;

QString Manage::conversationPng()
{
    QEventLoop eventLoop;
    QString reply;

    const auto &&filePaths = QFileDialog::getOpenFileNames(
                    nullptr,
                    QStringLiteral( "\u8BF7\u9009\u62E9PNG\u56FE\u7247\uFF08\u53EF\u591A\u9009\uFF09" ),
                    QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                    "*.png"
                );

    QtConcurrent::run( [ &eventLoop, &reply, &filePaths ]()
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

            if ( image.isNull() || !image.save( filePath ) )
            {
                reply = "openSourceError";
                QMetaObject::invokeMethod( &eventLoop, "quit" );
                return;
            }

            QImage image2( image.bits(), image.width(), image.height(), QImage::Format_ARGB32 );

            if ( image2.isNull() || !image2.save( filePath ) )
            {
                reply = "saveTargetError";
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
