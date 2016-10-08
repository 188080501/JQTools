/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "casetransform.h"

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
