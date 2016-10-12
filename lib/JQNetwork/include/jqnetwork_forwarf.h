/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_FORWARF_H
#define JQNETWORK_INCLUDE_JQNETWORK_FORWARF_H

// JQNetwork lib import
#include <JQNetworkFoundation>

class JQNetworkForwarf: public QObject
{
    Q_OBJECT

public:
    JQNetworkForwarf() = default;

    ~JQNetworkForwarf() = default;

    JQNetworkForwarf(const JQNetworkForwarf &) = delete;

    JQNetworkForwarf &operator =(const JQNetworkForwarf &) = delete;
};

#include "jqnetwork_forwarf.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_FORWARF_H
