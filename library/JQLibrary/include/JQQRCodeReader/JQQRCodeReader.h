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

