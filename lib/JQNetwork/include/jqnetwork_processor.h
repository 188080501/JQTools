/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H_
#define JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H_

// JQNetwork lib import
#include <JQNetworkFoundation>

#define JQNP_SUCCEED()                                                                  \
    send[ "succeed" ] = true;                                                           \
    send[ "message" ] = "";                                                             \
    return true;

#define JQNP_FAIL( errorMessage )                                                       \
    send[ "succeed" ] = false;                                                          \
    send[ "message" ] = errorMessage;                                                   \
    return false;

#define JQNP_SERVERFAIL( errorMessage )                                                 \
    const auto &&message = QString( "Server error: " ) + errorMessage;                  \
    qDebug() << message.toLocal8Bit().data();                                           \
    send[ "succeed" ] = false;                                                          \
    send[ "message" ] = errorMessage;                                                   \
    return false;

#define JQNP_CHECKRECEIVEDDATACONTAINS( ... )                                           \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContains(                                          \
            { __VA_ARGS__ },                                                            \
            received,                                                                   \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDDATACONTAINSANDNOT0( ... )                                    \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContainsAndNot0(                                   \
            { __VA_ARGS__ },                                                            \
            received,                                                                   \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDDATACONTAINSANDNOTEMPTY( ... )                                \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContainsAndNotEmpty(                               \
            { __VA_ARGS__ },                                                            \
            received,                                                                   \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDDATACONTAINSEXPECTEDCONTENT( key, ... )                       \
    if (                                                                                \
        !JQNetworkProcessor::checkDataContasinsExpectedContent(                         \
            key,                                                                        \
            __VA_ARGS__,                                                                \
            received,                                                                   \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDAPPENDDATACONTAINS( ... )                                     \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContains(                                          \
            { __VA_ARGS__ },                                                            \
            receivedAppend,                                                             \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDAPPENDDATACONTAINSANDNOT0( ... )                              \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContainsAndNot0(                                   \
            { __VA_ARGS__ },                                                            \
            receivedAppend,                                                             \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDAPPENDDATACONTAINSANDNOTEMPTY( ... )                          \
    if (                                                                                \
        !JQNetworkProcessor::checkMapContainsAndNotEmpty(                               \
            { __VA_ARGS__ },                                                            \
            receivedAppend,                                                             \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

#define JQNP_CHECKRECEIVEDAPPENDDATACONTAINSEXPECTEDCONTENT( key, ... )                 \
    if (                                                                                \
        !JQNetworkProcessor::checkDataContasinsExpectedContent(                         \
            key,                                                                        \
            __VA_ARGS__,                                                                \
            receivedAppend,                                                             \
            send                                                                        \
        )                                                                               \
    )                                                                                   \
    { return false; }

class JQNetworkProcessor: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkProcessor )

public:
    JQNetworkProcessor(const bool &invokeMethodByProcessorThread = false);

    ~JQNetworkProcessor() = default;

    QSet< QString > availableSlots();

    bool handlePackage(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package);

    void setReceivedPossibleThreads(const QSet< QThread * > &threads);

    static bool checkMapContains(const QStringList &keys, const QVariantMap &received, QVariantMap &send);

    static bool checkMapContainsAndNot0(const QStringList &keys, const QVariantMap &received, QVariantMap &send);

    static bool checkMapContainsAndNotEmpty(const QStringList &keys, const QVariantMap &received, QVariantMap &send);

    static bool checkDataContasinsExpectedContent(const QString &key, const QVariantList &expectedContentList, const QVariantMap &received, QVariantMap &send);

protected:
    JQNetworkConnectPointer currentThreadConnect();

private:
    inline static void deleteByteArray(QByteArray *ptr);

    inline static void deleteVariantMap(QVariantMap *ptr);

    static void deleteFileInfo(QFileInfo *ptr);

private:
    static QSet< QString > exceptionSlots_;

    bool invokeMethodByProcessorThread_;

    QSet< QString > availableSlots_;
    QMap< QThread *, JQNetworkConnectPointer > connectMapByThread_;

    QMap< QString, std::function<void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)> > onpackageReceivedCallbacks_;
};

// inc import
#include "jqnetwork_processor.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H_
