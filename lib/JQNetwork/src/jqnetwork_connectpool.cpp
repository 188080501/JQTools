/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_connectpool.h"

// Qt lib import
#include <QDebug>
#include <QTimer>

// JQNetwork lib import
#include <JQNetworkConnect>

using namespace std;
using namespace std::placeholders;

JQNetworkConnectPool::JQNetworkConnectPool(
        JQNetworkConnectPoolSettingsSharedPointer connectPoolSettings,
        JQNetworkConnectSettingsSharedPointer connectSettings
    ):
    connectPoolSettings_( connectPoolSettings ),
    connectSettings_( connectSettings )
{
    connectSettings_->connectToHostErrorCallback        = bind( &JQNetworkConnectPool::onConnectToHostError, this, _1 );
    connectSettings_->connectToHostTimeoutCallback      = bind( &JQNetworkConnectPool::onConnectToHostTimeout, this, _1 );
    connectSettings_->connectToHostSucceedCallback      = bind( &JQNetworkConnectPool::onConnectToHostSucceed, this, _1 );
    connectSettings_->remoteHostClosedCallback          = bind( &JQNetworkConnectPool::onRemoteHostClosed, this, _1 );
    connectSettings_->readyToDeleteCallback             = bind( &JQNetworkConnectPool::onReadyToDelete, this, _1 );
    connectSettings_->packageSendingCallback            = bind( &JQNetworkConnectPool::onPackageSending, this, _1, _2, _3, _4, _5 );
    connectSettings_->packageReceivingCallback          = bind( &JQNetworkConnectPool::onPackageReceiving, this, _1, _2, _3, _4, _5 );
    connectSettings_->packageReceivedCallback           = bind( &JQNetworkConnectPool::onPackageReceived, this, _1, _2 );
    connectSettings_->waitReplyPackageSucceedCallback   = bind( &JQNetworkConnectPool::onWaitReplyPackageSucceed, this, _1, _2, _3 );
    connectSettings_->waitReplyPackageFailCallback      = bind( &JQNetworkConnectPool::onWaitReplyPackageFail, this, _1, _2 );
}

JQNetworkConnectPool::~JQNetworkConnectPool()
{
    QVector< JQNetworkConnectSharedPointer > waitForCloseConnects;

    for ( const auto &connect: connectForConnecting_ )
    {
        waitForCloseConnects.push_back( connect );
    }

    for ( const auto &connect: connectForConnected_ )
    {
        waitForCloseConnects.push_back( connect );
    }

    for ( const auto &connect: waitForCloseConnects )
    {
        connect->close();
    }
}

void JQNetworkConnectPool::createConnect(
        const std::function< void( std::function< void() > ) > runOnConnectThreadCallback,
        const QString &hostName,
        const quint16 &port
    )
{
    auto connectKey = QString( "%1:%2" ).arg( hostName ).arg( port );

    mutex_.lock();

    if ( bimapForHostAndPort1.contains( connectKey ) )
    {
        mutex_.unlock();

        return;
    }

    mutex_.unlock();

    JQNetworkConnect::createConnect(
                [
                    this,
                    connectKey,
                    hostName,
                    port
                ](const auto &connect)
                {
                    this->mutex_.lock();

                    this->connectForConnecting_[ connect.data() ] = connect;
                    this->bimapForHostAndPort1[ connectKey ] = connect.data();
                    this->bimapForHostAndPort2[ connect.data() ] = connectKey;

                    this->mutex_.unlock();
                },
                runOnConnectThreadCallback,
                connectSettings_,
                hostName,
                port
            );
}

void JQNetworkConnectPool::createConnect(
        const std::function< void( std::function< void() > ) > runOnConnectThreadCallback,
        const qintptr &socketDescriptor
    )
{
    mutex_.lock();

    if ( bimapForSocketDescriptor1.contains( socketDescriptor ) )
    {
        mutex_.unlock();

        return;
    }

    mutex_.unlock();

    JQNetworkConnect::createConnect(
                [
                    this,
                    socketDescriptor
                ](const auto &connect)
                {
                    this->mutex_.lock();

                    this->connectForConnecting_[ connect.data() ] = connect;
                    this->bimapForSocketDescriptor1[ socketDescriptor ] = connect.data();
                    this->bimapForSocketDescriptor2[ connect.data() ] = socketDescriptor;

                    this->mutex_.unlock();
                },
                runOnConnectThreadCallback,
                connectSettings_,
                socketDescriptor
            );
}

