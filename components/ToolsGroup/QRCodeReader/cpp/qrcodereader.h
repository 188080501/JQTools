/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H_
#define GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H_

// Qt lib import
#include <QImage>
#include <QQuickImageProvider>

// JQToolsLibrary import
#include <JQToolsLibrary>

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

#endif//GROUP_MAKEGROUP_QRCODEREADER_CPP_QRCODEREADER_H_
