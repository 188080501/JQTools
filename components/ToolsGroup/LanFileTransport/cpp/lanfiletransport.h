/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
#define __GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__

// Qt lib import
#include <QtCore>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define LANFILETRANSPORT_INITIALIZA                                                                 \
{                                                                                                   \
    qmlRegisterType<LanFileTransport::Manage>("LanFileTransport", 1, 0, "LanFileTransportManage");  \
}

class JQNetworkLan;
class JQNetworkConnect;
class JQNetworkServer;
class JQNetworkClient;

namespace LanFileTransport
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

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
    void refreshLanNodes();

signals:
    void lanNodeChanged();

    void sending(const QString currentHostAddress, const QVariant payloadCurrentIndex, const QVariant payloadTotalSize);

    void sendFinish(const QString currentHostAddress);

private:
    QSharedPointer< JQNetworkServer > jqNetworkServer_;
    QSharedPointer< JQNetworkClient > jqNetworkClient_;
    QSharedPointer< JQNetworkLan > jqNetworkLan_;

    QMutex mutex_;
    bool showSelf_ = false;
    QVariantList lanNodes_;
    QMap< JQNetworkConnect *, QString > mapForConnectToHostAddress_;
};

}

#endif//__GROUP_TOOLSGROUP_LANFILETRANSPORT_CPP_LANFILETRANSPORT_H__
