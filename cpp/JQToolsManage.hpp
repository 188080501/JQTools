#ifndef __JQToolsManage_hpp__
#define __JQToolsManage_hpp__

// Qt ib import
#include <QObject>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

class JQToolsManage: public QObject
{
    Q_OBJECT

public:
    JQToolsManage() = default;

    ~JQToolsManage() = default;

public slots:
    QString jqToolsVersionString() const { return JQTOOLS_VERSIONSTRING; }
};

#endif//__JQToolsManage_hpp__
