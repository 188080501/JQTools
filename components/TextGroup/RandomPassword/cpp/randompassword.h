/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H_
#define GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

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

#endif//GROUP_TEXTGROUP_RANDOMPASSWORD_CPP_RANDOMPASSWORD_H_
