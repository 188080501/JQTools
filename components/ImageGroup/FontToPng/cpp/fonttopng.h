/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_IMAGEGROUP_FONTTOPNG_CPP_FONTTOPNG_H_
#define GROUP_IMAGEGROUP_FONTTOPNG_CPP_FONTTOPNG_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QVector>
#include <QMap>
#include <QImage>
#include <QQuickImageProvider>
#include <QPointer>
#include <QJsonArray>
#include <QMutex>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define FONTTOPNG_INITIALIZA                                                        \
{                                                                                   \
    auto fontToPngManage = new FontToPng::Manage;                                   \
    auto fontToPngImageProvider = new FontToPng::ImageProvider( fontToPngManage );  \
    engine.addImageProvider("FontToPngManage", fontToPngImageProvider);             \
    engine.rootContext()->setContextProperty("FontToPngManage", fontToPngManage);   \
}

namespace FontToPng
{

class Manage;

struct CharAdaptation
{
    qreal xOffset = 0;
    qreal yOffset = 0;
    qreal scale = 1;
};

struct CharPackage
{
    ushort code;
    QString name;

    CharAdaptation charAdaptation;
    QImage preview;
};

struct FontPackage
{
    QString fontName;
    QString ttfFilePath;
    QString txtFilePath;

    int fontId;
    QString fontFamilyName;

    QMap< ushort, CharPackage > charPackages;
};

class ImageProvider: public QQuickImageProvider
{
public:
    explicit ImageProvider(Manage *manage);

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

private:
    QPointer< Manage > manage_;
};

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)
    friend class ImageProvider;

public:
    Manage();

    ~Manage() = default;

public slots:
    void begin();

    QJsonArray getCharList(const QString &fontName, const QString &searchKey);

    QString saveIcon(const QString &fontFamilyName, const QString &charCodeHexString, const int pixelSize, const QString &color);

private:
    void loadFont(const QString fontName);

    QImage paintChar(const QString &fontFamilyName, const CharPackage &charPackage, const QColor &color, const QSizeF &charSize, const QSizeF &backgroundSize, const bool moreProcess);

    void makeAdaptation(const QString &fontFamilyName, CharPackage &charPackage);

    QImage requestImage(const QString &id, QSize *, const QSize &);

private:
    QVector< FontPackage > fontPackages_;
    QMutex mutex_;
};

}

#endif//GROUP_IMAGEGROUP_FONTTOPNG_CPP_FONTTOPNG_H_
