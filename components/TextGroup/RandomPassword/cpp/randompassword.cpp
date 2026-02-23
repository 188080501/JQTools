/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "randompassword.h"

// Qt lib import
#include <QDateTime>

using namespace RandomPassword;

Manage::Manage():
    randomGenerator_( static_cast< quint32 >( QDateTime::currentMSecsSinceEpoch() ) )
{ }

QString Manage::randomPassword(const int length, const bool number, const bool englishCharacters, const bool includeUppercaseLetters, const bool dividingLine)
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
        if ( includeUppercaseLetters )
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
            password += table.at( randomGenerator_.bounded( table.size() ) );
        }
    }

    return password;
}
