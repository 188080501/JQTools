/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TOOLSGROUP_LINESSTATISTICS_CPP_LINESSTATISTICS_H_
#define GROUP_TOOLSGROUP_LINESSTATISTICS_CPP_LINESSTATISTICS_H_

// Qt lib import
#include <QJsonObject>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define LINESSTATISTICS_INITIALIZA                                                              \
{                                                                                               \
    qmlRegisterType<LinesStatistics::Manage>("LinesStatistics", 1, 0, "LinesStatisticsManage"); \
}

namespace LinesStatistics
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QJsonObject statisticsLines(const QJsonArray &suffixs);
};

}

#endif//GROUP_TOOLSGROUP_LINESSTATISTICS_CPP_LINESSTATISTICS_H_
