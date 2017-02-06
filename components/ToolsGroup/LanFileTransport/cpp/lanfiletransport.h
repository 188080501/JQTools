/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
#define __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

// JQNetwork lib import
#include <JQNetworkFoundation>

#define LANFILETRANSPORT_INITIALIZA                                                                 \
{                                                                                                   \
    qmlRegisterType<LanFileTransport::Manage>("LanFileTransport", 1, 0, "LanFileTransportManage");  \
}

namespace LanFileTransport
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

    struct SendCounter
    {
        qint64 alreadySendSizeTotal;
        int alreadySendFileCount;

        qint64 sizeTotal;
        int fileCount;
    };

public:
    Manage();

    ~Manage() = default;

public slots:
    void setShowSelf(const bool &showSelf);

    void sendOnlinePing();

    QVariantList lanNodes();

    QString localHostName() const;

    QString localHostAddress();

    QString localNodeMarkSummary();

    QString transport(const QString &hostAddress, const QVariantList &filePaths);

    QString savePath();

private:
    void refresh();

    void lanNodeOffline(const JQNetworkLanNode &node);

    void emitSendingSignal(const QString &hostName, const SendCounter &counter);

signals:
    void lanNodeChanged();

    void sending(const QString currentHostAddress, const qreal sendPercentage);

    void sendFinish(const QString currentHostAddress);

private:
    QSharedPointer< JQNetworkServer > jqNetworkServer_;
    QSharedPointer< JQNetworkClient > jqNetworkClient_;
    QSharedPointer< JQNetworkLan > jqNetworkLan_;

    QMutex mutex_;
    QString savePath_;
    bool showSelf_ = false;
    QVariantList lanNodes_;

    QMap< JQNetworkConnect *, QString > mapForConnectToHostAddress_;
    QMap< QString, SendCounter > mapForConnectSendCounter_; // hostAddress -> SendCounter
};

}

#endif//__GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