QPair< QString, quint16 > JQNetworkConnectPool::getHostAndPortByConnect(const JQNetworkConnectPointer &connect)
{
    QPair< QString, quint16 > reply;

    mutex_.lock();

    {
        auto it = bimapForHostAndPort2.find( connect.data() );
        if ( it != bimapForHostAndPort2.end() )
        {
            auto index = it.value().lastIndexOf( ":" );

            if ( ( index > 0 ) && ( ( index + 1 ) < it.value().size() ) )
            {
                reply.first = it.value().mid( 0, index );
                reply.second = it.value().mid( index + 1 ).toUShort();
            }
        }
    }

    mutex_.unlock();

    return reply;
}

qintptr JQNetworkConnectPool::getSocketDescriptorByConnect(const JQNetworkConnectPointer &connect)
{
    qintptr reply = { };

    mutex_.lock();

    {
        auto it = bimapForSocketDescriptor2.find( connect.data() );
        if ( it != bimapForSocketDescriptor2.end() )
        {
            reply = it.value();
        }
    }

    mutex_.unlock();

    return reply;
}

JQNetworkConnectPointer JQNetworkConnectPool::getConnectByHostAndPort(const QString &hostName, const quint16 &port)
{
    JQNetworkConnectPointer reply;

    mutex_.lock();

    {
        auto it = bimapForHostAndPort1.find( QString( "%1:%2" ).arg( hostName, QString::number( port ) ) );
        if ( it != bimapForHostAndPort1.end() )
        {
            reply = it.value();
        }
    }

    mutex_.unlock();

    return reply;
}

JQNetworkConnectPointer JQNetworkConnectPool::getConnectBySocketDescriptor(const qintptr &socketDescriptor)
{
    JQNetworkConnectPointer reply;

    mutex_.lock();

    {
        auto it = bimapForSocketDescriptor1.find( socketDescriptor );
        if ( it != bimapForSocketDescriptor1.end() )
        {
            reply = it.value();
        }
    }

    mutex_.unlock();

    return reply;
}

void JQNetworkConnectPool::onConnectToHostSucceed(const JQNetworkConnectPointer &connect)
{
//    qDebug() << "JQNetworkConnectPool::onConnectToHostSucceed:" << connect.data();

    mutex_.lock();

    auto containsInConnecting = connectForConnecting_.contains( connect.data() );

    if ( !containsInConnecting )
    {
        mutex_.unlock();

        qDebug() << "JQNetworkConnectPool::onConnectToHostSucceed: error: connect not contains" << connect.data();
        return;
    }

    connectForConnected_[ connect.data() ] = connectForConnecting_[ connect.data() ];
    connectForConnecting_.remove( connect.data() );

    mutex_.unlock();

    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->connectToHostSucceedCallback );
    connectPoolSettings_->connectToHostSucceedCallback( connect, this );
}

void JQNetworkConnectPool::onReadyToDelete(const JQNetworkConnectPointer &connect)
{
//    qDebug() << "JQNetworkConnectPool::onReadyToDelete:" << connect.data();

    JQNETWORK_NULLPTR_CHECK( connectPoolSettings_->readyToDeleteCallback );
    connectPoolSettings_->readyToDeleteCallback( connect, this );

    mutex_.lock();

    auto containsInConnecting = connectForConnecting_.contains( connect.data() );
    auto containsInConnected = connectForConnected_.contains( connect.data() );
    auto containsInBimapForHostAndPort = bimapForHostAndPort2.contains( connect.data() );
    auto containsInBimapForSocketDescriptor = bimapForSocketDescriptor2.contains( connect.data() );

    if ( ( !containsInConnecting && !containsInConnected ) || ( !containsInBimapForHostAndPort && !containsInBimapForSocketDescriptor ) )
    {
        mutex_.unlock();

        qDebug() << "JQNetworkConnectPool::onReadyToDelete: error: connect not contains" << connect.data();
        return;
    }

    if ( containsInConnecting )
    {
        QTimer::singleShot( 0, [ connect = connectForConnecting_[ connect.data() ] ](){} );
        connectForConnecting_.remove( connect.data() );
    }

    if ( containsInConnected )
    {
        QTimer::singleShot( 0, [ connect = connectForConnected_[ connect.data() ] ](){} );
        connectForConnected_.remove( connect.data() );
    }

    if ( containsInBimapForHostAndPort )
    {
        bimapForHostAndPort1.remove( bimapForHostAndPort2[ connect.data() ] );
        bimapForHostAndPort2.remove( connect.data() );
    }

    if ( containsInBimapForSocketDescriptor )
    {
        bimapForSocketDescriptor1.remove( bimapForSocketDescriptor2[ connect.data() ] );
        bimapForSocketDescriptor2.remove( connect.data() );
    }

    mutex_.unlock();
}
