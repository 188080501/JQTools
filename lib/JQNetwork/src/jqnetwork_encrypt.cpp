/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_encrypt.h"

// Qt lib import
#include <QDebug>

bool JQNetworkEncrypt::encrypt(
        const QByteArray &source,
        QByteArray &target
    )
{
    if ( source.isEmpty() )
    {
        target.clear();
        return true;
    }

    //...

    return true;
}

bool JQNetworkEncrypt::decrypt(
        const QByteArray &source,
        QByteArray &target
    )
{
    if ( source.isEmpty() )
    {
        target.clear();
        return true;
    }

    //...

    return true;
}
