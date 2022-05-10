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

#ifndef JQQRCODEREADER_H_
#define JQQRCODEREADER_H_

// Qt lib import
#include <QObject>
#include <QSharedPointer>

class QSemaphore;

namespace zxing { class MultiFormatReader; }

class JQQRCodeReader: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQQRCodeReader )

public:
    enum DecodeType
    {
        DecodeAztecType = 1 << 1,
        DecodeCodaBarType = 1 << 2,
        DecodeCode39Type = 1 << 3,
        DecodeCode93Type = 1 << 4,
        DecodeCode128Type = 1 << 5,
        DecodeDataMatrixType = 1 << 6,
        DecodeEan8Type = 1 << 7,
        DecodeEan13Type = 1 << 8,
        DecodeItfType = 1 << 9,
        DecodeMaxiCodeType = 1 << 10,
        DecodePdf417Type = 1 << 11,
        DecodeQrCodeType = 1 << 12,
        DecodeRss14Type = 1 << 13,
        DecodeRssExpandedType = 1 << 14,
        DecodeUpcAType = 1 << 15,
        DecodeUpcEType = 1 << 16,
        DecodeUpcEanExtensionType = 1 << 17
    };

public:
    JQQRCodeReader();

    ~JQQRCodeReader();

public slots:
    QString decodeImage(const QImage &image, const int &decodeType = static_cast< int >( DecodeQrCodeType ) );

signals:
    void decodingStarted();

    void decodingFinished(bool succeeded);

    void tagFound(QString tag);

private:
    QSharedPointer< zxing::MultiFormatReader > decoder_;
    QSharedPointer< QSemaphore > semaphore_;
};

#endif//JQQRCODEREADER_H_

