/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "iconmaker.h"

// Qt lib import
#include <QBuffer>
#include <QDataStream>
#include <QFile>
#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QtConcurrent>

using namespace IconMaker;

Manage::Manage()
{
    targetSavePath_ = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );
    sourceIconImage_.load( ":/IconMaker/DefaultIcon.png" );
}

QString Manage::chooseTargetSavePath()
{
    const auto targetSavePath = QFileDialog::getExistingDirectory( nullptr, "\u8BF7\u9009\u62E9\u4FDD\u5B58\u8DEF\u5F84", QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) );

    if ( targetSavePath.isEmpty() ) { return "cancel"; }

    targetSavePath_ = targetSavePath;

    emit targetSavePathChanged();

    return "OK";
}

QString Manage::choostSourceIconFilePath()
{
    const auto sourceIconFilePath = QFileDialog::getOpenFileName(
        nullptr,
        "\u8BF7\u9009\u62E9\u56FE\u6807\u6587\u4EF6",
        QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ),
        "*.png *.jpg *.jpeg *.bmp" );

    if ( sourceIconFilePath.isEmpty() ) { return "cancel"; }

    QImage sourceIconImage;

    if ( !sourceIconImage.load( sourceIconFilePath ) ) { return "openFail"; }

    sourceIconFilePath_ = sourceIconFilePath;
    sourceIconImage_ = sourceIconImage;

    emit sourceIconFilePathChanged();

    return "OK";
}

QString Manage::makeAll()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeOSX();
            this->realMakeIOS();
            this->realMakeWindows();
            this->realMakeAndroid();
            this->realMakePWA();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makeOSX()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeOSX();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makeIOS()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeIOS();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makeWindows()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ =, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeWindows();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makeAndroid()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeAndroid();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makePWA()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakePWA();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            eventLoop.quit();
            return;
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

