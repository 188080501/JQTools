/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_MAKEGROUP_BARCODEMAKER_CPP_BARCODEMAKER_H_
#define GROUP_MAKEGROUP_BARCODEMAKER_CPP_BARCODEMAKER_H_

// Qt lib import
#include <QImage>
#include <QQuickImageProvider>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define BARCODEMAKER_INITIALIZA                                                             \
{                                                                                           \
    qmlRegisterType< BarcodeMaker::Manage >( "BarcodeMaker", 1, 0, "BarcodeMakerManage" );  \
}

namespace BarcodeMaker
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

#endif//GROUP_MAKEGROUP_BARCODEMAKER_CPP_BARCODEMAKER_H_
