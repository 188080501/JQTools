/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H_
#define GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H_

// Qt lib import
#include <QImage>
#include <QQuickImageProvider>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define QRCODEMAKER_INITIALIZA                                                          \
{                                                                                       \
    qmlRegisterType< QRCodeMaker::Manage >( "QRCodeMaker", 1, 0, "QRCodeMakerManage" ); \
}

namespace QRCodeMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage();

public slots:
    QString savePng(const QString &string);
};

class ImageProvider: public QQuickImageProvider
{
public:
    ImageProvider();

    ~ImageProvider() = default;

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize);
};

}

#endif//GROUP_MAKEGROUP_QRCODEMAKER_CPP_QRCODEMAKER_H_
