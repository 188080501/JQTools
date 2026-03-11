/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "qrcodemaker.h"

// Qt lib import
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QPainter>
#include <QCoreApplication>

// JQLibrary lib import
#include "JQQRCodeWriter.h"

using namespace QRCodeMaker;

Manage::Manage()
{
    qApp->property( "qmlEngine" ).value< QQmlApplicationEngine * >()->addImageProvider( "QRCodeMaker", new ImageProvider );
}

Manage::~Manage()
{
    qApp->property( "qmlEngine" ).value< QQmlApplicationEngine * >()->removeImageProvider( "QRCodeMaker" );
}

QString Manage::savePng(const QString &string, int resolution)
{
    auto filePath = AbstractTool::getSaveFileName(
                QStringLiteral( "081ee636-a896-4dd0-9155-1eab9a1bdcd4" ),
                QStringLiteral( "请选择保存图片的路径" ),
                QString(),
                "*.png"
            );

    if ( filePath.isEmpty() ) { return "cancel"; }

    if ( !filePath.toLower().endsWith( ".png" ) )
    {
        filePath += ".png";
    }

    const auto imageSideLength = qBound( 128, resolution, 8192 );
    const auto imagePadding = qMax( 2, imageSideLength / 50 );
    const auto qrCodeSideLength = qMax( 1, imageSideLength - ( imagePadding * 2 ) );

    QImage targetImage( QSize( imageSideLength, imageSideLength ), QImage::Format_RGB888 );
    targetImage.fill( QColor( "#ffffff" ) );

    const auto qrCodeImage = JQQRCodeWriter::makeQRcode( string, QSize( qrCodeSideLength, qrCodeSideLength ) );

    {
        QPainter painter;
        painter.begin( &targetImage );
        painter.drawImage( imagePadding, imagePadding, qrCodeImage );
    }

    const auto saveSucceed = targetImage.save( filePath );
    if ( !saveSucceed )
    {
        return "error";
    }

    return "OK";
}

ImageProvider::ImageProvider():
    QQuickImageProvider( QQuickImageProvider::Image )
{ }

QImage ImageProvider::requestImage(const QString &id, QSize *, const QSize &)
{
    return JQQRCodeWriter::makeQRcode( id );
}
