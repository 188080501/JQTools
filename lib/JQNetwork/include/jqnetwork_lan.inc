/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_LAN_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_LAN_INC_

// JQNetwork lib import
#include "jqnetwork_lan.h"

inline JQNetworkLanSettingsSharedPointer JQNetworkLan::lanSettings()
{
    return lanSettings_;
}

inline QString JQNetworkLan::nodeMarkSummary() const
{
    return nodeMarkSummary_;
}

inline void JQNetworkLan::setAppendData(const QVariant &appendData)
{
    appendData_ = appendData;
}

inline void JQNetworkLan::onLanNodeStateOnline(const JQNetworkLanNode &lanNode)
{
    if ( !lanSettings_->lanNodeOnlineCallback ) { return; }

    lanSettings_->lanNodeOnlineCallback( lanNode );
}

inline void JQNetworkLan::onLanNodeStateActive(const JQNetworkLanNode &lanNode)
{
    if ( !lanSettings_->lanNodeActiveCallback ) { return; }

    lanSettings_->lanNodeActiveCallback( lanNode );
}

inline void JQNetworkLan::onLanNodeStateOffline(const JQNetworkLanNode &lanNode)
{
    if ( !lanSettings_->lanNodeOfflineCallback ) { return; }

    lanSettings_->lanNodeOfflineCallback( lanNode );
}

inline void JQNetworkLan::onLanNodeListChanged()
{
    if ( !lanSettings_->lanNodeListChangedCallback ) { return; }

    lanSettings_->lanNodeListChangedCallback();
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_LAN_INC_
