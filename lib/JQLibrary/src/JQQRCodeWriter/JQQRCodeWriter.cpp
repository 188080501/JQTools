/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#include "JQQRCodeWriter.h"

// Qt lib import
#include <QDebug>
#include <QPainter>

// qrencode lib import
#include "./qrencode/qrencode.h"

using namespace JQQRCodeWriter;

QImage JQQRCodeWriter::makeQRcode(const QString &data, const QSize &size)
{
    QImage image( size, QImage::Format_RGB32 );

    QPainter painter( &image );

    if ( !painter.isActive() )
    {
        qDebug() << "JQQRCodeWriter::makeQRcode: error";

        memset( image.bits(), 0, image.width() * image.height() * 3 );

        return image;
    }

    QRcode *qrCode = QRcode_encodeString( data.toLatin1().data(), 1, QR_ECLEVEL_H, QR_MODE_8, true );
    if ( !qrCode )
    {
        qDebug() << "JQQRCodeWriter::makeQRcode: empty qrcode";

        QColor error( "#ffffff" );
        painter.setBrush( error );
        painter.setPen( Qt::NoPen );
        painter.drawRect( 0, 0, image.width(), image.height() );
        painter.end();

        return image;
    }

    QColor colorForPoint( "#000000" );
    QColor colorForBackground( "#ffffff" );

    painter.setBrush( colorForBackground );
    painter.setPen( Qt::NoPen );
    painter.drawRect( 0, 0, image.width(), image.height() );

    painter.setBrush( colorForPoint );

    const double &&s = ( qrCode->width > 0 ) ? ( qrCode->width ) : ( 1 );
    const double &&aspect = image.width() / image.height();
    const double &&scale = ( ( aspect > 1.0 ) ? image.height() : image.width() ) / s;

    for ( int y = 0; y < s; ++y )
    {
        const int &&yy = y * s;
        for( int x = 0; x < s; ++x )
        {
            const int &&xx = yy + x;
            const unsigned char &b = qrCode->data[xx];

            if( b & 0x01 )
            {
                const double rx1 = x * scale, ry1 = y * scale;
                QRectF r( rx1, ry1, scale, scale );
                painter.drawRects( &r,1 );
            }
        }
    }

    QRcode_free( qrCode );
    painter.end();

    return image;
}
