/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#ifndef JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H
#define JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H

// JQNetwork lib import
#include <JQNetworkFoundation>

class JQNetworkProcessor: public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY( JQNetworkProcessor )

public:
    JQNetworkProcessor() = default;

    ~JQNetworkProcessor() = default;

    QSet< QString > availableSlots();

    bool handlePackage(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package);

    void setReceivedPossibleThreads(const QSet< QThread * > &threads);

protected:
    JQNetworkConnectPointer currentThreadConnect();

private:
    inline static void deleteByteArray(QByteArray *ptr);

    inline static void deleteVariantMap(QVariantMap *ptr);

    static void deleteFileInfo(QFileInfo *ptr);

private:
    static QSet< QString > exceptionSlots_;

    QSet< QString > availableSlots_;
    QMap< QThread *, JQNetworkConnectPointer > connectMapByThread_;

    QMap< QString, std::function<void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)> > onpackageReceivedCallbacks_;
};

// inc import
#include "jqnetwork_processor.inc"

#endif//JQNETWORK_INCLUDE_JQNETWORK_PROCESSOR_H
