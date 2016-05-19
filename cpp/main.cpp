// Qt lib import
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QVersionNumber>

// JQLibrary import
#include "JQFoundation.h"

#ifdef JQQMLLIB_LIB
#   include "JQQmlLib.h"
#endif

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

// Project lib import
#include "JQToolsManage.hpp"

// Models import
#include "Welcome.h"
#include "PngWarningRemover.h"
#include "Utf16Transform.h"
#include "RgbStringTransform.h"
#include "HashCalculate.h"
#include "IconMaker.h"

void checkVersion();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    checkVersion();

    if ( !JQFoundation::singleApplication("JQTools") )
    {
        QMessageBox::warning( nullptr, QStringLiteral( "\u542F\u52A8\u5931\u8D25" ), QStringLiteral( "\u7A0B\u5E8F\u5DF2\u7ECF\u542F\u52A8" ) );
        return -1;
    }

    WELCOMEINITIALIZA
    PNGWARNINGREMOVERINITIALIZA
    UTF16TRANSFORMINITIALIZA
    RGBSTRINGTRANSFORMINITIALIZA
    HASHCALCULATEINITIALIZA
    ICONMAKERINITIALIZA

    QQmlApplicationEngine engine;
    JQToolsManage jqToolsManage;

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
        QMessageBox::warning( nullptr, QStringLiteral( "\u7248\u672C\u9519\u8BEF" ), QStringLiteral( "\u8BF7\u9009\u62E9release\u7248\u672C\u6216\u8005\u66F4\u6539\u7248\u672C\u6807\u8BB0" ) );
        ::exit( -1 );
    }
#endif
}
