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

#include "JQQRCodeReaderForQml.h"

// Qt lib import
#include <QDebug>
#include <QImage>
#include <QSemaphore>
#include <QThreadPool>
#include <QtConcurrent>
#include <QQuickItem>
#include <QQuickItemGrabResult>

// ImagePreviewView
QPointer< ImagePreviewView > ImagePreviewView::object_;
QMutex ImagePreviewView::mutex_;
QImage ImagePreviewView::image_;

void ImagePreviewView::pushImage(const QImage &image)
{
    if ( !object_ ) { return; }

    mutex_.lock();
    image_ = image;
    mutex_.unlock();

    QMetaObject::invokeMethod( object_, "update", Qt::QueuedConnection );
}

void ImagePreviewView::paint(QPainter *p)
{
    if ( !object_ )
    {
        object_ = this;
    }

    if ( image_.isNull() ) { return; }

    if ( QSize( static_cast< int >( this->width() ), static_cast< int >( this->height() ) ) != image_.size() )
    {
        this->setSize( QSizeF( image_.width(), image_.height() ) );
    }

    mutex_.lock();
    p->drawImage( 0, 0, image_ );
    mutex_.unlock();
}

// JQQRCodeReaderForQmlManage
JQQRCodeReaderForQmlManage::JQQRCodeReaderForQmlManage():
    threadPool_( new QThreadPool ),
    semaphore_( new QSemaphore )
{
    threadPool_->setMaxThreadCount( std::max( QThread::idealThreadCount(), 3 ) );
    semaphore_->release( threadPool_->maxThreadCount() );
}

JQQRCodeReaderForQmlManage::~JQQRCodeReaderForQmlManage()
{
    threadPool_->waitForDone();
}

void JQQRCodeReaderForQmlManage::analysisItem(
        QQuickItem *item,
        const int &apertureX,
        const int &apertureY,
        const int &apertureWidth,
        const int &apertureHeight
    )
{
    if ( !semaphore_->tryAcquire( 1 ) ) { return; }

    const auto &&result = item->grabToImage();
    const auto &&geometry = QRect( apertureX, apertureY, apertureWidth, apertureHeight );

    QSharedPointer< QMetaObject::Connection > connection( new QMetaObject::Connection );
    *connection = connect( result.data(), &QQuickItemGrabResult::ready, [ this, result, connection, geometry ]()
    {
        const auto image = result->image();
        if ( image.isNull() )
        {
            qDebug( "JQQRCodeReaderForQmlManage::analysisItem: image is null" );
            return;
        }

        qDebug() << QByteArray( (const char *)image.bits(), 10 ).toHex();

        QtConcurrent::run( threadPool_.data(), [ this, image, geometry ]()
        {
//            QTime time;
//            time.start();

            QImage apertureImage = image.copy( geometry );

            this->decodeImage( apertureImage, this->decodeQrCodeType_ );

            const auto &&binarizationImage1 = this->binarization( apertureImage, defaultCorrectionValue_ );
            this->decodeImage( binarizationImage1, this->decodeQrCodeType_ );
//            ImagePreviewView::pushImage( binarizationResult1 );

            const auto &&binarizationImage2 = this->binarization( apertureImage, defaultCorrectionValue_ + 0.3 );
            this->decodeImage( binarizationImage2, this->decodeQrCodeType_ );
//            ImagePreviewView::pushImage( binarizationResult2 );

            const auto &&binarizationImage3 = this->binarization( apertureImage, defaultCorrectionValue_ - 0.3 );
            this->decodeImage( binarizationImage3, this->decodeQrCodeType_ );
//            ImagePreviewView::pushImage( binarizationResult3 );

            semaphore_->release( 1 );

//            qDebug() << time.elapsed();
        } );

        disconnect( *connection );
    } );
}

QImage JQQRCodeReaderForQmlManage::binarization(const QImage &image, const qreal &correctionValue)
{
    QImage result = image;

    int reference1 = getReference( result, 0, 0, result.width() / 2, result.height() / 2, correctionValue );
    int reference2 = getReference( result, result.width() / 2, 0, result.width(), result.height() / 2, correctionValue );
    int reference3 = getReference( result, 0, result.height() / 2, result.width() / 2, result.height(), correctionValue );
    int reference4 = getReference( result, result.width() / 2, result.height() / 2, result.width(), result.height(), correctionValue );

    double referenceAvg = ( reference1 + reference2 + reference3 + reference4 ) / 4;

    processImage( result, 0, 0, result.width() / 2, result.height() / 2, avgReference( referenceAvg, reference1 ), correctionValue );
    processImage( result, result.width() / 2, 0, result.width(), result.height() / 2, avgReference( referenceAvg, reference2 ), correctionValue );
    processImage( result, 0, result.height() / 2, result.width() / 2, result.height(), avgReference( referenceAvg, reference3 ), correctionValue );
    processImage( result, result.width() / 2, result.height() / 2, result.width(), result.height(), avgReference( referenceAvg, reference4 ), correctionValue );

    return result;
}

int JQQRCodeReaderForQmlManage::getReference(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd, const qreal &correctionValue)
{
    qint64 total = 0;

    for ( auto y = yStart; y < yEnd; ++y )
    {
        for ( auto x = xStart; x < xEnd; ++x )
        {
            const auto &&color = image.pixelColor( x, y );
            const auto &&value = color.red() + color.green() + color.blue();

            total += value;
        }
    }

    qint64 avg = total / ( ( xEnd - xStart ) * ( yEnd - yStart ) );
    int reference = 0;

    for ( auto y = yStart; y < yEnd; ++y )
    {
        for ( auto x = xStart; x < xEnd; ++x )
        {
            const auto &&color = image.pixelColor( x, y );
            const auto &&value = color.red() + color.green() + color.blue();

            if ( value > ( avg / correctionValue ) )
            {
                ++reference;
            }
        }
    }

    return reference;
}

qreal JQQRCodeReaderForQmlManage::avgReference(const qreal &referenceAvg, const qreal &currentReference)
{
    if ( ( currentReference / referenceAvg ) > 1.15 ) { return 0.08 * 2; }
    if ( ( currentReference / referenceAvg ) > 1.1 ) { return 0.04 * 2; }
    if ( ( currentReference / referenceAvg ) > 1.05 ) { return 0.02 * 2; }
    if ( ( currentReference / referenceAvg ) < 0.95 ) { return -0.02 * 2; }
    if ( ( currentReference / referenceAvg ) < 0.9 ) { return -0.04 * 2; }
    if ( ( currentReference / referenceAvg ) < 0.85 ) { return -0.08 * 2; }
    return 0;
}

void JQQRCodeReaderForQmlManage::processImage(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd, const qreal &offset, const qreal &correctionValue)
{
    qint64 total = 0;

    for ( auto y = yStart; y < yEnd; ++y )
    {
        for ( auto x = xStart; x < xEnd; ++x )
        {
            const auto &&color = image.pixelColor( x, y );
            const auto &&value = color.red() + color.green() + color.blue();

            total += value;
        }
    }

    qint64 avg = total / ( ( xEnd - xStart ) * ( yEnd - yStart ) );

    for ( auto y = yStart; y < yEnd; ++y )
    {
        for ( auto x = xStart; x < xEnd; ++x )
        {
            const auto &&color = image.pixelColor( x, y );
            const auto &&value = color.red() + color.green() + color.blue();

            if ( value > ( avg / ( correctionValue + offset ) ) )
            {
                image.setPixelColor( x, y, QColor( 255, 255, 255 ) );
            }
            else
            {
                image.setPixelColor( x, y, QColor( 0, 0, 0 ) );
            }
        }
    }
}
