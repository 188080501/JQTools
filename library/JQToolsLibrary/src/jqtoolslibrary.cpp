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
#include <QDate>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QDebug>

QPointer< QQmlApplicationEngine > AbstractTool::qmlApplicationEngine_;

QString AbstractTool::jqToolsVersionString()
{
    const auto compileDateText = QStringLiteral( __DATE__ ).simplified();
    const auto compileDate = QLocale( QLocale::English ).toDate( compileDateText, "MMM d yyyy" );

    if ( compileDate.isValid() )
    {
        return compileDate.toString( "yy.M.d" );
    }

    return compileDateText;
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
