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
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMetaObject>
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
    const auto targetSavePath = AbstractTool::getExistingDirectory(
                QStringLiteral( "c006719b-2fec-43ab-a296-e4f9029ecddc" ),
                "\u8BF7\u9009\u62E9\u4FDD\u5B58\u8DEF\u5F84"
            );

    if ( targetSavePath.isEmpty() ) { return "cancel"; }

    targetSavePath_ = targetSavePath;

    emit targetSavePathChanged();

    return "OK";
}

QString Manage::chooseSourceIconFilePath()
{
    const auto sourceIconFilePath = AbstractTool::getOpenFileName(
        QStringLiteral( "a6974b21-e63b-49b2-9655-eb9beb713d95" ),
        "\u8BF7\u9009\u62E9\u56FE\u6807\u6587\u4EF6",
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
            this->generateOSXIconAssets();
            this->generateIOSIconAssets();
            this->generateWindowsIconAsset();
            this->generateAndroidIconAssets();
            this->generatePWAIconAssets();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
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
            this->generateOSXIconAssets();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
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
            this->generateIOSIconAssets();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
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
            this->generateWindowsIconAsset();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
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
            this->generateAndroidIconAssets();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
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
            this->generatePWAIconAssets();
        }
        catch(const bool)
        {
            reply = "saveToFileError";
            QMetaObject::invokeMethod( &eventLoop, "quit" );
            return;
        }

        reply = "OK";
        QMetaObject::invokeMethod( &eventLoop, "quit" );
    } );

    eventLoop.exec();

    return reply;
}

void Manage::generateOSXIconAssets()
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

void Manage::generateIOSIconAssets()
{
    const auto appIconSetPath = targetSavePath_ + "/iOS/AppIcon.appiconset";

    if ( !QDir().mkpath( appIconSetPath ) )
    {
        throw false;
    }

    struct IOSIconFileItem
    {
        QString fileName;
        QSize pixelSize;
    };

    const QList< IOSIconFileItem > iosIconFileItems
    {
        { "icon_20x20.png", { 20, 20 } },
        { "icon_20x20@2x.png", { 40, 40 } },
        { "icon_20x20@3x.png", { 60, 60 } },
        { "icon_29x29.png", { 29, 29 } },
        { "icon_29x29@2x.png", { 58, 58 } },
        { "icon_29x29@3x.png", { 87, 87 } },
        { "icon_40x40.png", { 40, 40 } },
        { "icon_40x40@2x.png", { 80, 80 } },
        { "icon_40x40@3x.png", { 120, 120 } },
        { "icon_60x60@2x.png", { 120, 120 } },
        { "icon_60x60@3x.png", { 180, 180 } },
        { "icon_76x76.png", { 76, 76 } },
        { "icon_76x76@2x.png", { 152, 152 } },
        { "icon_83.5x83.5@2x.png", { 167, 167 } },
        { "icon_1024x1024.png", { 1024, 1024 } },
    };

    for ( const auto &iosIconFileItem: iosIconFileItems )
    {
        this->saveToPng( appIconSetPath + "/" + iosIconFileItem.fileName, iosIconFileItem.pixelSize );
    }

    struct IOSIconSlotItem
    {
        QString fileName;
        QString idiom;
        QString pointSize;
        QString scale;
    };

    const QList< IOSIconSlotItem > iosIconSlotItems
    {
        { "icon_20x20@2x.png", "iphone", "20x20", "2x" },
        { "icon_20x20@3x.png", "iphone", "20x20", "3x" },
        { "icon_29x29@2x.png", "iphone", "29x29", "2x" },
        { "icon_29x29@3x.png", "iphone", "29x29", "3x" },
        { "icon_40x40@2x.png", "iphone", "40x40", "2x" },
        { "icon_40x40@3x.png", "iphone", "40x40", "3x" },
        { "icon_60x60@2x.png", "iphone", "60x60", "2x" },
        { "icon_60x60@3x.png", "iphone", "60x60", "3x" },
        { "icon_20x20.png", "ipad", "20x20", "1x" },
        { "icon_20x20@2x.png", "ipad", "20x20", "2x" },
        { "icon_29x29.png", "ipad", "29x29", "1x" },
        { "icon_29x29@2x.png", "ipad", "29x29", "2x" },
        { "icon_40x40.png", "ipad", "40x40", "1x" },
        { "icon_40x40@2x.png", "ipad", "40x40", "2x" },
        { "icon_76x76.png", "ipad", "76x76", "1x" },
        { "icon_76x76@2x.png", "ipad", "76x76", "2x" },
        { "icon_83.5x83.5@2x.png", "ipad", "83.5x83.5", "2x" },
        { "icon_1024x1024.png", "ios-marketing", "1024x1024", "1x" },
    };

    QJsonArray imagesJsonArray;

    for ( const auto &iosIconSlotItem: iosIconSlotItems )
    {
        QJsonObject imageJsonObject;

        imageJsonObject[ "filename" ] = iosIconSlotItem.fileName;
        imageJsonObject[ "idiom" ] = iosIconSlotItem.idiom;
        imageJsonObject[ "size" ] = iosIconSlotItem.pointSize;
        imageJsonObject[ "scale" ] = iosIconSlotItem.scale;

        imagesJsonArray << imageJsonObject;
    }

    QJsonObject infoJsonObject;
    infoJsonObject[ "author" ] = "xcode";
    infoJsonObject[ "version" ] = 1;

    QJsonObject contentsJsonObject;
    contentsJsonObject[ "images" ] = imagesJsonArray;
    contentsJsonObject[ "info" ] = infoJsonObject;

    QFile contentsFile( appIconSetPath + "/Contents.json" );

    if ( !contentsFile.open( QIODevice::WriteOnly | QIODevice::Truncate ) )
    {
        throw false;
    }

    const auto contentsJsonData = QJsonDocument( contentsJsonObject ).toJson( QJsonDocument::Indented );

    if ( contentsFile.write( contentsJsonData ) != contentsJsonData.size() )
    {
        throw false;
    }
}

void Manage::generateWindowsIconAsset()
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

void Manage::generateAndroidIconAssets()
{
    if ( !QDir().mkpath( targetSavePath_ + "/Android" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/Android/icon_36.png", { 36, 36 } );
    this->saveToPng( targetSavePath_ + "/Android/icon_72.png", { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/Android/icon_96.png", { 96, 96 } );
}

void Manage::generatePWAIconAssets()
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
