/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_ENCRYPT_H
#define JQNETWORK_INCLUDE_JQNETWORK_ENCRYPT_H

// JQNetwork lib import
#include <JQNetworkFoundation>

namespace JQNetworkEncrypt
{

bool encrypt(
        const QByteArray &source,
        QByteArray &target
    );

bool decrypt(
        const QByteArray &source,
        QByteArray &target
    );

}

// inc import
#include "jqnetwork_encrypt.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_ENCRYPT_H
