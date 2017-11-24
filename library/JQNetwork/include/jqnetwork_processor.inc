/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_INC_

// JQNetwork lib import
#include "jqnetwork_processor.h"

inline void JQNetworkProcessor::deleteByteArray(QByteArray *ptr)
{
    delete ptr;
}

inline void JQNetworkProcessor::deleteVariantMap(QVariantMap *ptr)
{
    delete ptr;
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_INC_
