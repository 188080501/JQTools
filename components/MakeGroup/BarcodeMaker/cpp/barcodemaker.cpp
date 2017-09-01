/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "barcodemaker.h"

// Qt lib import
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>

// JQLibrary lib import
#include "JQBarcode.h"

using namespace BarcodeMaker;

Manage::Manage()
{
    this->qmlApplicationEngine().data()->addImageProvider( "BarcodeMaker", new ImageProvider );
}

Manage::~Manage()
{
    this->qmlApplicationEngine().data()->removeImageProvider( "BarcodeMaker" );
}

QString Manage::savePng(const QString &string)
{
    auto filePath = QFileDialog::getSaveFileName(
                nullptr,
                QStringLiteral( "请选择保存图片的路径" ),
                QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                "*.png"
            );

    if ( filePath.isEmpty() ) { return "cancel"; }

    if ( !filePath.toLower().endsWith( ".png" ) )
    {
        filePath += ".png";
    }

    QImage targetImage( QSize( 210, 140 ), QImage::Format_RGB888 );
    targetImage.fill( QColor( "#ffffff" ) );

    const auto &&barcodeImage = JQBarcode::makeBarcode( string.toLongLong() );

    if ( ( string.size() == 13 ) && string.toLongLong() && ( string[ 0 ] == '6' ) )
    {
        QPainter painter;
        painter.begin( &targetImage );
        painter.drawImage( 10, 10, barcodeImage );
    }

    const auto &&saveSucceed = targetImage.save( filePath );
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
    if ( ( id.size() == 13 ) && id.toLongLong() && ( id[ 0 ] == '6' ) )
    {
        return JQBarcode::makeBarcode( id.toLongLong() );
    }
    else
    {
        return { };
    }
}
