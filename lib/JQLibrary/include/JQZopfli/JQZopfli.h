/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#ifndef __JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__
#define __JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__

// Qt lib import
#include <QString>

namespace JQZopfli
{

struct OptimizeResult
{
    bool optimizeSucceed = false;

    int originalSize = 0;
    int resultSize = 0;

    qreal compressionRatio = 0.0;
    int timeConsuming = 0;
};

OptimizeResult optimize(const QString &originalFilePath, const QString &resultFilePath);

}

#endif//__JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__
