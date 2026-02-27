/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "barcodegenerator.h"

// Qt lib import
#include <QDebug>

qint64 BarcodeGenerator::makeNumber(const qint64 rawNumber)
{
    const auto &n1 = rawNumber / 100000000000 % 10;
    const auto &n2 = rawNumber / 10000000000 % 10;
    const auto &n3 = rawNumber / 1000000000 % 10;
    const auto &n4 = rawNumber / 100000000 % 10;
    const auto &n5 = rawNumber / 10000000 % 10;
    const auto &n6 = rawNumber / 1000000 % 10;
    const auto &n7 = rawNumber / 100000 % 10;
    const auto &n8 = rawNumber / 10000 % 10;
    const auto &n9 = rawNumber / 1000 % 10;
    const auto &n10 = rawNumber / 100 % 10;
    const auto &n11 = rawNumber / 10 % 10;
    const auto &n12 = rawNumber / 1 % 10;
    const auto c1 = n1 + n3 + n5 + n7 + n9 + n11;
    const auto c2 = ( n2 + n4 + n6 + n8 + n10 + n12 ) * 3;
    const auto cc = c1 + c2;
    // EAN-13 check digit: (10 - (sum % 10)) % 10, so remainder 0 gives 0.
    const auto c = ( 10 - ( cc % 10 ) ) % 10;

    return rawNumber * 10 + c;
}

QImage BarcodeGenerator::makeBarcode(const qint64 number)
{
    QImage image( QSize( 190, 120 ), QImage::Format_ARGB32 );
    image.fill( qRgba( 0, 0, 0, 0 ) );

    auto pos = 0;

    BarcodeGenerator::paintLine( image, true,  pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, false, pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, true,  pos, 120 ); pos += 1;

    BarcodeGenerator::paintByteA( image, number / 100000000000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteB( image, number / 10000000000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteB( image, number / 1000000000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteB( image, number / 100000000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteA( image, number / 10000000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteA( image, number / 1000000 % 10, pos ); pos += 7;

    BarcodeGenerator::paintLine( image, false, pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, true,  pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, false, pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, true,  pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, false, pos, 120 ); pos += 1;

    BarcodeGenerator::paintByteC( image, number / 100000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteC( image, number / 10000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteC( image, number / 1000 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteC( image, number / 100 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteC( image, number / 10 % 10, pos ); pos += 7;
    BarcodeGenerator::paintByteC( image, number % 10, pos ); pos += 7;

    BarcodeGenerator::paintLine( image, true,  pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, false, pos, 120 ); pos += 1;
    BarcodeGenerator::paintLine( image, true,  pos, 120 );

    return image;
}

void BarcodeGenerator::paintByteA(QImage &image, const int number, const int pos)
{
    switch ( number )
    {
        case 0: BarcodeGenerator::paintLines( image, "0001101", pos ); break;
        case 1: BarcodeGenerator::paintLines( image, "0011001", pos ); break;
        case 2: BarcodeGenerator::paintLines( image, "0010011", pos ); break;
        case 3: BarcodeGenerator::paintLines( image, "0111101", pos ); break;
        case 4: BarcodeGenerator::paintLines( image, "0100011", pos ); break;
        case 5: BarcodeGenerator::paintLines( image, "0110001", pos ); break;
        case 6: BarcodeGenerator::paintLines( image, "0101111", pos ); break;
        case 7: BarcodeGenerator::paintLines( image, "0111011", pos ); break;
        case 8: BarcodeGenerator::paintLines( image, "0110111", pos ); break;
        case 9: BarcodeGenerator::paintLines( image, "0001011", pos ); break;
        default: qDebug() << "BarcodeGenerator::paintByteA: unexpected number:" << number; break;
    }
}

void BarcodeGenerator::paintByteB(QImage &image, const int number, const int pos)
{
    switch ( number )
    {
        case 0: BarcodeGenerator::paintLines( image, "0100111", pos ); break;
        case 1: BarcodeGenerator::paintLines( image, "0110011", pos ); break;
        case 2: BarcodeGenerator::paintLines( image, "0011011", pos ); break;
        case 3: BarcodeGenerator::paintLines( image, "0100001", pos ); break;
        case 4: BarcodeGenerator::paintLines( image, "0011101", pos ); break;
        case 5: BarcodeGenerator::paintLines( image, "0111001", pos ); break;
        case 6: BarcodeGenerator::paintLines( image, "0000101", pos ); break;
        case 7: BarcodeGenerator::paintLines( image, "0010001", pos ); break;
        case 8: BarcodeGenerator::paintLines( image, "0001001", pos ); break;
        case 9: BarcodeGenerator::paintLines( image, "0010111", pos ); break;
        default: qDebug() << "BarcodeGenerator::paintByteB: unexpected number:" << number; break;
    }
}

void BarcodeGenerator::paintByteC(QImage &image, const int number, const int pos)
{
    switch ( number )
    {
        case 0: BarcodeGenerator::paintLines( image, "1110010", pos ); break;
        case 1: BarcodeGenerator::paintLines( image, "1100110", pos ); break;
        case 2: BarcodeGenerator::paintLines( image, "1101100", pos ); break;
        case 3: BarcodeGenerator::paintLines( image, "1000010", pos ); break;
        case 4: BarcodeGenerator::paintLines( image, "1011100", pos ); break;
        case 5: BarcodeGenerator::paintLines( image, "1001110", pos ); break;
        case 6: BarcodeGenerator::paintLines( image, "1010000", pos ); break;
        case 7: BarcodeGenerator::paintLines( image, "1000100", pos ); break;
        case 8: BarcodeGenerator::paintLines( image, "1001000", pos ); break;
        case 9: BarcodeGenerator::paintLines( image, "1110100", pos ); break;
        default: qDebug() << "BarcodeGenerator::paintByteC: unexpected number:" << number; break;
    }
}

void BarcodeGenerator::paintLines(QImage &image, const QString &key, const int pos, const int len)
{
    for ( auto index = 0; index < 7; ++index )
    {
        BarcodeGenerator::paintLine( image, key[ index ] == '1', pos + index, len );
    }
}

void BarcodeGenerator::paintLine(QImage &image, const bool black, const int pos, const int len)
{
    for ( auto index = 0; index < len; ++index )
    {
        image.setPixel( pos * 2, index, ( black ) ? ( qRgba( 0, 0, 0, 255 ) ) : ( qRgba( 0, 0, 0, 0 ) ) );
        image.setPixel( pos * 2 + 1, index, ( black ) ? ( qRgba( 0, 0, 0, 255 ) ) : ( qRgba( 0, 0, 0, 0 ) ) );
    }
}
