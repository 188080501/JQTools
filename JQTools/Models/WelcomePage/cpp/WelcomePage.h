#ifndef __WelcomePage_h__
#define __WelcomePage_h__

// Qt lib import
#include <QObject>

#define WELCOMEPAGEINITIALIZA                                                       \
{                                                                                   \
    qmlRegisterType<WelcomePage::Manage>("WelcomePage", 1, 0, "WelcomePageManage"); \
}

namespace WelcomePage
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage();

public slots:
    QString jqToolsVersion();

    void openGitHubLink();

    void openDownloadLink();
};

}

#endif//__WelcomePage_h__
