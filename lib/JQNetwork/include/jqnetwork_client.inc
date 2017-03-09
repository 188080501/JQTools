/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC
#define JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC

// JQNetwork lib import
#include "jqnetwork_client.h"

inline JQNetworkClientSettingsSharedPointer JQNetworkClient::clientSettings()
{
    return clientSettings_;
}

inline JQNetworkConnectPoolSettingsSharedPointer JQNetworkClient::connectPoolSettings()
{
    return connectPoolSettings_;
}

inline JQNetworkConnectSettingsSharedPointer JQNetworkClient::connectSettings()
{
    return connectSettings_;
}

inline QString JQNetworkClient::nodeMarkSummary() const
{
    return nodeMarkSummary_;
}

inline qint32 JQNetworkClient::sendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendPayloadData(
                hostName,
                port,
                { }, // empty targetActionFlag
                payloadData,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::sendFileData(
        const QString &hostName,
        const quint16 &port,
        const QFileInfo &fileInfo,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendFileData(
                hostName,
                port,
                { }, // empty targetActionFlag
                fileInfo,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC
