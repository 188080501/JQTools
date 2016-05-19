#ifndef __Welcome_h__
#define __Welcome_h__

// Qt lib import
#include <QObject>

#define WELCOMEINITIALIZA                                               \
{                                                                       \
    qmlRegisterType<Welcome::Manage>("Welcome", 1, 0, "WelcomeManage"); \
}

namespace Welcome
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString jqToolsVersion();

    void openGitHubLink();

    void openLatestVersionDownloadLink();
};

}

#endif//__Welcome_h__
