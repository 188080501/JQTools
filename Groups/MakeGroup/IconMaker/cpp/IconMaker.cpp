#include "IconMaker.h"

// Qt lib import
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
    const auto &&targetSavePath = QFileDialog::getExistingDirectory( nullptr, "\u8BF7\u9009\u62E9\u4FDD\u5B58\u8DEF\u5F84", QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ) );

    if ( targetSavePath.isEmpty() ) { return "cancel"; }

    targetSavePath_ = targetSavePath;

    emit targetSavePathChanged();

    return "OK";
}

QString Manage::choostSourceIconFilePath()
{
    const auto &&sourceIconFilePath = QFileDialog::getOpenFileName( nullptr, "\u8BF7\u9009\u62E9\u56FE\u6807\u6587\u4EF6", QStandardPaths::writableLocation( QStandardPaths::DesktopLocation ), "*.png" );

    if ( sourceIconFilePath.isEmpty() ) { return "cancel"; }

    QImage sourceIconImage;

    if ( !sourceIconImage.load( sourceIconFilePath, "PNG" ) ) { return "openFail"; }

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
//            this->realMakeWindows();
            this->realMakeWP();
            this->realMakeAndroid();
        }
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
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
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
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
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
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

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
//            this->realMakeWindows();
        }
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
        }

        reply = "OK";
        eventLoop.quit();
    } );

    eventLoop.exec();

    return reply;
}

QString Manage::makeWP()
{
    QEventLoop eventLoop;
    QString reply;

    QtConcurrent::run( [ this, &eventLoop, &reply ]()
    {
        try
        {
            this->realMakeWP();
        }
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
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
        catch(const bool &)
        {
            reply = "saveToFileError";
            eventLoop.quit();
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
    system( QString( "iconutil -c icns " + QString( targetSavePath_.replace( ' ', "\\ " ) + "/OSX/icon.iconset" ) ).toUtf8().data() );
#endif
}

void Manage::realMakeIOS()
{
    if ( !QDir().mkpath( targetSavePath_ + "/iOS" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/iOS/Icon_29x29.png",     { 29, 29 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_29x29@2x.png",  { 58, 58 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_29x29@3x.png",  { 87, 87 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_40x40.png",     { 40, 40 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_40x40@2x.png",  { 80, 80 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_40x40@3x.png",  { 120, 120 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_50x50.png",     { 50, 50 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_50x50@2x.png",  { 100, 100 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_57x57.png",     { 57, 57 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_57x57@2x.png",  { 114, 114 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_60x60@2x.png",  { 120, 120 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_60x60@3x.png",  { 180, 180 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_72x72.png",     { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_72x72@2x.png",  { 144, 144 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_76x76.png",     { 76, 76 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_76x76@2x.png",  { 152, 152 } );
    this->saveToPng( targetSavePath_ + "/iOS/Icon_83.5x83.5@2x.png",{ 167, 167 } );
    this->saveToJpg( targetSavePath_ + "/iOS/Icon_1024x1024.jpg", { 1024, 1024 } );

    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_2x_640x960.png", { 640, 960 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R4_640x1136.png", { 640, 1136 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R4.7_750x1334.png", { 750, 1334 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_R5.5_1242x2208.png", { 1242, 2208 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_iPad_Portrait_1536x2048.png", { 1536, 2048 } );
    this->saveToEmptyPng( targetSavePath_ + "/iOS/LaunchImage_iPad_Landscape_2048x1536.png", { 2048, 1536 } );
}

void Manage::realMakeWindows() // TODO
{
//    if ( !QDir().mkpath( targetSavePath_ + "/Windows" ) )
//    {
//        throw false;
//    }

//    this->saveToIco( targetSavePath_ + "/Windows/Icon.ico", { 0, 0 } );
}

void Manage::realMakeWP()
{
    if ( !QDir().mkpath( targetSavePath_ + "/WP" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/WP/logo_44x44.png",   { 44, 44 } );
    this->saveToPng( targetSavePath_ + "/WP/logo_71x71.png",   { 71, 71 } );
    this->saveToPng( targetSavePath_ + "/WP/logo_480x800.png", { 480, 480 } );
    this->saveToPng( targetSavePath_ + "/WP/logo_large.png",   { 150, 150 } );
    this->saveToPng( targetSavePath_ + "/WP/logo_store.png",   { 50, 50 } );
}

void Manage::realMakeAndroid()
{
    if ( !QDir().mkpath( targetSavePath_ + "/Android" ) )
    {
        throw false;
    }

    this->saveToPng( targetSavePath_ + "/Android/Icon_36.png", { 36, 36 } );
    this->saveToPng( targetSavePath_ + "/Android/Icon_72.png", { 72, 72 } );
    this->saveToPng( targetSavePath_ + "/Android/Icon_96.png", { 96, 96 } );
}

void Manage::saveToIco(const QString &targetFilePath, const QSize &size)
{
    if ( !sourceIconImage_.scaled( size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ).save( targetFilePath, "JPG" ) )
    {
        throw false;
    }
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
    memset( image.bits(), 0xff, image.byteCount() );

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