void Manage::realMakeOSX()
{
    if ( !QDir().mkpath( targetSavePath_ + "/OSX/icon.iconset" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_16x16.png",      { 16, 16 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_16x16@2x.png",   { 32, 32 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_32x32.png",      { 32, 32 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_32x32@2x.png",   { 64, 64 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_128x128.png",    { 128, 128 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_128x128@2x.png", { 256, 256 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_256x256.png",    { 256, 256 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_256x256@2x.png", { 512, 512 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_512x512.png",    { 512, 512 } );
    this->saveToPng( targetSavePath_ + "/OSX/icon.iconset/icon_512x512@2x.png", { 1024, 1024 } );

#ifdef Q_OS_MAC
    const auto escapedTargetSavePath = QString( targetSavePath_ ).replace( ' ', "\\ " );
    system( QString( "iconutil -c icns " + escapedTargetSavePath + "/OSX/icon.iconset" ).toUtf8().data() );
#endif
}

void Manage::realMakeIOS()
{
    if ( !QDir().mkpath( targetSavePath_ + "/iOS" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/iOS/icon_29x29.png",     { 29, 29 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_29x29@2x.png",  { 58, 58 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_29x29@3x.png",  { 87, 87 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_40x40.png",     { 40, 40 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_40x40@2x.png",  { 80, 80 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_40x40@3x.png",  { 120, 120 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_50x50.png",     { 50, 50 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_50x50@2x.png",  { 100, 100 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_57x57.png",     { 57, 57 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_57x57@2x.png",  { 114, 114 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_60x60@2x.png",  { 120, 120 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_60x60@3x.png",  { 180, 180 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_72x72.png",     { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_72x72@2x.png",  { 144, 144 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_76x76.png",     { 76, 76 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_76x76@2x.png",  { 152, 152 } );
    this->saveToPng( targetSavePath_ + "/iOS/icon_83.5x83.5@2x.png",{ 167, 167 } );
    this->saveToJpg( targetSavePath_ + "/iOS/icon_1024x1024.jpg", { 1024, 1024 } );

    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_2x_640x960.png", { 640, 960 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R4_640x1136.png", { 640, 1136 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R4.7_750x1334.png", { 750, 1334 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R5.5_1242x2208.png", { 1242, 2208 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_iPad_Portrait_1536x2048.png", { 1536, 2048 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_iPad_Landscape_2048x1536.png", { 2048, 1536 } );
}

void Manage::realMakeWindows()
{
    if ( !QDir().mkpath( targetSavePath_ + "/Windows" ) )
    {
        throw false;
    }

    const QList< QSize > iconSizes
    {
        { 16, 16 },
        { 20, 20 },
        { 24, 24 },
        { 32, 32 },
        { 40, 40 },
        { 48, 48 },
        { 64, 64 },
        { 72, 72 },
        { 80, 80 },
        { 96, 96 },
        { 128, 128 },
        { 256, 256 },
    };

    QList< QByteArray > iconImageDataList;

    for ( const auto &iconSize: iconSizes )
    {
        QByteArray iconImageData;
        QBuffer iconDataBuffer( &iconImageData );

        if ( !iconDataBuffer.open( QIODevice::WriteOnly ) )
        {
            throw false;
        }

        const auto scaledIconImage = sourceIconImage_.scaled(
            iconSize,
            Qt::IgnoreAspectRatio,
            Qt::SmoothTransformation
        ).convertToFormat( QImage::Format_ARGB32 );

        if ( !scaledIconImage.save( &iconDataBuffer, "PNG" ) )
        {
            throw false;
        }

        iconImageDataList << iconImageData;
    }

    QFile iconFile( targetSavePath_ + "/Windows/icon.ico" );

    if ( !iconFile.open( QIODevice::WriteOnly ) )
    {
        throw false;
    }

    QDataStream iconStream( &iconFile );
    iconStream.setByteOrder( QDataStream::LittleEndian );

    iconStream << static_cast< quint16 >( 0 );
    iconStream << static_cast< quint16 >( 1 );
    iconStream << static_cast< quint16 >( iconSizes.size() );

    quint32 imageDataOffset = static_cast< quint32 >( 6 + ( iconSizes.size() * 16 ) );

    for ( int index = 0; index < iconSizes.size(); ++index )
    {
        const auto iconWidth = iconSizes[ index ].width();
        const auto iconHeight = iconSizes[ index ].height();
        const auto iconDataSize = iconImageDataList[ index ].size();
        const auto icoWidth = static_cast< quint8 >( ( iconWidth >= 256 ) ? 0 : iconWidth );
        const auto icoHeight = static_cast< quint8 >( ( iconHeight >= 256 ) ? 0 : iconHeight );

        iconStream << icoWidth;
        iconStream << icoHeight;
        iconStream << static_cast< quint8 >( 0 );
        iconStream << static_cast< quint8 >( 0 );
        iconStream << static_cast< quint16 >( 1 );
        iconStream << static_cast< quint16 >( 32 );
        iconStream << static_cast< quint32 >( iconDataSize );
        iconStream << imageDataOffset;

        imageDataOffset += static_cast< quint32 >( iconDataSize );
    }

    for ( const auto &iconImageData: std::as_const( iconImageDataList ) )
    {
        if ( iconStream.writeRawData( iconImageData.constData(), iconImageData.size() ) != iconImageData.size() )
        {
            throw false;
        }
    }
}

void Manage::realMakeAndroid()
{
    if ( !QDir().mkpath( targetSavePath_ + "/Android" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/Android/icon_36.png", { 36, 36 } );
    this->saveToPng( targetSavePath_ + "/Android/icon_72.png", { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/Android/icon_96.png", { 96, 96 } );
}

void Manage::realMakePWA()
{
    if ( !QDir().mkpath( targetSavePath_ + "/PWA" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/PWA/icon_16.png", { 16, 16 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_48.png", { 48, 48 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_72.png", { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_96.png", { 96, 96 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_128.png", { 128, 128 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_144.png", { 144, 144 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_168.png", { 168, 168 } );
    this->saveToPng( targetSavePath_ + "/PWA/icon_192.png", { 192, 192 } );
}

void Manage::saveToPng(const QString &targetFilePath, const QSize &size)
{
    if ( !sourceIconImage_.scaled( size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ).save( targetFilePath, "PNG" ) )
    {
        throw false;
    }
}

void Manage::saveToEmptyPng(const QString &targetFilePath, const QSize &size)
{
    QImage image( size, QImage::Format_ARGB32 );

#if QT_VERSION >= QT_VERSION_CHECK( 5, 10, 0)
    memset( image.bits(), 0xff, static_cast< size_t >( image.sizeInBytes() ) );
#else
    memset( image.bits(), 0xff, static_cast< size_t >( image.byteCount() ) );
#endif

    if ( !image.save( targetFilePath, "PNG" ) )
    {
        throw false;
    }
}

void Manage::saveToJpg(const QString &targetFilePath, const QSize &size)
{
    if ( !sourceIconImage_.scaled( size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ).save( targetFilePath, "JPG" ) )
    {
        throw false;
    }
}
