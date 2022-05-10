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

#ifndef JQQRCODEREADERFORQML_H_
#define JQQRCODEREADERFORQML_H_

// Qt lib import
#include <QObject>
#include <QSharedPointer>
#include <QPointer>
#include <QQmlContext>
#include <QQuickPaintedItem>
#include <QMutex>
#include <QPainter>

// JQLibrary import
#include "JQQRCodeReader.h"

#ifdef QT_QML_LIB
#   define JQQRCODEREADERFORQML_REGISTERTYPE( engine ) \
    engine.rootContext()->setContextProperty( "JQQRCodeReaderForQmlManage", new JQQRCodeReaderForQmlManage ); \
    engine.addImportPath( ":/JQQRCodeReader/" ); \
    qmlRegisterType< ImagePreviewView >( "ImagePreviewView", 1, 0, "ImagePreviewView" );
#endif

class QThreadPool;
class QSemaphore;
class QQuickItem;
class QQuickItemGrabResult;
class QImage;

class ImagePreviewView: public QQuickPaintedItem
{
    Q_OBJECT

public:
    ImagePreviewView() = default;

    ~ImagePreviewView() = default;

    static void pushImage(const QImage &image);

private:
    void paint(QPainter *p);

private:
    static QPointer< ImagePreviewView > object_;
    static QMutex mutex_;
    static QImage image_;
};

class JQQRCodeReaderForQmlManage: public JQQRCodeReader
{
    Q_OBJECT
    Q_DISABLE_COPY( JQQRCodeReaderForQmlManage )
    Q_PROPERTY(int decodeQrCodeType READ decodeQrCodeType WRITE setDecodeQrCodeType)

public:
    JQQRCodeReaderForQmlManage();

    ~JQQRCodeReaderForQmlManage();

public slots:
    void analysisItem(
            QQuickItem *item,
            const int &apertureX,
            const int &apertureY,
            const int &apertureWidth,
            const int &apertureHeight
        );

private:
    static QImage binarization(const QImage &image, const qreal &correctionValue);

    static int getReference(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd, const qreal &correctionValue);

    static qreal avgReference(const qreal &referenceAvg, const qreal &currentReference);

    static void processImage(QImage &image, const int &xStart, const int &yStart, const int &xEnd, const int &yEnd, const qreal &offset, const qreal &correctionValue);

private:
    QSharedPointer< QThreadPool > threadPool_;
    QSharedPointer< QSemaphore > semaphore_;
    QSharedPointer< QQuickItemGrabResult > quickItemGrabResult_;
    qreal defaultCorrectionValue_ = 1.42;

    // Property code start
    private: int decodeQrCodeType_ = JQQRCodeReader::DecodeQrCodeType;
    public: Q_SLOT inline int decodeQrCodeType() const
    { return decodeQrCodeType_; }
    public: Q_SLOT inline void setDecodeQrCodeType(const int &newValue)
    { if ( newValue == decodeQrCodeType_ ) { return; } decodeQrCodeType_ = newValue; }
    private:
    // Property code end
};

#endif//JQQRCODEREADERFORQML_H_

