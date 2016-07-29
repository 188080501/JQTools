#include "FontToPng.h"

// Qt lib import
#include <QFontDatabase>
#include <QPainter>
#include <QFileDialog>
#include <QJsonObject>
#include <QEventLoop>
#include <QtConcurrent>
#include <QDebug>

// JQLibrary import
#include "JQFile.h"

using namespace FontToPng;

Manage::Manage():
    QQuickImageProvider( QQuickImageProvider::Image )
{ }

void Manage::begin()
{
    QEventLoop eventLoop;

    QtConcurrent::run( [ this ](){ this->loadFont( "Elusive" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "FontAwesome" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Foundation" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "GlyphiconsHalflings" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "IcoMoon" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "IconFont" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Icons8" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "IconWorks" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "JustVector" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "MaterialDesign" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Metrize" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Mfglabs" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "OpenIconic" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Socicon" ); } );
    QtConcurrent::run( [ this ](){ this->loadFont( "Typicons" ); } );

    QThreadPool threadPool;
    threadPool.setMaxThreadCount( 1 );
    QtConcurrent::run( &threadPool, [ &eventLoop, this ]()
    {
        QThreadPool::globalInstance()->waitForDone();

        this->mutex_.lock();

        std::sort(
                    this->fontPackages_.begin(),
                    this->fontPackages_.end(),
                    []( const FontPackage &a, const FontPackage &b )
                    {
                        return a.fontName < b.fontName;
                    }
                );

        this->mutex_.unlock();

        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();
}

QJsonArray Manage::getCharList(const QString &familieName, const QString &searchKey)
{
    QJsonArray result;

    for ( const auto &fontPackage: fontPackages_ )
    {
        if ( ( familieName != fontPackage.fontName ) && ( familieName != QStringLiteral("\u6240\u6709\u5B57\u4F53\u96C6") ) ) { continue; }

        for ( const auto &charPackage: fontPackage.charPackages )
        {
            if ( ( searchKey.isEmpty() ) ? ( false ) : ( !charPackage.name.contains( searchKey ) ) ) { continue; }

            result.push_back( QJsonObject( { {
                                                 { "familieName", fontPackage.familieName },
                                                 { "charCode", QString::number( charPackage.code, 16 ).toUpper() },
                                                 { "charName", charPackage.name },
                                                 { "charPreviewUrl", QString( "image://FontToPngManage/CharPreview/%1/%2" ).
                                                     arg( fontPackage.familieName ).
                                                     arg( charPackage.code ) }
                                             } } ) );
        }
    }

    return result;
}

QString Manage::saveIcon(const QString &familieName, const QString &charCodeHexString, const int &pixelSize, const QString &color)
{
    auto filePath = QFileDialog::getSaveFileName(
                nullptr,
                QStringLiteral( "请选择保存图标的路径" ),
                QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
                "*.png"
            );

    if ( filePath.isEmpty() ) { return "cancel"; }

    if ( !filePath.toLower().endsWith( ".png" ) )
    {
        filePath += ".png";
    }

    CharPackage charPackage;

    for ( const auto &fontPackage: fontPackages_ )
    {
        if ( familieName != fontPackage.familieName ) { continue; }

        const auto &&charCode = charCodeHexString.toInt( nullptr, 16 );

        if ( !fontPackage.charPackages.contains( charCode ) ) { return "error"; }

        charPackage = fontPackage.charPackages[ charCode ];
    }

    if ( !charPackage.code ) { return "error"; }

    const auto &&image = this->paintChar( familieName, charPackage, QColor( color ), QSizeF( pixelSize, pixelSize ), QSizeF( pixelSize, pixelSize ) );
    const auto &&saveSucceed = image.save( filePath, "PNG" );

    return ( saveSucceed ) ? ( "OK" ) : ( "error" );
}

void Manage::loadFont(const QString fontName)
{
    FontPackage fontPackage;

    fontPackage.fontName = fontName;
    fontPackage.ttfFilePath = QString( ":/%1/%1.ttf" ).arg( fontName );
    fontPackage.txtFilePath = QString( ":/%1/%1.txt" ).arg( fontName );

    auto fontId = QFontDatabase::addApplicationFont( fontPackage.ttfFilePath );

    fontPackage.fontId = fontId;
    fontPackage.familieName = QFontDatabase::applicationFontFamilies( fontId ).first();

    auto txtData = JQFile::readFile( fontPackage.txtFilePath );
    if ( !txtData.first ) { return; }

    auto txtLines = txtData.second.split( '\n' );
    for ( const auto &line: txtLines )
    {
        CharPackage charPackage;
        auto data = line.split( ':' );

        if ( data.size() != 2 ) { continue; }

        charPackage.code = data.first().toUShort( nullptr, 16 );
        charPackage.name = data.last();

        if ( !charPackage.code ) { continue; }

        this->makeAdaptation( fontPackage.familieName, charPackage );
        charPackage.preview = this->paintChar( fontPackage.familieName, charPackage, "#000000", { 60, 60 }, { 60, 60 } );

        fontPackage.charPackages[ charPackage.code ] = charPackage;
    }

    mutex_.lock();
    fontPackages_.push_back( fontPackage );
    mutex_.unlock();
}

QImage Manage::paintChar(const QString &familieName, const CharPackage &charPackage, const QColor &color, const QSizeF &charSize, const QSizeF &backgroundSize)
{
    QPainter patiner;
    QImage image( backgroundSize.toSize(), QImage::Format_ARGB32 );

    memset( image.bits(), 0x0, image.width() * image.height() * 4 );

    if ( !patiner.begin( &image ) ) { return image; }

    QFont font( familieName );
    font.setPixelSize( qMin( charSize.width(), charSize.height() ) * charPackage.charAdaptation.scale );

    patiner.setFont( font );
    patiner.setPen( QPen( color ) );

    patiner.drawText(
                image.width() * charPackage.charAdaptation.xOffset,
                image.height() * charPackage.charAdaptation.yOffset,
                image.width(),
                image.height(),
                Qt::AlignCenter,
                QString( QChar( charPackage.code ) )
            );

    return image;
}

void Manage::makeAdaptation(const QString &familieName, CharPackage &charPackage)
{
    QSizeF charSize( 400, 400 );
    QSizeF backgroundSize( 500, 500 );

    auto referenceImage = this->paintChar( familieName, charPackage, { "#000000" }, charSize, backgroundSize);

    qreal xStart = -1;
    qreal xEnd = backgroundSize.width();
    qreal yStart = -1;
    qreal yEnd = backgroundSize.height();

    for ( auto x = 0; ( x < backgroundSize.width() ) && ( xStart == -1 ); ++x)
    {
        for ( auto y = 0; ( y < backgroundSize.height() ) && ( xStart == -1 ); ++y)
        {
            if ( referenceImage.pixel( x, y ) )
            {
                xStart = x;
                break;
            }
        }
    }

    for ( auto x = backgroundSize.width() - 1; ( x >= 0 ) && ( xEnd == backgroundSize.width() ); --x)
    {
        for ( auto y = 0; ( y < backgroundSize.height() ) && ( xEnd == backgroundSize.width() ); ++y)
        {
            if ( referenceImage.pixel( x, y ) )
            {
                xEnd = x;
                break;
            }
        }
    }

    for ( auto y = 0; ( y < backgroundSize.height() ) && ( yStart == -1 ); y++ )
    {
        for ( auto x = 0; ( x < backgroundSize.width() ) && ( yStart == -1 ); x++ )
        {
            if ( referenceImage.pixel( x, y ) )
            {
                yStart = y;
                break;
            }
        }
    }

    for ( auto y = backgroundSize.height() - 1; ( y >= 0 ) && ( yEnd == backgroundSize.height() ); --y )
    {
        for ( auto x = 0; ( x < backgroundSize.width() ) && ( yEnd == backgroundSize.height() ); ++x )
        {
            if ( referenceImage.pixel( x, y ) )
            {
                yEnd = y;
                break;
            }
        }
    }

    charPackage.charAdaptation.xOffset = ( backgroundSize.width() - xEnd - xStart ) / charSize.width() / 2.0;
    charPackage.charAdaptation.yOffset = ( backgroundSize.height() - yEnd - yStart ) / charSize.width() / 2.0;

    if ( ( xEnd - xStart ) > ( charSize.width() * 0.85 ) )
    {
        if ( ( ( yEnd - yStart ) > ( charSize.width() * 0.85 ) ) && ( ( yEnd - yStart ) > ( xEnd - xStart ) ) )
        {
            charPackage.charAdaptation.scale = ( charSize.width() * 0.85 ) / ( yEnd - yStart );
            charPackage.charAdaptation.xOffset *= charPackage.charAdaptation.scale;
            charPackage.charAdaptation.yOffset *= charPackage.charAdaptation.scale;
        }
        else
        {
            charPackage.charAdaptation.scale = ( charSize.width() * 0.85 ) / ( xEnd - xStart );
            charPackage.charAdaptation.xOffset *= charPackage.charAdaptation.scale;
            charPackage.charAdaptation.yOffset *= charPackage.charAdaptation.scale;
        }
    }

    if ( ( charPackage.charAdaptation.xOffset >= -0.0015 ) && ( charPackage.charAdaptation.xOffset <= 0.0015 ) ) { charPackage.charAdaptation.xOffset = 0; }
    if ( ( charPackage.charAdaptation.yOffset >= -0.0015 ) && ( charPackage.charAdaptation.yOffset <= 0.0015 ) ) { charPackage.charAdaptation.yOffset = 0; }

    if ( charPackage.charAdaptation.xOffset >= 0.9985 ) { charPackage.charAdaptation.xOffset = 1; }
    if ( charPackage.charAdaptation.xOffset <= -0.9985 ) { charPackage.charAdaptation.xOffset = -1; }
    if ( charPackage.charAdaptation.yOffset >= 0.9985 ) { charPackage.charAdaptation.yOffset = 1; }
    if ( charPackage.charAdaptation.yOffset <= -0.9985 ) { charPackage.charAdaptation.yOffset = -1; }
}

QImage Manage::requestImage(const QString &id, QSize *, const QSize &)
{
    auto datas = id.split( '/' );

    if ( datas.size() < 3 ) { return { }; }

    auto mode = datas.first();

    if ( mode == "CharPreview" )
    {
        auto familieName = datas.at( 1 );

        for ( const auto &fontPackage: fontPackages_ )
        {
            if ( familieName != fontPackage.familieName ) { continue; }

            auto charCode = datas.at( 2 ).toUShort();

            if ( !fontPackage.charPackages.contains( charCode ) ) { return { }; }

            return fontPackage.charPackages[ charCode ].preview;
        }
    }

    return { };
}
