/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC_

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

inline QSet< QString > JQNetworkClient::availableProcessorMethodNames() const
{
    return QSet< QString >::fromList( processorCallbacks_.keys() );
}

inline qint32 JQNetworkClient::sendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendPayloadData(
                hostName,
                port,
                targetActionFlag,
                payloadData,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
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

inline qint32 JQNetworkClient::sendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendVariantMapData(
                hostName,
                port,
                targetActionFlag,
                variantMap,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::sendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QVariantMap &variantMap,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendVariantMapData(
                hostName,
                port,
                { }, // empty targetActionFlag
                variantMap,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::sendFileData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendFileData(
                hostName,
                port,
                targetActionFlag,
                fileInfo,
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

inline qint32 JQNetworkClient::waitForSendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendPayloadData(
                hostName,
                port,
                targetActionFlag,
                payloadData,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::waitForSendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendPayloadData(
                hostName,
                port,
                { }, // empty targetActionFlag
                payloadData,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::waitForSendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &variantMap,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendVariantMapData(
                hostName,
                port,
                targetActionFlag,
                variantMap,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::waitForSendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QVariantMap &variantMap,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendVariantMapData(
                hostName,
                port,
                { }, // empty targetActionFlag
                variantMap,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::waitForSendFileData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendFileData(
                hostName,
                port,
                targetActionFlag,
                fileInfo,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkClient::waitForSendFileData(
        const QString &hostName,
        const quint16 &port,
        const QFileInfo &fileInfo,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->waitForSendFileData(
                hostName,
                port,
                { }, // empty targetActionFlag
                fileInfo,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_CLIENG_INC_
