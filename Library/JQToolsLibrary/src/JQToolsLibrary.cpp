#include "JQToolsLibrary.h"

// Qt lib import
#include <QApplication>
#include <QClipboard>

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
