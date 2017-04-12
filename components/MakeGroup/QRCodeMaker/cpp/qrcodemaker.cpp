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
#include <QFileDialog>
#include <QStandardPaths>

// JQLibrary lib import
#include "JQQRCodeWriter.h"

using namespace QRCodeMaker;

Manage::Manage()
{
    this->qmlApplicationEngine().data()->addImageProvider( "QRCodeMaker", new ImageProvider );
}

Manage::~Manage()
{
    this->qmlApplicationEngine().data()->removeImageProvider( "QRCodeMaker" );
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

    const auto &&saveSucceed = JQQRCodeWriter::makeQRcode( string ).save( filePath );
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
