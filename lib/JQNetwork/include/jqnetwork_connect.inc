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

inline qint32 JQNetworkConnect::sendPayloadData(
        const QByteArray &payloadData,
        const JQNetworkConnectPointerAndPackageSharedPointerFunction &succeedCallback,
        const JQNetworkConnectPointerFunction &failCallback
    )
{
    return this->sendPayloadData(
                payloadData,
                { },
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
                fileInfo,
                { },
                succeedCallback,
                failCallback
            );
}

inline qint32 JQNetworkConnect::replyPayloadData(
        const qint32 &receivedPackageRandomFlag,
        const QByteArray &payloadData
    )
{
    return this->replyPayloadData(
                receivedPackageRandomFlag,
                payloadData,
                { }
            );
}

inline qint32 JQNetworkConnect::replyFile(
        const qint32 &receivedPackageRandomFlag,
        const QFileInfo &fileInfo
    )
{
    return this->replyFile(
                receivedPackageRandomFlag,
                fileInfo,
                { }
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

#endif//JQNETWORK_INCLUDE_JQNETWORK_CONNECT_INC
