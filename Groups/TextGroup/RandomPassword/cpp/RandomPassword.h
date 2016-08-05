#ifndef __GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H__
#define __GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define RANDOMPASSWORD_INITIALIZA                                                     \
{                                                                               \
    qmlRegisterType<RandomPassword::Manage>("RandomPassword", 1, 0, "RandomPasswordManage");   \
}

namespace RandomPassword
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    QString randomPassword(const int &length, const bool &number, const bool &englishCharacters, const bool &caseSensitive, const bool &dividingLine);
};

}

#endif//__GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H__
