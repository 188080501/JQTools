/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_package.h"

// Qt lib import
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

#define BOOL_CHECK( actual, message )           \
    if ( !( actual ) )                          \
    {                                           \
        qDebug() << __func__ << message;        \
        this->isAbandonPackage_ = true;         \
        mixPackage->isAbandonPackage_ = true;   \
        return false;                           \
    }

qint32 JQNetworkPackage::checkDataIsReadyReceive(const QByteArray &rawData)
{
    /*
     * Return value:
     * > 0: Wait for more byte
     * < 0: Error data, need to abandon
     * = 0: Data is ready for receive
     */

    if ( rawData.size() < JQNetworkPackage::headSize() ) { return JQNetworkPackage::headSize() - rawData.size(); }

    auto head = ( Head * )rawData.data();
    auto dataSize = rawData.size() - JQNetworkPackage::headSize();

    if ( head->bootFlag_ != JQNETWORKPACKAGE_BOOTFLAG ) { return -1; }
    switch ( head->packageFlag_ )
    {
        case JQNETWORKPACKAGE_DATATRANSPORTPACKGEFLAG:
        case JQNETWORKPACKAGE_DATAREQUESTPACKGEFLAG: { break; }
        default: { return -1; }
    }
    if ( head->randomFlag_ == 0 ) { return -1; }

    switch ( head->metaDataFlag_ )
    {
        case JQNETWORKPACKAGE_UNCOMPRESSEDFLAG:
        case JQNETWORKPACKAGE_COMPRESSEDFLAG: { break; }
        default: { return -1; }
    }
    if ( head->metaDataTotalSize_ < -1 ) { return -1; }
    if ( head->metaDataCurrentSize_ < -1 ) { return -1; }
    if ( head->metaDataTotalSize_ < head->metaDataCurrentSize_ ) { return -1; }

    switch ( head->payloadDataFlag_ )
    {
        case JQNETWORKPACKAGE_UNCOMPRESSEDFLAG:
        case JQNETWORKPACKAGE_COMPRESSEDFLAG: { break; }
        default: { return -1; }
    }
    if ( head->payloadDataTotalSize_ < -1 ) { return -1; }
    if ( head->payloadDataCurrentSize_ < -1 ) { return -1; }
    if ( head->payloadDataTotalSize_ < head->payloadDataCurrentSize_ ) { return -1; }

    auto expectDataSize = 0;
    if ( head->metaDataCurrentSize_ > 0 )
    {
        expectDataSize += head->metaDataCurrentSize_;
    }
    if ( head->payloadDataCurrentSize_ > 0 )
    {
        expectDataSize += head->payloadDataCurrentSize_;
    }

    if ( dataSize < expectDataSize ) { return expectDataSize - dataSize; }

    return 0;
}

JQNetworkPackageSharedPointer JQNetworkPackage::readPackage(QByteArray &rawData)
{
    auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );
    auto data = rawData.data() + JQNetworkPackage::headSize();

    package->head_ = *( Head * )rawData.data();

    if ( package->metaDataCurrentSize() > 0 )
    {
        package->metaData_.append( data, package->metaDataCurrentSize() );
        data += package->metaDataCurrentSize();
    }
    if ( package->payloadDataCurrentSize() > 0 )
    {
        package->payloadData_.append( data, package->payloadDataCurrentSize() );
        data += package->payloadDataCurrentSize();
    }

    rawData.remove( 0, data - rawData.data() );

    package->refreshPackage();

    return package;
}

QList< JQNetworkPackageSharedPointer > JQNetworkPackage::createTransportPackages(
        const QByteArray &payloadData,
        const qint32 &randomFlag,
        const qint64 cutPackageSize,
        const bool &compressionData
    )
{
    return JQNetworkPackage::createTransportPackages(
                "",
                "",
                { },
                payloadData,
                randomFlag,
                cutPackageSize,
                compressionData
            );
}

