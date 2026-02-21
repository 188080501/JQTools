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
#include <QMessageBox>
#include <QTimer>
#include <QLockFile>
#include <QStandardPaths>

// JQToolsLibrary import
#include <JQToolsLibrary>

// Group import
#include <WelcomeGroup>
#include <TextGroup>
#include <CalculateGroup>
#include <ImageGroup>
#include <ToolsGroup>
#include <QRCodeGroup>
#include <QtGroup>

bool checkSingletonFlag(const QString &flag)
{
    auto file = new QLockFile( QString( "%1/%2" ).arg( QStandardPaths::writableLocation( QStandardPaths::TempLocation ), flag ) );
    if ( file->tryLock() )
    {
        return true;
    }

    delete file;
    return false;
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    qputenv( "QSG_RENDER_LOOP", "basic" );
#endif

    QApplication app(argc, argv);

    if ( !checkSingletonFlag( "8a6f4ab6-68d7-4a09-9e89-0e651f573b69" ) )
    {
        QTimer::singleShot( 3000, qApp, &QCoreApplication::quit );

        QMessageBox::warning(
                    nullptr,
                    QStringLiteral( "\u542F\u52A8\u5931\u8D25" ),
                    QStringLiteral( "\u7A0B\u5E8F\u5DF2\u7ECF\u542F\u52A8\n3\u79D2\u540E\u81EA\u52A8\u9000\u51FA" )
                );
        return -1;
    }

    QQmlApplicationEngine engine;
    app.setProperty( "qmlEngine", QVariant::fromValue( &engine ) );

    // Group initializa
    WELCOMEGROUP_INITIALIZA
    TEXTGROUP_INITIALIZA
    CALCULATEGROUP_INITIALIZA
    IMAGEGROUP_INITIALIZA
    TOOLSGROUP_INITIALIZA
    QRCODEGROUP_INITIALIZA
    QTGROUP_INITIALIZA

    engine.load( QUrl( "qrc:/main.qml" ) );

    return app.exec();
}
