#include "CaseTransform.h"

// Qt lib import
#include <QColor>
#include <QUrl>

using namespace CaseTransform;

QString Manage::upper(const QString &string)
{
    return string.toUpper();
}

QString Manage::lower(const QString &string)
{
    return string.toLower();
}
