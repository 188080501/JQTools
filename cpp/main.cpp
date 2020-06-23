/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

// Qt lib import
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QVersionNumber>
#include <QMessageBox>

// JQLibrary import
#include "JQFoundation.h"

// JQToolsLibrary import
#include <JQToolsLibrary>

// Project lib import
#include <JQToolsManage>

// Group import
#include <WelcomeGroup>
#include <TextGroup>
#include <CalculateGroup>
#include <MakeGroup>
#include <ToolsGroup>
#include <QtGroup>

void checkVersion();

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    qputenv( "QSG_RENDER_LOOP", "basic" );
#endif

    QApplication app(argc, argv);

    if ( !JQFoundation::singleApplication( "JQTools" ) )
    {
        QTimer::singleShot( 3000, qApp, &QCoreApplication::quit );

        QMessageBox::warning(
                    nullptr,
                    QStringLiteral( "\u542F\u52A8\u5931\u8D25" ),
                    QStringLiteral( "\u7A0B\u5E8F\u5DF2\u7ECF\u542F\u52A8\n3\u79D2\u540E\u81EA\u52A8\u9000\u51FA" )
                );
        return -1;
    }

    if ( QThreadPool::globalInstance()->maxThreadCount() > 1 )
    {
        QThreadPool::globalInstance()->setMaxThreadCount( QThreadPool::globalInstance()->maxThreadCount() - 1 );
    }

    QQmlApplicationEngine engine;
    JQToolsManage jqToolsManage;

    jqToolsManage.setQmlApplicationEngine( &engine );

    // Group initializa
    WELCOMEGROUP_INITIALIZA
    TEXTGROUP_INITIALIZA
    CALCULATEGROUP_INITIALIZA
    MAKEGROUP_INITIALIZA
    TOOLSGROUP_INITIALIZA
    QTGROUP_INITIALIZA

    engine.rootContext()->setContextProperty( "JQToolsManage", &jqToolsManage );

    engine.load( QUrl( "qrc:/main.qml" ) );

    return app.exec();
}
