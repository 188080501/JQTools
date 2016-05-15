#ifndef __PngWarningRemover_h__
#define __PngWarningRemover_h__

// Qt lib import
#include <QObject>

#define PNGWARNINGREMOVERINITIALIZA                                                                     \
{                                                                                                       \
    qmlRegisterType<PngWarningRemover::Manage>("PngWarningRemover", 1, 0, "PngWarningRemoverManage");   \
}

namespace PngWarningRemover
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage();

public slots:
    void conversationPng();
};

}

#endif//__PngWarningRemover_h__
