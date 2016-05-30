#ifndef __RandomPassword_h__
#define __RandomPassword_h__

// Qt lib import
#include <QObject>

#define RANDOMPASSWORD_INITIALIZA                                                     \
{                                                                               \
    qmlRegisterType<RandomPassword::Manage>("RandomPassword", 1, 0, "RandomPasswordManage");   \
}

namespace RandomPassword
{

class Manage: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    QString randomPassword(const int &length, const bool &number, const bool &englishCharacters, const bool &caseSensitive, const bool &dividingLine);

    void setClipboardText(const QString &string);
};

}

#endif//__RandomPassword_h__
