#ifndef __LinesStatistics_h__
#define __LinesStatistics_h__

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

#endif//__LinesStatistics_h__
