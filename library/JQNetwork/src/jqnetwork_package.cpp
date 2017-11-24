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
#include <QFileInfo>
#include <QDateTime>

#define BOOL_CHECK( actual, message )                           \
    if ( !( actual ) )                                          \
    {                                                           \
        qDebug() << "JQNetworkPackage::mixPackage:" << message; \
        this->isAbandonPackage_ = true;                         \
        mixPackage->isAbandonPackage_ = true;                   \
        return false;                                           \
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

    const auto *head = reinterpret_cast< const Head * >( rawData.data() );
    auto dataSize = rawData.size() - JQNetworkPackage::headSize();

    if ( head->bootFlag_ != JQNETWORKPACKAGE_BOOTFLAG ) { return -1; }
    switch ( head->packageFlag_ )
    {
        case JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG:
        case JQNETWORKPACKAGE_PAYLOADDATAREQUESTPACKGEFLAG: { break; }
        case JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG:
        case JQNETWORKPACKAGE_FILEDATAREQUESTPACKGEFLAG: { break; }
        default: { return -1; }
    }
    if ( head->randomFlag_ <= 0 ) { return -1; }

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

    package->head_ = *reinterpret_cast< const Head * >( rawData.data() );

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

    rawData.remove( 0, static_cast< int> ( data - rawData.data() ) );

    package->refreshPackage();

    return package;
}

QList< JQNetworkPackageSharedPointer > JQNetworkPackage::createPayloadTransportPackages(
        const QString &targetActionFlag,
        const QByteArray &payloadData,
        const QVariantMap &appendData,
        const qint32 &randomFlag,
        const qint64 cutPackageSize,
        const bool &compressionData
    )
{
    QList< JQNetworkPackageSharedPointer > result;

    QByteArray metaData;

    if ( !targetActionFlag.isEmpty() || !appendData.isEmpty() )
    {
        QVariantMap metaDataInVariantMap;

        metaDataInVariantMap[ "targetActionFlag" ] = targetActionFlag;
        metaDataInVariantMap[ "appendData" ] = appendData;

        metaData = QJsonDocument( QJsonObject::fromVariantMap( metaDataInVariantMap ) ).toJson( QJsonDocument::Compact );
    }

    if ( payloadData.isEmpty() )
    {
        auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

        package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
        package->head_.packageFlag_ = JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG;
        package->head_.randomFlag_ = randomFlag;

        package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        package->head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

        if ( !metaData.isEmpty() )
        {
            package->head_.metaDataTotalSize_ = metaData.size();
            package->head_.metaDataCurrentSize_ = metaData.size();

            package->metaData_ = metaData;
        }

        package->metaDataOriginalIndex_ = 0;
        package->metaDataOriginalCurrentSize_ = 0;
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
            package->head_.packageFlag_ = JQNETWORKPACKAGE_PAYLOADDATATRANSPORTPACKGEFLAG;
            package->head_.randomFlag_ = randomFlag;

            package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

            if ( !metaData.isEmpty() )
            {
                package->head_.metaDataTotalSize_ = metaData.size();

                if ( !index )
                {
                    package->head_.metaDataCurrentSize_ = metaData.size();
                    package->metaData_ = metaData;
                }
                else
                {
                    package->head_.metaDataCurrentSize_ = 0;
                }
            }

            package->head_.payloadDataFlag_ = ( compressionData ) ? ( JQNETWORKPACKAGE_COMPRESSEDFLAG ) : ( JQNETWORKPACKAGE_UNCOMPRESSEDFLAG );
            package->head_.payloadDataTotalSize_ = payloadData.size();

            if ( cutPackageSize == -1 )
            {
                package->payloadData_ = ( compressionData ) ? ( qCompress( payloadData, 4 ) ) : ( payloadData );
                package->head_.payloadDataCurrentSize_ = package->payloadData_.size();
                package->isCompletePackage_ = true;

                package->metaDataOriginalIndex_ = 0;
                package->metaDataOriginalCurrentSize_ = 0;
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

                    if ( index == 0 )
                    {
                        package->metaDataOriginalIndex_ = 0;
                        package->metaDataOriginalCurrentSize_ = 0;
                    }

                    package->payloadDataOriginalIndex_ = index;
                    package->payloadDataOriginalCurrentSize_ = payloadData.size() - index;

                    index = payloadData.size();
                }
                else
                {
                    package->payloadData_ = ( compressionData ) ? ( qCompress( payloadData.mid( index, static_cast< int >( cutPackageSize ) ), 4 ) ) : ( payloadData.mid( index, static_cast< int >( cutPackageSize ) ) );
                    package->head_.payloadDataCurrentSize_ = package->payloadData_.size();
                    package->isCompletePackage_ = !index && ( ( index + cutPackageSize ) == payloadData.size() );

                    package->payloadDataOriginalIndex_ = index;
                    package->payloadDataOriginalCurrentSize_ = static_cast< int >( cutPackageSize );

                    index += cutPackageSize;
                }
            }

            result.push_back( package );
        }
    }

    return result;
}

