/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_INC
#define JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_INC

// JQNetwork lib import
#include "jqnetwork_package.h"

inline int JQNetworkPackage::headSize()
{
    return sizeof( head_ );
}

inline bool JQNetworkPackage::isCompletePackage() const 
{ 
    return isCompletePackage_; 
}

inline bool JQNetworkPackage::isAbandonPackage() const 
{ 
    return isAbandonPackage_;
}

inline qint8 JQNetworkPackage::bootFlag() const 
{ 
    return head_.bootFlag_; 
}

inline qint8 JQNetworkPackage::packageFlag() const 
{ 
    return head_.packageFlag_; 
}

inline qint32 JQNetworkPackage::randomFlag() const 
{ 
    return head_.randomFlag_; 
}

inline qint8 JQNetworkPackage::metaDataFlag() const 
{ 
    return head_.metaDataFlag_;
}

inline qint32 JQNetworkPackage::metaDataTotalSize() const 
{ 
    return head_.metaDataTotalSize_; 
}

inline qint32 JQNetworkPackage::metaDataCurrentSize() const 
{ 
    return head_.metaDataCurrentSize_; 
}

inline qint8 JQNetworkPackage::payloadDataFlag() const 
{ 
    return head_.payloadDataFlag_; 
}

inline qint32 JQNetworkPackage::payloadDataTotalSize() const 
{ 
    return head_.payloadDataTotalSize_; 
}

inline qint32 JQNetworkPackage::payloadDataCurrentSize() const 
{ 
    return head_.payloadDataCurrentSize_; 
}

inline QByteArray JQNetworkPackage::metaData() const 
{ 
    return metaData_; 
}

inline int JQNetworkPackage::metaDataSize() const
{
    return metaData_.size();
}

inline QString JQNetworkPackage::metaDataActionFlag() const
{
    return "actionFlag";
}

inline QByteArray JQNetworkPackage::payloadData() const 
{ 
    return payloadData_; 
}

inline int JQNetworkPackage::payloadDataSize() const
{
    return payloadData_.size();
}

inline qint32 JQNetworkPackage::metaDataOriginalIndex() const
{
    return metaDataOriginalIndex_;
}

inline qint32 JQNetworkPackage::metaDataOriginalCurrentSize() const
{
    return metaDataOriginalCurrentSize_;
}

inline qint32 JQNetworkPackage::payloadDataOriginalIndex() const
{
    return payloadDataOriginalIndex_;
}

inline qint32 JQNetworkPackage::payloadDataOriginalCurrentSize() const
{
    return payloadDataOriginalCurrentSize_;
}

inline QByteArray JQNetworkPackage::toByteArray() const
{
    QByteArray buffer;

    buffer.append( (const char *)&head_, JQNetworkPackage::headSize() );
    if ( head_.metaDataCurrentSize_ > 0 )
    {
        buffer.append( metaData_ );
    }
    if ( head_.payloadDataCurrentSize_ > 0 )
    {
        buffer.append( payloadData_ );
    }

    return buffer;
}

#endif//JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_INC
