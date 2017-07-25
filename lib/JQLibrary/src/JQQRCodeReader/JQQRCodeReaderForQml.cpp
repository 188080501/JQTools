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

void JQQRCodeReaderForQmlManage::analysisItem(QQuickItem *item)
{
    if ( !semaphore_->tryAcquire( 1 ) ) { return; }

    auto result = item->grabToImage();

    QSharedPointer< QMetaObject::Connection > connection( new QMetaObject::Connection );
    *connection = connect( result.data(), &QQuickItemGrabResult::ready, [ this, result, connection ]()
    {
        const auto image = result->image();

        QtConcurrent::run( [ this, image ]()
        {
            QImage buf;

            const auto cut = std::min( image.width(), image.height() ) * 0.28;

            if ( image.width() > image.height() )
            {
                buf = image.copy(
                            ( image.width() - image.height() ) / 2 + cut,
                            0 + cut,
                            image.height() - cut * 2,
                            image.height() - cut * 2
                        );
            }
            else
            {
                buf = image.copy(
                            0 + cut,
                            ( image.height() - image.width() ) / 2 + cut,
                            image.width() - cut * 2,
                            image.width() - cut * 2
                        );
            }

            this->decodeImage( buf, this->decodeQrCodeType_ );

            int reference1 = this->getReference( buf, 0, 0, buf.width() / 2, buf.height() / 2 );
            int reference2 = this->getReference( buf, buf.width() / 2, 0, buf.width(), buf.height() / 2 );
            int reference3 = this->getReference( buf, 0, buf.height() / 2, buf.width() / 2, buf.height() );
            int reference4 = this->getReference( buf, buf.width() / 2, buf.height() / 2, buf.width(), buf.height() );

            double referenceAvg = ( reference1 + reference2 + reference3 + reference4 ) / 4;

            this->processImage( buf, 0, 0, buf.width() / 2, buf.height() / 2, this->avgReference( referenceAvg, reference1 ) );
            this->processImage( buf, buf.width() / 2, 0, buf.width(), buf.height() / 2, this->avgReference( referenceAvg, reference2 ) );
            this->processImage( buf, 0, buf.height() / 2, buf.width() / 2, buf.height(), this->avgReference( referenceAvg, reference3 ) );
            this->processImage( buf, buf.width() / 2, buf.height() / 2, buf.width(), buf.height(), this->avgReference( referenceAvg, reference4 ) );

            this->decodeImage( buf, this->decodeQrCodeType_ );

//            TestClass::o->mutex.lock();
//            TestClass::o->image = buf;
//            TestClass::o->mutex.unlock();
//            QMetaObject::invokeMethod( TestClass::o, "update", Qt::QueuedConnection );

            semaphore_->release( 1 );
        } );

        disconnect( *connection );
    } );
}

int JQQRCodeReaderForQmlManage::getReference(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd)
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

            if ( value > ( avg / correctionValue_ ) )
            {
                ++reference;
            }
        }
    }

    return reference;
}

qreal JQQRCodeReaderForQmlManage::avgReference(const qreal &referenceAvg, const qreal &currentReference)
{
    if ( ( currentReference / referenceAvg ) > 1.15 ) { return 0.08; }
    if ( ( currentReference / referenceAvg ) > 1.1 ) { return 0.04; }
    if ( ( currentReference / referenceAvg ) > 1.05 ) { return 0.02; }
    if ( ( currentReference / referenceAvg ) < 0.95 ) { return -0.02; }
    if ( ( currentReference / referenceAvg ) < 0.9 ) { return -0.04; }
    if ( ( currentReference / referenceAvg ) < 0.85 ) { return -0.08; }
    return 0;
}

void JQQRCodeReaderForQmlManage::processImage(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd, const qreal &offset)
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

            if ( value > ( avg / ( correctionValue_ + offset ) ) )
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

//TestClass *TestClass::o;
//QMutex TestClass::mutex;
//QImage TestClass::image;

//void TestClass::paint(QPainter *p)
//{
//    o = this;

//    mutex.lock();
//    p->drawImage( 0, 0, image );
//    mutex.unlock();
//}
