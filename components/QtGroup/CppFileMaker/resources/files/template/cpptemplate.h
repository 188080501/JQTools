#ifndef __%MACROPROTECTSPREFIX%_%CLASSNAME%_H__
#define __%MACROPROTECTSPREFIX%_%CLASSNAME%_H__

// Qt lib import
#include <QObject>

class %ClassName%: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( %ClassName% )

public:
    %ClassName%() = default;

    ~%ClassName%() = default;

public slots:
    //...

private:
    //...
};

// .inc include
#include "%classname%.inc"

#endif//__%MACROPROTECTSPREFIX%_%CLASSNAME%_H__
