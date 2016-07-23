#ifndef __GROUP_TOOLS_LINESSTATISTICS_CPP_LINESSTATISTICS_H__
#define __GROUP_TOOLS_LINESSTATISTICS_CPP_LINESSTATISTICS_H__

// Qt lib import
#include <QJsonObject>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

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

#endif//__GROUP_TOOLS_LINESSTATISTICS_CPP_LINESSTATISTICS_H__
