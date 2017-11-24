/*
    This file is part of JasonQt

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
