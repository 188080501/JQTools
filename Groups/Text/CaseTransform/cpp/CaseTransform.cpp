#include "CaseTransform.h"

// Qt lib import
#include <QColor>
#include <QUrl>
#include <QClipboard>
#include <QApplication>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace CaseTransform;

QString Manage::upper(const QString &string)
{
    return string.toUpper();
}

QString Manage::lower(const QString &string)
{
    return string.toLower();
}

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
