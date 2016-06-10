#include "FontToPng.h"

// Qt lib import
#include <QFontDatabase>
#include <QPainter>
#include <QDebug>

// JQLibrary import
#include "JQFile.h"

using namespace FontToPng;

Manage::Manage()
{
//    this->loadFont( "Elusive" );
    this->loadFont( "FontAwesome" );
//    this->loadFont( "Foundation" );
//    this->loadFont( "GlyphiconsHalflings" );
//    this->loadFont( "IcoMoon" );
//    this->loadFont( "IconFont" );
//    this->loadFont( "Icons8" );
//    this->loadFont( "IconWorks" );
//    this->loadFont( "JustVector" );
//    this->loadFont( "MaterialDesign" );
//    this->loadFont( "Metrize" );
//    this->loadFont( "Mfglabs" );
//    this->loadFont( "OpenIconic" );
//    this->loadFont( "Socicon" );
//    this->loadFont( "Typicons" );
}

void Manage::loadFont(const QString fontName)
{
    QSharedPointer< FontPackage > fontPackage( new FontPackage );

    fontPackage->fontName = fontName;
    fontPackage->ttfFilePath = QString( ":/%1/%1.ttf" ).arg( fontName );
    fontPackage->txtFilePath = QString( ":/%1/%1.txt" ).arg( fontName );

    auto fontId = QFontDatabase::addApplicationFont( fontPackage->ttfFilePath );

    fontPackage->fontId = fontId;
    fontPackage->familieName = QFontDatabase::applicationFontFamilies( fontId ).first();

    auto txtData = JQFile::readFile( fontPackage->txtFilePath );
    if ( !txtData.first ) { return; }

    auto txtLines = txtData.second.split( '\n' );
    for( const auto &line: txtLines )
    {
        QSharedPointer< CharPackage > charPackage( new CharPackage );
        auto data = line.split( ':' );

        if ( data.size() != 2 ) { continue; }

        charPackage->code = data.first().toUShort( nullptr, 16 );
        charPackage->name = data.last();

        if ( !charPackage->code ) { continue; }

        this->makeAdaptation( fontPackage->familieName, charPackage->code, charPackage );
        charPackage->preview = this->paintChar( fontPackage->familieName, charPackage, { 100, 100 }, "#000000" );
    }

    fontPackages_.push_back( fontPackage );
}

QImage Manage::paintChar(const QString &familieName, const QSharedPointer< CharPackage > &charPackage, const QSize &size, const QColor &color)
{
    QPainter patiner;
    QImage image( size, QImage::Format_ARGB32 );

    memset( image.bits(), 0x0, image.width() * image.height() * 4 );

    if ( !patiner.begin( &image ) ) { return image; }

    patiner.setFont( QFont( familieName ) );
    patiner.setPen( QPen( color ) );

    patiner.drawText( 0, 0, image.width(), image.height(), Qt::AlignCenter, QString().append( QChar( charPackage->code ) ) );

    return image;
}

void Manage::makeAdaptation(const QString &familieName, const ushort &code, const QSharedPointer< CharPackage > &charPackage)
{
    //...
}
