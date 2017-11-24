/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "jqtoolslibrary.h"

// Qt lib import
#include <QApplication>
#include <QClipboard>
#include <QQmlApplicationEngine>
#include <QDebug>

QPointer< QQmlApplicationEngine > AbstractTool::qmlApplicationEngine_;

QString AbstractTool::jqToolsVersionString()
{
    return JQTOOLS_VERSIONSTRING;
}

QString AbstractTool::clipboardText()
{
    return qApp->clipboard()->text();
}

void AbstractTool::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}

void AbstractTool::setQmlApplicationEngine(QQmlApplicationEngine *qmlApplicationEngine)
{
    qmlApplicationEngine_ = qmlApplicationEngine;
}

QPointer< QQmlApplicationEngine > AbstractTool::qmlApplicationEngine()
{
    return qmlApplicationEngine_;
}
