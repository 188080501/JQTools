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

#include "JQBarcode.h"

// Qt lib import
#include <QDebug>
#include <QPainter>

qint64 JQBarcode::makeNumber(const qint64 &rawNumebr)
{
    const auto &n1 = rawNumebr / 100000000000 % 10;
    const auto &n2 = rawNumebr / 10000000000 % 10;
    const auto &n3 = rawNumebr / 1000000000 % 10;
    const auto &n4 = rawNumebr / 100000000 % 10;
    const auto &n5 = rawNumebr / 10000000 % 10;
    const auto &n6 = rawNumebr / 1000000 % 10;
    const auto &n7 = rawNumebr / 100000 % 10;
    const auto &n8 = rawNumebr / 10000 % 10;
    const auto &n9 = rawNumebr / 1000 % 10;
    const auto &n10 = rawNumebr / 100 % 10;
    const auto &n11 = rawNumebr / 10 % 10;
    const auto &n12 = rawNumebr / 1 % 10;
    const auto &&c1 = n1 + n3 + n5 + n7 + n9 + n11;
    const auto &&c2 = ( n2 + n4 + n6 + n8 + n10 + n12 ) * 3;
    const auto &&cc = c1 + c2;
    const auto &&c = qAbs( 10 - ( cc % 10 ) );

//    qDebug() << n1 << n2 << n3 << n4 << n5 << n6 << n7 << n8 << n9 << n10 << n11 << n12;
//    qDebug() << cc;

    return rawNumebr * 10 + c;
}

QImage JQBarcode::makeBarcode(const qint64 &number)
{
    QImage image( QSize( 190, 120 ), QImage::Format_ARGB32 );
    image.fill( qRgba( 0, 0, 0, 0 ) );

    auto pos = 0;

    JQBarcode::paintLine( image, true,  pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, false, pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, true,  pos, 120 ); pos += 1;

    JQBarcode::paintByteA( image, number / 100000000000 % 10, pos ); pos += 7;
    JQBarcode::paintByteB( image, number / 10000000000 % 10, pos ); pos += 7;
    JQBarcode::paintByteB( image, number / 1000000000 % 10, pos ); pos += 7;
    JQBarcode::paintByteB( image, number / 100000000 % 10, pos ); pos += 7;
    JQBarcode::paintByteA( image, number / 10000000 % 10, pos ); pos += 7;
    JQBarcode::paintByteA( image, number / 1000000 % 10, pos ); pos += 7;

    JQBarcode::paintLine( image, false, pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, true,  pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, false, pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, true,  pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, false, pos, 120 ); pos += 1;

    JQBarcode::paintByteC( image, number / 100000 % 10, pos ); pos += 7;
    JQBarcode::paintByteC( image, number / 10000 % 10, pos ); pos += 7;
    JQBarcode::paintByteC( image, number / 1000 % 10, pos ); pos += 7;
    JQBarcode::paintByteC( image, number / 100 % 10, pos ); pos += 7;
    JQBarcode::paintByteC( image, number / 10 % 10, pos ); pos += 7;
    JQBarcode::paintByteC( image, number % 10, pos ); pos += 7;

    JQBarcode::paintLine( image, true,  pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, false, pos, 120 ); pos += 1;
    JQBarcode::paintLine( image, true,  pos, 120 );

    return image;
}

void JQBarcode::paintByteA(QImage &image, const int &number, const int &pos)
{
    switch( number )
    {
        case 0: JQBarcode::paintLines( image, "0001101", pos ); break;
        case 1: JQBarcode::paintLines( image, "0011001", pos ); break;
        case 2: JQBarcode::paintLines( image, "0010011", pos ); break;
        case 3: JQBarcode::paintLines( image, "0111101", pos ); break;
        case 4: JQBarcode::paintLines( image, "0100011", pos ); break;
        case 5: JQBarcode::paintLines( image, "0110001", pos ); break;
        case 6: JQBarcode::paintLines( image, "0101111", pos ); break;
        case 7: JQBarcode::paintLines( image, "0111011", pos ); break;
        case 8: JQBarcode::paintLines( image, "0110111", pos ); break;
        case 9: JQBarcode::paintLines( image, "0001011", pos ); break;
        default: qDebug() << "JQBarcode::paintByteA: unexpected number:" << number; break;
    }
}

void JQBarcode::paintByteB(QImage &image, const int &number, const int &pos)
{
    switch( number )
    {
        case 0: JQBarcode::paintLines( image, "0100111", pos ); break;
        case 1: JQBarcode::paintLines( image, "0110011", pos ); break;
        case 2: JQBarcode::paintLines( image, "0011011", pos ); break;
        case 3: JQBarcode::paintLines( image, "0100001", pos ); break;
        case 4: JQBarcode::paintLines( image, "0011101", pos ); break;
        case 5: JQBarcode::paintLines( image, "0111001", pos ); break;
        case 6: JQBarcode::paintLines( image, "0000101", pos ); break;
        case 7: JQBarcode::paintLines( image, "0010001", pos ); break;
        case 8: JQBarcode::paintLines( image, "0001001", pos ); break;
        case 9: JQBarcode::paintLines( image, "0010111", pos ); break;
        default: qDebug() << "JQBarcode::paintByteB: unexpected number:" << number; break;
    }
}

void JQBarcode::paintByteC(QImage &image, const int &number, const int &pos)
{
    switch( number )
    {
        case 0: JQBarcode::paintLines( image, "1110010", pos ); break;
        case 1: JQBarcode::paintLines( image, "1100110", pos ); break;
        case 2: JQBarcode::paintLines( image, "1101100", pos ); break;
        case 3: JQBarcode::paintLines( image, "1000010", pos ); break;
        case 4: JQBarcode::paintLines( image, "1011100", pos ); break;
        case 5: JQBarcode::paintLines( image, "1001110", pos ); break;
        case 6: JQBarcode::paintLines( image, "1010000", pos ); break;
        case 7: JQBarcode::paintLines( image, "1000100", pos ); break;
        case 8: JQBarcode::paintLines( image, "1001000", pos ); break;
        case 9: JQBarcode::paintLines( image, "1110100", pos ); break;
        default: qDebug() << "JQBarcode::paintByteC: unexpected number:" << number; break;
    }
}

void JQBarcode::paintLines(QImage &image, const QString &key, const int &pos, const int &len)
{
    for ( auto index = 0; index < 7; ++index )
    {
        JQBarcode::paintLine( image, key[ index ] == '1', pos + index, len);
    }
}

void JQBarcode::paintLine(QImage &image, const bool &black, const int &pos, const int &len)
{
    for ( auto index = 0; index < len; ++index )
    {
        image.setPixel( pos * 2, index, ( black ) ? ( qRgba( 0, 0, 0, 255 ) ) : ( qRgba( 0, 0, 0, 0 ) ) );
        image.setPixel( pos * 2 + 1, index, ( black ) ? ( qRgba( 0, 0, 0, 255 ) ) : ( qRgba( 0, 0, 0, 0 ) ) );
    }
}
