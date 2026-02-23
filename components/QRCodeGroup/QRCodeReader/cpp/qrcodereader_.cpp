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
#include <QUrl>

// JQLibrary lib import
#include "JQQRCodeReader.h"

using namespace QRCodeReader;

Manage::Manage():
    jqQRCodeReader_( new JQQRCodeReader )
{ }

QUrl Manage::chooseImage() const
{
    return QUrl::fromLocalFile(
                AbstractTool::getOpenFileName(
                    QStringLiteral( "5786d92b-7deb-4a6e-8d39-d45181ecceb5" ),
                    QStringLiteral( "\u8BF7\u9009\u62E9\u56FE\u7247" ),
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
