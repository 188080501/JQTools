/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "qrcodereader.h"

// Qt lib import
#include <QDebug>
#include <QFileDialog>
#include <QStandardPaths>
#include <QUrl>

// JQLibrary lib import
#include "JQQRCodeReader.h"

using namespace QRCodeReader_;

Manage::Manage():
    jqQRCodeReader_( new JQQRCodeReader )
{ }

QUrl Manage::chooseImage() const
{
    return QUrl::fromLocalFile(
                QFileDialog::getOpenFileName(
                    nullptr,
                    QStringLiteral( "\u8BF7\u9009\u62E9\u56FE\u7247" ),
                    QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                    "*.png *.jpg"
                )
            );
}

QString Manage::decodeImage(const QUrl &imageUrl)
{
    if ( imageUrl.toString().startsWith( "file:" ) )
    {
        return jqQRCodeReader_->decodeImage( QImage( imageUrl.toLocalFile() ) );
    }
    else if ( imageUrl.toString().startsWith( "qrc:" ) )
    {
        return jqQRCodeReader_->decodeImage( QImage( imageUrl.toString().mid( 3 ) ) );
    }

    return { };
}
