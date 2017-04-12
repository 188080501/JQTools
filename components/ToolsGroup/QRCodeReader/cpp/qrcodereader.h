/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H__
#define __GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H__

// Qt lib import
#include <QImage>
#include <QQuickImageProvider>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define QRCODEREADER_INITIALIZA                                                             \
{                                                                                           \
    qmlRegisterType< QRCodeReader_::Manage >( "QRCodeReader", 1, 0, "QRCodeReaderManage" ); \
}

class JQQRCodeReader;

namespace QRCodeReader_
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    QUrl chooseImage() const;

    QString decodeImage(const QUrl &imageUrl);

private:
    QSharedPointer< JQQRCodeReader > jqQRCodeReader_;
};

}

#endif//__GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H__
