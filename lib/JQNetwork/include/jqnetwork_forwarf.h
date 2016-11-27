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

struct JQNetworkForwarfSettings
{
    //...
};

class JQNetworkForwarf: public QObject
{
    Q_OBJECT

public:
    JQNetworkForwarf(
            const JQNetworkForwarfSettingsSharedPointer &forwarfSettings
        );

    ~JQNetworkForwarf() = default;

    JQNetworkForwarf(const JQNetworkForwarf &) = delete;

    JQNetworkForwarf &operator =(const JQNetworkForwarf &) = delete;

    static JQNetworkForwarfSharedPointer createForwarf();

private:
    JQNetworkForwarfSettingsSharedPointer forwarfSettings_;
};

// inc import
#include "jqnetwork_forwarf.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_FORWARF_H
