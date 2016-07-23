// Qt lib import
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QVersionNumber>
#include <QMessageBox>

// JQLibrary import
#include "JQFoundation.h"

#ifdef JQQMLLIB_LIB
#   include "JQQmlLib.h"
#endif

// JQToolsLibrary import
#include "JQToolsLibrary.h"

// Project lib import
#include "JQToolsManage.hpp"

// Welcome import
#include "Welcome.h"

// Text group import
#include "Utf16Transform.h"
#include "RgbStringTransform.h"
#include "CaseTransform.h"
#include "RandomPassword.h"
#include "UrlEncode.h"
#include "JsonFormat.h"

// Calculate group import
#include "HashCalculate.h"
#include "TimestampTransform.h"

// Make group import
#include "IconMaker.h"
#include "FontToPng.h"

// Tool group import
#include "LinesStatistics.h"
#include "PngOptimize.h"

// Qt group import
#include "PngWarningRemover.h"
#include "PropertyMaker.h"

void checkVersion();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    checkVersion();

    if ( !JQFoundation::singleApplication( "JQTools" ) )
    {
        QMessageBox::warning(
                    nullptr,
                    QStringLiteral( "\u542F\u52A8\u5931\u8D25" ),
                    QStringLiteral( "\u7A0B\u5E8F\u5DF2\u7ECF\u542F\u52A8" )
                );
        return -1;
    }

    if ( QThreadPool::globalInstance()->maxThreadCount() > 1 )
    {
        QThreadPool::globalInstance()->setMaxThreadCount( QThreadPool::globalInstance()->maxThreadCount() - 1 );
    }

    QQmlApplicationEngine engine;
    JQToolsManage jqToolsManage;

    // Welcome initializa
    WELCOME_INITIALIZA;

    // Text group  initializa
    UTF16TRANSFORM_INITIALIZA;
    RGBSTRINGTRANSFORM_INITIALIZA;
    CASETRANSFORM_INITIALIZA;
    RANDOMPASSWORD_INITIALIZA;
    URLENCODE_INITIALIZA;
    JSONFORMAT_INITIALIZA;

    // Calculate group initializa
    HASHCALCULATE_INITIALIZA;
    TTIMESTAMPTRANSFORM_INITIALIZA;

    // Make group initializa
    ICONMAKER_INITIALIZA;
    FONTTOPNG_INITIALIZA;

    // Tool group initializa
    LINESSTATISTICS_INITIALIZA;
    PNGOPTIMIZE_INITIALIZA;

    // Qt group initializa
    PNGWARNINGREMOVER_INITIALIZA;
    PROPERTYMAKER_INITIALIZA;

#ifdef JQQMLLIB_LIB
    JQQmlLibAddToEngine(engine)
#endif

    engine.rootContext()->setContextProperty("JQToolsManage", &jqToolsManage);

    engine.load(QUrl("qrc:/main.qml"));

    return app.exec();
}

void checkVersion()
{
#ifndef QT_NO_DEBUG
    const auto &&versionNumber = QVersionNumber::fromString( JQTOOLS_VERSIONSTRING );
    const auto &&dateTime = QDateTime::currentDateTime();

    if ( versionNumber.majorVersion() != (dateTime.date().year() % 100) ||
         versionNumber.minorVersion() != dateTime.date().month() ||
         versionNumber.microVersion() != dateTime.date().day() )
    {
        QMessageBox::warning(
                    nullptr,
                    QStringLiteral( "\u7248\u672C\u9519\u8BEF" ),
                    QStringLiteral( "\u8BF7\u9009\u62E9release\u7248\u672C\u6216\u8005\u66F4\u6539\u7248\u672C\u6807\u8BB0" )
                );
        ::exit( -1 );
    }
#endif
}
