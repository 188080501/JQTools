/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_H
#define JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_H

// Qt lib import
#include <QVariant>

// JQNetwork lib import
#include <JQNetworkFoundation>

class QFileInfo;
class QDateTime;

class JQNetworkPackage
{
private:
    JQNetworkPackage() = default;

public:
    ~JQNetworkPackage() = default;

    JQNetworkPackage(const JQNetworkPackage &) = delete;

    JQNetworkPackage &operator =(const JQNetworkPackage &) = delete;

public:
    static inline int headSize();

    static qint32 checkDataIsReadyReceive(const QByteArray &rawData);

    static JQNetworkPackageSharedPointer readPackage(QByteArray &rawData);

    static QList< JQNetworkPackageSharedPointer > createPayloadTransportPackages(
            const QString &targetNodeFlag,
            const QString &targerActionFlag,
            const QVariantMap &appendData,
            const QByteArray &payloadData,
            const qint32 &randomFlag,
            const qint64 cutPackageSize = -1,
            const bool &compressionData = false
        );

    inline static QList< JQNetworkPackageSharedPointer > createPayloadTransportPackages(
            const QVariantMap &appendData,
            const QByteArray &payloadData,
            const qint32 &randomFlag,
            const qint64 cutPackageSize = -1,
            const bool &compressionData = false
        );

    inline static QList< JQNetworkPackageSharedPointer > createPayloadTransportPackages(
            const QByteArray &payloadData,
            const qint32 &randomFlag,
            const qint64 cutPackageSize = -1,
            const bool &compressionData = false
        );

    static JQNetworkPackageSharedPointer createFileTransportPackage(
            const QString &targetNodeFlag,
            const QString &targerActionFlag,
            const QVariantMap &appendData,
            const QFileInfo &fileInfo,
            const QByteArray &fileData,
            const qint32 &randomFlag,
            const bool &compressionData = false
        );

    inline static JQNetworkPackageSharedPointer createFileTransportPackage(
            const QVariantMap &appendData,
            const QFileInfo &fileInfo,
            const QByteArray &fileData,
            const qint32 &randomFlag,
            const bool &compressionData = false
        );

    inline static JQNetworkPackageSharedPointer createFileTransportPackage(
            const QFileInfo &fileInfo,
            const QByteArray &fileData,
            const qint32 &randomFlag,
            const bool &compressionData = false
        );

    static JQNetworkPackageSharedPointer createPayloadDataRequestPackage(const qint32 &randomFlag);

    static JQNetworkPackageSharedPointer createFileDataRequestPackage(const qint32 &randomFlag);

    inline bool isCompletePackage() const;

    inline bool isAbandonPackage() const;


    inline qint8 bootFlag() const;

    inline qint8 packageFlag() const;

    inline qint32 randomFlag() const;

    inline qint8 metaDataFlag() const;

    inline qint32 metaDataTotalSize() const;

    inline qint32 metaDataCurrentSize() const;

    inline qint8 payloadDataFlag() const;

    inline qint32 payloadDataTotalSize() const;

    inline qint32 payloadDataCurrentSize() const;

    inline QByteArray metaData() const;

    inline int metaDataSize() const;

    inline QString metaDataActionFlag() const;

    inline QByteArray payloadData() const;

    inline int payloadDataSize() const;

    inline qint32 metaDataOriginalIndex() const;

    inline qint32 metaDataOriginalCurrentSize() const;

    inline qint32 payloadDataOriginalIndex() const;

    inline qint32 payloadDataOriginalCurrentSize() const;


    inline QVariantMap metaDataInVariantMap() const;

    inline QString targetNodeFlag() const;

    inline QString targerActionFlag() const;

    inline QVariantMap appendData() const;

    inline QString fileName() const;

    inline qint64 fileSize() const;

    inline qint32 filePermissions() const;

    QDateTime fileCreatedTime() const;

    QDateTime fileLastReadTime() const;

    QDateTime fileLastModifiedTime() const;

    inline bool containsFile() const;

    inline QString localFilePath() const;

    inline void setLocalFilePath(const QString &localFilePath);

    inline void clearMetaData();

    inline void clearPayloadData();


    inline QByteArray toByteArray() const;

    bool mixPackage(const JQNetworkPackageSharedPointer &mixPackage);

    void refreshPackage();

private:
    bool isCompletePackage_ = false;
    bool isAbandonPackage_ = false;

#pragma pack(push)
#pragma pack(1)
    struct Head
    {
        qint8 bootFlag_ = 0;
        qint8 packageFlag_ = 0;
        qint32 randomFlag_ = 0;

        qint8 metaDataFlag_ = 0;
        qint32 metaDataTotalSize_ = -1;
        qint32 metaDataCurrentSize_ = -1;

        qint8 payloadDataFlag_ = 0;
        qint32 payloadDataTotalSize_ = -1;
        qint32 payloadDataCurrentSize_ = -1;
    } head_;
#pragma pack(pop)

    QByteArray metaData_;
    QByteArray payloadData_;

    QString localFilePath_;

    qint32 metaDataOriginalIndex_ = -1;
    qint32 metaDataOriginalCurrentSize_ = -1;
    qint32 payloadDataOriginalIndex_ = -1;
    qint32 payloadDataOriginalCurrentSize_ = -1;

    QVariantMap metaDataInVariantMap_;
};

// inc import
#include "jqnetwork_package.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_PACKAGE_H
