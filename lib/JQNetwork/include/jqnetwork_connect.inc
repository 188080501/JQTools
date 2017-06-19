/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC_
#define JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC_

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

inline qint32 JQNetworkConnect::sendPayloadData(
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendPayloadData(
                { }, // empty targetActionFlag
                payloadData,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkConnect::sendVariantMapData(
        const QVariantMap &variantMap,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendVariantMapData(
                { }, // empty targetActionFlag
                variantMap,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkConnect::sendFileData(
        const QFileInfo &fileInfo,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendFileData(
                { }, // empty targetActionFlag
                fileInfo,
                { }, // empty appendData
                succeedCallback,
                failCallback
            );
}

inline bool JQNetworkConnect::putPayloadData(
        const QByteArray &payloadData,
        const QVariantMap &appendData
    )
{
    return this->putPayloadData(
                { }, // empty targetActionFlag,
                payloadData,
                appendData
            );
}

inline bool JQNetworkConnect::putVariantMapData(
        const QVariantMap &variantMap,
        const QVariantMap &appendData
    )
{
    return this->putVariantMapData(
                { }, // empty targetActionFlag,
                variantMap,
                appendData
            );
}

inline bool JQNetworkConnect::putFile(
        const QFileInfo &fileInfo,
        const QVariantMap &appendData
    )
{
    return this->putFile(
                { }, // empty targetActionFlag,
                fileInfo,
                appendData
            );
}

inline bool JQNetworkConnect::needCompressionPayloadData(const int &dataSize)
{
    bool compressionPayloadData = false;

    if ( connectSettings_->packageCompressionThresholdForConnectSucceedElapsed != -1)
    {
        if ( this->connectSucceedElapsed() >= connectSettings_->packageCompressionThresholdForConnectSucceedElapsed )
        {
            compressionPayloadData = true;
        }

        if ( ( connectSettings_->packageCompressionMinimumBytes != -1 ) &&
             ( dataSize < connectSettings_->packageCompressionMinimumBytes ) )
        {
            compressionPayloadData = false;
        }
    }

    return compressionPayloadData;
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC_
