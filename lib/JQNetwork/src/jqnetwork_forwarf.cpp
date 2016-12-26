/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_forwarf.h"

// Qt lib import
#include <QDebug>

JQNetworkForwarf::JQNetworkForwarf(
        const JQNetworkForwarfSettingsSharedPointer &forwarfSettings
    ):
    forwarfSettings_( forwarfSettings )
{ }

JQNetworkForwarfSharedPointer JQNetworkForwarf::createForwarf(
        const bool & /*fileTransferEnabled*/
    )
{
    JQNetworkForwarfSettingsSharedPointer forwarfSettings( new JQNetworkForwarfSettings );

    return JQNetworkForwarfSharedPointer( new JQNetworkForwarf( forwarfSettings ) );
}
