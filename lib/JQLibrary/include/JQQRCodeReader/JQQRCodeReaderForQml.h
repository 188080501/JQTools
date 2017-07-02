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

#ifndef JQQRCODEREADERFORQML_H_
#define JQQRCODEREADERFORQML_H_

// Qt lib import
#include <QObject>
#include <QSharedPointer>
#include <QQmlContext>

// JQLibrary import
#include "JQQRCodeReader.h"

#ifdef QT_QML_LIB
#   define JQQRCODEREADERFORQML_REGISTERTYPE( engine ) \
    engine.rootContext()->setContextProperty( "JQQRCodeReaderForQmlManage", new JQQRCodeReaderForQmlManage ); \
    engine.addImportPath( ":/JQQRCodeReader/" );
#endif

class QThreadPool;
class QSemaphore;
class QQuickItem;
class QQuickItemGrabResult;

class JQQRCodeReaderForQmlManage: public JQQRCodeReader
{
    Q_OBJECT
    Q_DISABLE_COPY( JQQRCodeReaderForQmlManage )
    Q_PROPERTY(int decodeQrCodeType READ decodeQrCodeType WRITE setDecodeQrCodeType)

public:
    JQQRCodeReaderForQmlManage();

    ~JQQRCodeReaderForQmlManage();

public slots:
    void analysisItem(QQuickItem *item);

private:
    QSharedPointer< QThreadPool > threadPool_;
    QSharedPointer< QSemaphore > semaphore_;
    QSharedPointer< QQuickItemGrabResult > quickItemGrabResult_;

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

