/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_clientforqml.h"

// Qt lib import
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

// JQNetwork lib import
#include <JQNetworkClient>
#include <JQNetworkConnect>
#include <JQNetworkPackage>

using namespace std;
using namespace std::placeholders;

bool JQNetworkClientForQml::beginClient()
{
    jqNetworkClient_ = JQNetworkClient::createClient();

    jqNetworkClient_->clientSettings()->connectToHostErrorCallback = std::bind( &JQNetworkClientForQml::connectToHostError, this, _2, _3 );
    jqNetworkClient_->clientSettings()->connectToHostTimeoutCallback = std::bind( &JQNetworkClientForQml::connectToHostTimeout, this, _2, _3 );
    jqNetworkClient_->clientSettings()->connectToHostSucceedCallback = std::bind( &JQNetworkClientForQml::connectToHostSucceed, this, _2, _3 );
    jqNetworkClient_->clientSettings()->remoteHostClosedCallback = std::bind( &JQNetworkClientForQml::remoteHostClosed, this, _2, _3 );
    jqNetworkClient_->clientSettings()->readyToDeleteCallback = std::bind( &JQNetworkClientForQml::readyToDelete, this, _2, _3 );

    return jqNetworkClient_->begin();
}

void JQNetworkClientForQml::createConnect(const QString &hostName, const quint16 &port)
{
    jqNetworkClient_->createConnect( hostName, port );
}

void JQNetworkClientForQml::sendPayloadData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &payloadData,
        QJSValue succeedCallback,
        QJSValue failCallback
    )
{
    if ( !jqNetworkClient_ )
    {
        qDebug() << "JQNetworkClientForQml::sendPayloadData: error, client need beginClient";
        return;
    }

    qDebug() << "JQNetworkClientForQml::sendPayloadData:" << hostName << port << targetActionFlag;

    jqNetworkClient_->sendPayloadData(
                hostName,
                port,
                targetActionFlag,
                QJsonDocument( QJsonObject::fromVariantMap( payloadData ) ).toJson( QJsonDocument::Compact ),
                { }, // emptyvappendData
                [ succeedCallback ](const auto &, const auto &){ },
                [ failCallback ](const auto &){ }
            );
}
