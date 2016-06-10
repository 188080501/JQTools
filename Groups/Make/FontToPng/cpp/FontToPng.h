#ifndef __FontToPng_h__
#define __FontToPng_h__

// C++ lib import
#include <functional>

// Qt lib import
#include <QVector>
#include <QSharedPointer>
#include <QImage>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define FONTTOPNG_INITIALIZA                                                    \
{                                                                               \
    qmlRegisterType<FontToPng::Manage>("FontToPng", 1, 0, "FontToPngManage");   \
}

namespace FontToPng
{

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
    QString familieName;

    QVector< QSharedPointer< CharPackage > > charPackages;
};

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

private:
    void loadFont(const QString fontName);

    QImage paintChar(const QString &familieName, const QSharedPointer< CharPackage > &charPackage, const QSize &size, const QColor &color);

    void makeAdaptation(const QString &familieName, const ushort &code, const QSharedPointer< CharPackage > &charPackage);
private:
    QVector< QSharedPointer< FontPackage > > fontPackages_;
};

}

#endif//__FontToPng_h__
