/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_INC_

// JQNetwork lib import
#include "jqnetwork_foundation.h"

// JQNetworkThreadPool
inline int JQNetworkThreadPool::nextRotaryIndex()
{
    rotaryIndex_ = ( rotaryIndex_ + 1 ) % helpers_->size();
    return rotaryIndex_;
}

inline void JQNetworkThreadPool::runEach(const std::function<void ()> &callback)
{
    for ( auto index = 0; index < helpers_->size(); ++index )
    {
        ( *helpers_ )[ index ]->run( callback );
    }
}

inline void JQNetworkThreadPool::waitRunEach(const std::function<void ()> &callback)
{
    for ( auto index = 0; index < helpers_->size(); ++index )
    {
        this->waitRun( callback, index );
    }
}

// JQNetworkNodeMark
inline qint64 JQNetworkNodeMark::applicationStartTime() const
{
    return applicationStartTime_;
}

inline QString JQNetworkNodeMark::applicationFilePath() const
{
    return applicationFilePath_;
}

inline QString JQNetworkNodeMark::localHostName() const
{
    return localHostName_;
}

inline qint64 JQNetworkNodeMark::nodeMarkCreatedTime() const
{
    return nodeMarkCreatedTime_;
}

inline QString JQNetworkNodeMark::nodeMarkClassAddress() const
{
    return nodeMarkClassAddress_;
}

inline QString JQNetworkNodeMark::dutyMark() const
{
    return dutyMark_;
}

inline QString JQNetworkNodeMark::nodeMarkSummary() const
{
    return nodeMarkSummary_;
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_FOUNDATION_INC_
