/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: shijie.chen

    Contact email: xingwozhonghua@126.com

    GitHub: https://github.com/xingwozhonghua126
*/

#include "binarysearchassistant.h"

// Qt lib import
using namespace BinarySearchAssistant;

void Manage::startNewGame(int min, int max)
{
    if ( min > max ) { return; }

    m_min = min;
    m_max = max;
    updateGuess();
}

void Manage::targetIsHigher()
{
    if ( m_guess >= m_max ) { return; }

    m_min = m_guess + 1;
    updateGuess();
}

void Manage::targetIsLower()
{
    if ( m_guess <= m_min ) { return; }

    m_max = m_guess - 1;
    updateGuess();
}

void Manage::updateGuess()
{
    if ( m_min > m_max ) { return; }

    m_guess = m_min + ( m_max - m_min ) / 2;
    emit guessChanged();
}