QList< JQNetworkPackageSharedPointer > JQNetworkPackage::createTransportPackages(
        const QString &targetNodeFlag,
        const QString &targerActionFlag,
        const QJsonObject &appendData,
        const QByteArray &payloadData,
        const qint32 &randomFlag,
        const qint64 cutPackageSize,
        const bool &compressionData
    )
{
    QList< JQNetworkPackageSharedPointer > result;
    QJsonObject metaData;

    if ( payloadData.isEmpty() )
    {
        auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

        package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
        package->head_.packageFlag_ = JQNETWORKPACKAGE_DATATRANSPORTPACKGEFLAG;
        package->head_.randomFlag_ = randomFlag;

        package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        package->head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        package->payloadDataOriginalIndex_ = 0;
        package->payloadDataOriginalCurrentSize_ = 0;

        package->isCompletePackage_ = true;

        result.push_back( package );
    }
    else
    {
        for ( auto index = 0; index < payloadData.size(); )
        {
            auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

            package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
            package->head_.packageFlag_ = JQNETWORKPACKAGE_DATATRANSPORTPACKGEFLAG;
            package->head_.randomFlag_ = randomFlag;

            package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

            package->head_.payloadDataFlag_ = ( compressionData ) ? ( JQNETWORKPACKAGE_COMPRESSEDFLAG ) : ( JQNETWORKPACKAGE_UNCOMPRESSEDFLAG );
            package->head_.payloadDataTotalSize_ = payloadData.size();

            if ( cutPackageSize == -1 )
            {
                package->payloadData_ = ( compressionData ) ? ( qCompress( payloadData, 4 ) ) : ( payloadData );
                package->head_.payloadDataCurrentSize_ = package->payloadData_.size();
                package->isCompletePackage_ = true;

                package->payloadDataOriginalIndex_ = index;
                package->payloadDataOriginalCurrentSize_ = payloadData.size();

                index = payloadData.size();
            }
            else
            {
                if ( ( index + cutPackageSize ) > payloadData.size() )
                {
                    package->payloadData_ = ( compressionData ) ? ( qCompress( payloadData.mid( index ), 4 ) ) : ( payloadData.mid( index ) );
                    package->head_.payloadDataCurrentSize_ = package->payloadData_.size();
                    package->isCompletePackage_ = result.isEmpty();

                    package->payloadDataOriginalIndex_ = index;
                    package->payloadDataOriginalCurrentSize_ = payloadData.size() - index;

                    index = payloadData.size();
                }
                else
                {
                    package->payloadData_ = ( compressionData ) ? ( qCompress( payloadData.mid( index, cutPackageSize ), 4 ) ) : ( payloadData.mid( index, cutPackageSize ) );
                    package->head_.payloadDataCurrentSize_ = package->payloadData_.size();
                    package->isCompletePackage_ = !index && ( ( index + cutPackageSize ) == payloadData.size() );

                    package->payloadDataOriginalIndex_ = index;
                    package->payloadDataOriginalCurrentSize_ = cutPackageSize;

                    index += cutPackageSize;
                }
            }

            result.push_back( package );
        }
    }

    return result;
}

JQNetworkPackageSharedPointer JQNetworkPackage::createDataRequestPackage(const qint32 &randomFlag)
{
    auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

    package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
    package->head_.packageFlag_ = JQNETWORKPACKAGE_DATAREQUESTPACKGEFLAG;
    package->head_.randomFlag_ = randomFlag;

    package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    package->head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    return package;
}

bool JQNetworkPackage::mixPackage(const JQNetworkPackageSharedPointer &mixPackage)
{
    BOOL_CHECK( !this->isCompletePackage(), ": current package is complete" );
    BOOL_CHECK( !mixPackage->isCompletePackage(), ": mix package is complete" );
    BOOL_CHECK( !this->isAbandonPackage(), ": current package is abandon package" );
    BOOL_CHECK( !mixPackage->isAbandonPackage(), ": mix package is abandon package" );
    BOOL_CHECK( this->randomFlag() == mixPackage->randomFlag(), ": randomFlag not same" );

    BOOL_CHECK( this->metaDataTotalSize() == mixPackage->metaDataTotalSize(), ": metaDataTotalSize not same" );
    BOOL_CHECK( ( this->metaDataCurrentSize() + mixPackage->metaDataCurrentSize() ) <= this->metaDataTotalSize(),
                ": metaDataCurrentSize overmuch" );

    BOOL_CHECK( this->payloadDataTotalSize() == mixPackage->payloadDataTotalSize(), ": payloadDataTotalSize not same" );
    BOOL_CHECK( ( this->payloadDataCurrentSize() + mixPackage->payloadDataCurrentSize() ) <= this->payloadDataTotalSize(),
                ": payloadDataCurrentSize overmuch" );

    BOOL_CHECK( ( ( this->metaDataTotalSize() > 0 ) || ( this->payloadDataTotalSize() > 0 ) ), ": data error" );

    if ( this->metaDataTotalSize() > 0 )
    {
        this->metaData_.append( mixPackage->metaData() );
        this->head_.metaDataCurrentSize_ += mixPackage->metaDataCurrentSize();
    }
    if ( this->payloadDataTotalSize() > 0 )
    {
        this->payloadData_.append( mixPackage->payloadData() );
        this->head_.payloadDataCurrentSize_ += mixPackage->payloadDataCurrentSize();
    }

    this->refreshPackage();

    return true;
}

void JQNetworkPackage::refreshPackage()
{
    if ( head_.metaDataFlag_ == JQNETWORKPACKAGE_COMPRESSEDFLAG )
    {
        head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        metaData_ = qUncompress( metaData_ );
        head_.metaDataCurrentSize_ = metaData_.size();
    }

    if ( head_.payloadDataFlag_ == JQNETWORKPACKAGE_COMPRESSEDFLAG )
    {
        head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        payloadData_ = qUncompress( payloadData_ );
        head_.payloadDataCurrentSize_ = payloadData_.size();
    }

    if ( this->metaDataTotalSize() != this->metaDataCurrentSize() ) { return; }
    if ( this->payloadDataTotalSize() != this->payloadDataCurrentSize() ) { return; }

    this->isCompletePackage_ = true;
}
