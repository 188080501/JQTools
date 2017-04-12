/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __JQToolsLibrary_h__
#define __JQToolsLibrary_h__

// Qt lib import
#include <QObject>
#include <QPointer>

#define JQTOOLS_VERSIONSTRING "17.4.12"

class QQmlApplicationEngine;

class AbstractTool: public QObject
{
    Q_OBJECT

public slots:
    QString jqToolsVersionString();

    QString clipboardText();

    void setClipboardText(const QString &string);

    static void setQmlApplicationEngine(QQmlApplicationEngine *qmlApplicationEngine);

    static QPointer< QQmlApplicationEngine > qmlApplicationEngine();

private:
    static QPointer< QQmlApplicationEngine > qmlApplicationEngine_;
};

#endif//__JQToolsLibrary_h__
