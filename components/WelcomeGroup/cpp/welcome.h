#ifndef GROUP_WELCOMEGROUP_CPP_WELCOME_H_
#define GROUP_WELCOMEGROUP_CPP_WELCOME_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define WELCOME_INITIALIZA                                               \
{                                                                       \
    qmlRegisterType<Welcome::Manage>("Welcome", 1, 0, "WelcomeManage"); \
}

namespace Welcome
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    void openGitHubLink();

    void openLatestVersionDownloadLink();
};

}

#endif//GROUP_WELCOMEGROUP_CPP_WELCOME_H_