JQNetworkPackageSharedPointer JQNetworkPackage::createFileTransportPackage(
        const QString &targetActionFlag,
        const QFileInfo &fileInfo,
        const QByteArray &fileData,
        const QVariantMap &appendData,
        const qint32 &randomFlag,
        const bool &compressionData
    )
{
    JQNetworkPackageSharedPointer package( new JQNetworkPackage );

    QByteArray metaData;

    {
        QVariantMap metaDataInVariantMap;

        metaDataInVariantMap[ "targetActionFlag" ] = targetActionFlag;
        metaDataInVariantMap[ "appendData" ] = appendData;

        if ( fileInfo.isFile() )
        {
            metaDataInVariantMap[ "fileName" ] = fileInfo.fileName();
            metaDataInVariantMap[ "fileSize" ] = fileInfo.size();
            metaDataInVariantMap[ "filePermissions" ] = static_cast< qint32 >( fileInfo.permissions() );
            metaDataInVariantMap[ "fileCreatedTime" ] = fileInfo.created().toMSecsSinceEpoch();
            metaDataInVariantMap[ "fileLastReadTime" ] = fileInfo.lastRead().toMSecsSinceEpoch();
            metaDataInVariantMap[ "fileLastModifiedTime" ] = fileInfo.lastModified().toMSecsSinceEpoch();
        }

        metaData = QJsonDocument( QJsonObject::fromVariantMap( metaDataInVariantMap ) ).toJson( QJsonDocument::Compact );
    }

    package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
    package->head_.packageFlag_ = JQNETWORKPACKAGE_FILEDATATRANSPORTPACKGEFLAG;
    package->head_.randomFlag_ = randomFlag;

    package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;
    package->head_.metaDataTotalSize_ = metaData.size();
    package->head_.metaDataCurrentSize_ = metaData.size();
    package->metaData_ = metaData;

    package->head_.payloadDataFlag_ = ( compressionData ) ? ( JQNETWORKPACKAGE_COMPRESSEDFLAG ) : ( JQNETWORKPACKAGE_UNCOMPRESSEDFLAG );
    package->head_.payloadDataTotalSize_ = fileData.size();
    package->payloadData_ = ( compressionData ) ? ( qCompress( fileData, 4 ) ) : ( fileData );
    package->head_.payloadDataCurrentSize_ = package->payloadData_.size();

    package->metaDataOriginalIndex_ = 0;
    package->metaDataOriginalCurrentSize_ = 0;
    package->payloadDataOriginalIndex_ = 0;
    package->payloadDataOriginalCurrentSize_ = fileData.size();

    return package;
}

JQNetworkPackageSharedPointer JQNetworkPackage::createPayloadDataRequestPackage(const qint32 &randomFlag)
{
    auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

    package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
    package->head_.packageFlag_ = JQNETWORKPACKAGE_PAYLOADDATAREQUESTPACKGEFLAG;
    package->head_.randomFlag_ = randomFlag;

    package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    package->head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    return package;
}

JQNetworkPackageSharedPointer JQNetworkPackage::createFileDataRequestPackage(const qint32 &randomFlag)
{
    auto package = JQNetworkPackageSharedPointer( new JQNetworkPackage );

    package->head_.bootFlag_ = JQNETWORKPACKAGE_BOOTFLAG;
    package->head_.packageFlag_ = JQNETWORKPACKAGE_FILEDATAREQUESTPACKGEFLAG;
    package->head_.randomFlag_ = randomFlag;

    package->head_.metaDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    package->head_.payloadDataFlag_ = JQNETWORKPACKAGE_UNCOMPRESSEDFLAG;

    return package;
}

QDateTime JQNetworkPackage::fileCreatedTime() const
{
    return ( metaDataInVariantMap_.contains( "fileCreatedTime" ) ) ? ( QDateTime::fromMSecsSinceEpoch( metaDataInVariantMap_[ "fileCreatedTime" ].toLongLong() ) ) : ( QDateTime() );
}

QDateTime JQNetworkPackage::fileLastReadTime() const
{
    return ( metaDataInVariantMap_.contains( "fileLastReadTime" ) ) ? ( QDateTime::fromMSecsSinceEpoch( metaDataInVariantMap_[ "fileLastReadTime" ].toLongLong() ) ) : ( QDateTime() );
}

QDateTime JQNetworkPackage::fileLastModifiedTime() const
{
    return ( metaDataInVariantMap_.contains( "fileLastModifiedTime" ) ) ? ( QDateTime::fromMSecsSinceEpoch( metaDataInVariantMap_[ "fileLastModifiedTime" ].toLongLong() ) ) : ( QDateTime() );
}

bool JQNetworkPackage::mixPackage(const JQNetworkPackageSharedPointer &mixPackage)
{
    BOOL_CHECK( !this->isCompletePackage(), "current package is complete" );
    BOOL_CHECK( !mixPackage->isCompletePackage(), "mix package is complete" );
    BOOL_CHECK( !this->isAbandonPackage(), "current package is abandon package" );
    BOOL_CHECK( !mixPackage->isAbandonPackage(), "mix package is abandon package" );
    BOOL_CHECK( this->randomFlag() == mixPackage->randomFlag(), "randomFlag not same" );

    BOOL_CHECK( this->metaDataTotalSize() == mixPackage->metaDataTotalSize(), "metaDataTotalSize not same" );
    BOOL_CHECK( ( this->metaDataCurrentSize() + mixPackage->metaDataCurrentSize() ) <= this->metaDataTotalSize(),
                "metaDataCurrentSize overmuch" );

    BOOL_CHECK( this->payloadDataTotalSize() == mixPackage->payloadDataTotalSize(), "payloadDataTotalSize not same" );
    BOOL_CHECK( ( this->payloadDataCurrentSize() + mixPackage->payloadDataCurrentSize() ) <= this->payloadDataTotalSize(),
                "payloadDataCurrentSize overmuch" );

    BOOL_CHECK( ( ( this->metaDataTotalSize() > 0 ) || ( this->payloadDataTotalSize() > 0 ) ), "data error" );

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

    if ( !metaData_.isEmpty() )
    {
        metaDataInVariantMap_ = QJsonDocument::fromJson( metaData_ ).object().toVariantMap();
    }
}
