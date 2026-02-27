/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "randompassword.h"

// Qt lib import
#include <QList>
#include <QSet>
#include <QRandomGenerator>

using namespace RandomPassword;

namespace
{

QString uniqueCharacters(const QString &characters)
{
    QString result;
    QSet< QChar > existsCharacters;

    for ( const auto character: characters )
    {
        if ( existsCharacters.contains( character ) ) { continue; }

        existsCharacters.insert( character );
        result.append( character );
    }

    return result;
}

QString removeAmbiguousCharacters(const QString &characters)
{
    static const QSet< QChar > ambiguousCharacters {
        '0',
        'O',
        'o',
        '1',
        'l',
        'I',
        '|'
    };

    QString result;
    for ( const auto character: characters )
    {
        if ( ambiguousCharacters.contains( character ) ) { continue; }

        result.append( character );
    }

    return result;
}

QChar randomCharacterFromTable(const QString &table)
{
    if ( table.isEmpty() ) { return QChar(); }

    return table.at( QRandomGenerator::system()->bounded( table.size() ) );
}

void shuffleString(QString &string)
{
    if ( string.size() < 2 ) { return; }

    for ( auto index = string.size() - 1; index > 0; --index )
    {
        const auto swapIndex = QRandomGenerator::system()->bounded( index + 1 );
        const auto currentCharacter = string.at( index );
        string[ index ] = string.at( swapIndex );
        string[ swapIndex ] = currentCharacter;
    }
}

int pureCharacterLengthFromTotalLength(const int totalLength)
{
    if ( totalLength <= 0 ) { return 0; }

    // 每4位中的第4位为分割线，长度需要包含分割线
    return totalLength - ( totalLength / 4 );
}

QString addDividingLine(const QString &source, const int totalLength)
{
    if ( source.isEmpty() || ( totalLength <= 0 ) ) { return { }; }

    QString result;
    auto sourceIndex = 0;

    for ( auto index = 0; index < totalLength; ++index )
    {
        if ( ( index > 0 ) && !( ( index + 1 ) % 4 ) )
        {
            result += '-';
            continue;
        }

        if ( sourceIndex >= source.size() ) { break; }
        result += source.at( sourceIndex );
        ++sourceIndex;
    }

    return result;
}

}

QString Manage::randomPassword(
        const int length,
        const bool number,
        const bool englishCharacters,
        const bool includeUppercaseLetters,
        const bool includeSpecialCharacters,
        const QString &customSpecialCharacters,
        const bool excludeAmbiguousCharacters,
        const bool ensureEachSelectedType,
        const bool dividingLine
    )
{
    if ( length <= 0 ) { return { }; }

    auto pureCharacterLength = length;
    if ( dividingLine )
    {
        pureCharacterLength = pureCharacterLengthFromTotalLength( length );
        if ( pureCharacterLength <= 0 ) { return { }; }
    }

    auto numberTable = uniqueCharacters( QStringLiteral( "0123456789" ) );
    auto lowercaseCharacters = uniqueCharacters( QStringLiteral( "abcdefghijklmnopqrstuvwxyz" ) );
    auto upperCharacters = uniqueCharacters( QStringLiteral( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) );
    auto specialCharacters = customSpecialCharacters.trimmed();
    if ( specialCharacters.isEmpty() )
    {
        specialCharacters = QStringLiteral( "!@#$%^&*()-_=+[]{}:,.?" );
    }
    specialCharacters = uniqueCharacters( specialCharacters );

    if ( excludeAmbiguousCharacters )
    {
        numberTable = removeAmbiguousCharacters( numberTable );
        lowercaseCharacters = removeAmbiguousCharacters( lowercaseCharacters );
        upperCharacters = removeAmbiguousCharacters( upperCharacters );
        specialCharacters = removeAmbiguousCharacters( specialCharacters );
    }

    QList< QString > tableList;
    if ( number && !numberTable.isEmpty() )
    {
        tableList.push_back( numberTable );
    }

    if ( englishCharacters && !lowercaseCharacters.isEmpty() )
    {
        tableList.push_back( lowercaseCharacters );
    }

    if ( englishCharacters && includeUppercaseLetters && !upperCharacters.isEmpty() )
    {
        tableList.push_back( upperCharacters );
    }

    if ( includeSpecialCharacters && !specialCharacters.isEmpty() )
    {
        tableList.push_back( specialCharacters );
    }

    if ( tableList.isEmpty() ) { return { }; }
    if ( ensureEachSelectedType && ( pureCharacterLength < tableList.size() ) ) { return { }; }

    QString allTable;
    for ( const auto &table: tableList )
    {
        allTable += table;
    }
    allTable = uniqueCharacters( allTable );
    if ( allTable.isEmpty() ) { return { }; }

    QString password;

    if ( ensureEachSelectedType )
    {
        for ( const auto &table: tableList )
        {
            password += randomCharacterFromTable( table );
        }
    }

    while ( password.size() < pureCharacterLength )
    {
        password += randomCharacterFromTable( allTable );
    }

    shuffleString( password );

    if ( dividingLine )
    {
        return addDividingLine( password, length );
    }
    else
    {
        return password;
    }
}
