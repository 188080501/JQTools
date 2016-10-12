/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC
#define JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC

// JQNetwork lib import
#include "jqnetwork_connect.h"

inline bool JQNetworkConnect::onceConnectSucceed() const
{
    return onceConnectSucceed_;
}

inline bool JQNetworkConnect::isAbandonTcpSocket() const
{
    return isAbandonTcpSocket_;
}

inline qint64 JQNetworkConnect::connectCreateTime() const
{
    return connectCreateTime_;
}

inline qint64 JQNetworkConnect::connectSucceedTime() const
{
    return connectSucceedTime_;
}

inline qint64 JQNetworkConnect::waitForSendBytes() const
{
    return waitForSendBytes_;
}

inline qint64 JQNetworkConnect::alreadyWrittenBytes() const
{
    return alreadyWrittenBytes_;
}

inline qint64 JQNetworkConnect::connectSucceedElapsed() const
{
    if ( !connectSucceedTime_ ) { return -1; }

    return connectSucceedTime_ - connectCreateTime_;
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC
