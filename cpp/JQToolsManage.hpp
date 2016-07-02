#ifndef __JQToolsManage_hpp__
#define __JQToolsManage_hpp__

// Qt ib import
#include <QObject>
#include <QEventLoop>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

class JQToolsManage: public AbstractTool
{
    Q_OBJECT

public:
    JQToolsManage() = default;

    ~JQToolsManage() = default;

public slots:
    void eventLoopWhile()
    {
        QEventLoop eventLoop;
        while( eventLoop.processEvents() );
    }
};

#endif//__JQToolsManage_hpp__
