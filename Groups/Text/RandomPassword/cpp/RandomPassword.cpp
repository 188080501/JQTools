#include "RandomPassword.h"

// Qt lib import
#include <QCoreApplication>
#include <QDateTime>

using namespace RandomPassword;

Manage::Manage()
{
    srand( QDateTime::currentDateTime().toTime_t() + qApp->applicationFilePath().size() );
}

QString Manage::randomPassword(const int &length, const bool &number, const bool &englishCharacters, const bool &caseSensitive, const bool &dividingLine)
{
    QString password;
    QString table;

    auto numberTable = "0123456789";
    auto lowercaseCharacters = "abcdefghijklmnopqrstuvwxyz";
    auto upperCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if ( number )
    {
        table += numberTable;
    }
    if ( englishCharacters )
    {
        if ( caseSensitive )
        {
            table += lowercaseCharacters;
            table += upperCharacters;
        }
        else
        {
            table += lowercaseCharacters;
        }
    }

    if ( table.isEmpty() ) { return { }; }

    for ( auto index = 0; index < length; index++ )
    {
        if ( dividingLine && ! ( (index + 1) % 4 ) )
        {
            password += '-';
        }
        else
        {
            password += table.at( rand() % table.size() );
        }
    }

    return password;
}
