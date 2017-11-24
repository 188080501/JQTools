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
#include <QMetaObject>

// JQNetwork lib import
#include <JQNetworkClient>
#include <JQNetworkConnect>
#include <JQNetworkPackage>

using namespace std;
using namespace std::placeholders;

JQNetworkClientForQml::JQNetworkClientForQml()
{
    static bool flag = true;
    if ( flag )
    {
        flag = false;
        qRegisterMetaType< std::function<void()> >( "std::function<void()>" );
        qRegisterMetaType< QVariantMap >( "QVariantMap" );
    }
}

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

void JQNetworkClientForQml::sendVariantMapData(
        const QString &hostName,
        const quint16 &port,
        const QString &targetActionFlag,
        const QVariantMap &payloadData,
        QJSValue succeedCallback,
        QJSValue failCallback
    )
{
    if ( !succeedCallback.isCallable() )
    {
        qDebug() << "JQNetworkClientForQml::sendPayloadData: error, succeedCallback not callable";
        return;
    }

    if ( !failCallback.isCallable() )
    {
        qDebug() << "JQNetworkClientForQml::sendPayloadData: error, failCallback not callable";
        return;
    }

    if ( !jqNetworkClient_ )
    {
        qDebug() << "JQNetworkClientForQml::sendPayloadData: error, client need beginClient";
        return;
    }

    jqNetworkClient_->sendVariantMapData(
                hostName,
                port,
                targetActionFlag,
                payloadData,
                { }, // empty appendData
                [ this, succeedCallback ](const auto &, const auto &package)
                {
                    const auto &&received = QJsonDocument::fromJson( package->payloadData() ).object().toVariantMap();

                    QMetaObject::invokeMethod(
                                this,
                                "onSendSucceed",
                                Qt::QueuedConnection,
                                Q_ARG( QVariant, QVariant::fromValue( succeedCallback ) ),
                                Q_ARG( QVariant, received )
                            );
                },
                [ this, failCallback ](const auto &)
                {
                    QMetaObject::invokeMethod(
                                this,
                                "received",
                                Qt::QueuedConnection,
                                Q_ARG( QVariant, QVariant::fromValue( failCallback ) )
                            );
                }
            );
}
