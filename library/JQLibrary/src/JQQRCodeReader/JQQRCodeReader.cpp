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

/*
    本文件中，部分源码来自于QZxing

    https://github.com/ftylitak/qzxing
*/

#include "JQQRCodeReader.h"

// Qt lib import
#include <QDebug>
#include <QImage>
#include <QMetaObject>
#include <QSemaphore>
#include <QThread>

// zxing lib import
#include "zxing/common/GlobalHistogramBinarizer.h"
#include "zxing/Binarizer.h"
#include "zxing/BinaryBitmap.h"
#include "zxing/MultiFormatReader.h"
#include "zxing/DecodeHints.h"
#include "zxing/LuminanceSource.h"

// ImageWrapper
class ImageWrapper: public zxing::LuminanceSource
{
    Q_DISABLE_COPY( ImageWrapper )

public:
    ImageWrapper(const QImage &sourceImage):
        LuminanceSource( sourceImage.width(), sourceImage.height() ),
        image_( sourceImage )
    { }

    virtual ~ImageWrapper() = default;

    // Callers take ownership of the returned memory and must call delete [] on it themselves.
    zxing::ArrayRef< char > getRow(int y, zxing::ArrayRef< char > row) const
    {
        int width = getWidth();

        if ( row->size() != width )
        {
            row.reset( zxing::ArrayRef< char >( width ) );
        }

        for ( int x = 0; x < width; ++x )
        {
            row[ x ] = static_cast< char >( qGray( image_.pixel( x,y ) ) );
        }

        return row;
    }

    zxing::ArrayRef< char > getMatrix() const
    {
        int width = image_.width();
        int height = image_.height();
        char *matrix = new char[ width * height ];
        char *m = matrix;

        for( int y = 0; y < height; ++y )
        {
            zxing::ArrayRef< char > tmpRow;
            tmpRow = getRow( y, zxing::ArrayRef< char >( width ) );
#if __cplusplus > 199711L
            memcpy( m, tmpRow->values().data(), width );
#else
            memcpy( m, &tmpRow->values()[ 0 ], width );
#endif
            m += width * sizeof( unsigned char );

            //delete tmpRow;
        }

        zxing::ArrayRef< char > arr = zxing::ArrayRef< char >(matrix, width*height);

        if( matrix )
        {
            delete[] matrix;
        }

        return arr;
    }

private:
    QImage image_;
};

// JQQRCodeReader
JQQRCodeReader::JQQRCodeReader():
    decoder_( new zxing::MultiFormatReader ),
    semaphore_( new QSemaphore( 1 ) )
{ }

JQQRCodeReader::~JQQRCodeReader()
{
    semaphore_->acquire( 1 );
}

QString JQQRCodeReader::decodeImage(const QImage &image, const int &decodeType)
{
    semaphore_->acquire( 1 );

    zxing::Ref< zxing::Result > res;
    QMetaObject::invokeMethod( this, "decodingStarted", Qt::QueuedConnection );

    if( image.isNull() )
    {
        qDebug() << "JQQRCodeReader::decodeImage: error: image is null";
        emit decodingFinished( false );

        semaphore_->release( 1 );
        return { };
    }

    auto ciw = new ImageWrapper( image );

    zxing::Ref< zxing::LuminanceSource > imageRef( ciw );
    zxing::GlobalHistogramBinarizer* binz = new zxing::GlobalHistogramBinarizer( imageRef );

    zxing::Ref< zxing::Binarizer > bz( binz );
    zxing::BinaryBitmap *bb = new zxing::BinaryBitmap( bz );

    zxing::Ref< zxing::BinaryBitmap > ref( bb );

    try
    {
        res = decoder_->decode( ref, static_cast< zxing::DecodeHints >( static_cast< unsigned int >( decodeType ) ) );

        QString string = QString( res->getText()->getText().c_str() );

        QMetaObject::invokeMethod( this, "tagFound", Qt::QueuedConnection, Q_ARG( QString, string ) );
        QMetaObject::invokeMethod( this, "decodingFinished", Qt::QueuedConnection, Q_ARG( bool, true ) );

        semaphore_->release( 1 );
        return string;
    }
    catch ( zxing::Exception & )
    {
        QMetaObject::invokeMethod( this, "decodingFinished", Qt::QueuedConnection, Q_ARG( bool, false ) );

        semaphore_->release( 1 );
    }

    return { };
}
