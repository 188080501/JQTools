/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_QTGROUP_CPPFILEMAKER_CPP_CPPFILEMAKER_H__
#define __GROUP_QTGROUP_CPPFILEMAKER_CPP_CPPFILEMAKER_H__

// C++ lib import
#include <functional>

// Qt lib import
#include <QMap>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define CPPFILEMAKER_INITIALIZA                                                         \
{                                                                                       \
    qmlRegisterType<CppFileMaker::Manage>("CppFileMaker", 1, 0, "CppFileMakerManage");  \
}

namespace CppFileMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString make(
            const QString &macroProtectsPrefix,
            const QString &className,
            const bool &qmlExpand
        );

    QString getTemplateData(
            const QString &templateFilePath,
            const QString &macroProtectsPrefix,
            const QString &className
        );
};

}

#endif//__GROUP_QTGROUP_CPPFILEMAKER_CPP_CPPFILEMAKER_H__
