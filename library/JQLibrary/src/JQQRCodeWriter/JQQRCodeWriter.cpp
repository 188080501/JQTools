/*
    This file is part of JQLibrary

    Copyright: Jason and others

    Contact email: 188080501@qq.com

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "JQQRCodeWriter.h"

// Qt lib import
#include <QDebug>
#include <QPainter>

// qrencode lib import
#include "./qrencode/qrencode.h"

using namespace JQQRCodeWriter;

QImage JQQRCodeWriter::makeQRcode(
        const QString &data,
        const QSize &size,
        const QColor &colorForPoint
    )
{
    QImage image( size, QImage::Format_RGB32 );
    image.fill( QColor( "#000000" ) );

    QPainter painter( &image );

    if ( !painter.isActive() )
    {
        qDebug() << "JQQRCodeWriter::makeQRcode: error";

        return image;
    }

    QRcode *qrCode = QRcode_encodeString( data.toUtf8().data(), 1, QR_ECLEVEL_H, QR_MODE_8, true );
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
        const int &&yy = static_cast< int >( y * s );
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
