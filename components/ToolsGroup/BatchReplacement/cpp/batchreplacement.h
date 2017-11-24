/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENT_H_
#define GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENT_H_

// Qt lib import
#include <QJsonObject>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define BATCHREPLACEMENT_INITIALIZA                                                              \
{                                                                                               \
    qmlRegisterType<BatchReplacement::Manage>("BatchReplacement", 1, 0, "BatchReplacementManage"); \
}

namespace BatchReplacement
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QJsonObject startBatchReplacement(
            const QJsonArray &suffixs,
            const QString &sourceKey,
            const QString &targetKey,
            const bool &multiCase
        );
};

}

#endif//GROUP_TOOLSGROUP_BATCHREPLACEMENT_CPP_BATCHREPLACEMENT_H_
