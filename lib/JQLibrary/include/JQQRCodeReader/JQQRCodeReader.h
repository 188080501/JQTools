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

#ifndef __JQQRCodeReader_h__
#define __JQQRCodeReader_h__

// Qt lib import
#include <QObject>
#include <QSharedPointer>

namespace zxing { class MultiFormatReader; }

class JQQRCodeReader: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQQRCodeReader )

public:
    JQQRCodeReader();

    ~JQQRCodeReader() = default;

public slots:
    QString decodeImage(const QImage &image);

signals:
    void decodingStarted();

    void decodingFinished(bool succeeded);

    void tagFound(QString tag);

private:
    QSharedPointer< zxing::MultiFormatReader > decoder_;
};

#endif//__JQQRCodeReader_h__

