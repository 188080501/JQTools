/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_processor.h"

// Qt lib import
#include <QDebug>
#include <QThread>
#include <QMetaObject>
#include <QMetaMethod>
#include <QVariantMap>
#include <QJsonDocument>
#include <QJsonObject>

// JQNetwork lib import
#include <JQNetworkServer>
#include <JQNetworkConnect>
#include <JQNetworkPackage>

// JQNetworkProcessor
QSet< QString > JQNetworkProcessor::exceptionSlots_( { "deleteLater", "_q_reregisterTimers" } );

QSet< QString > JQNetworkProcessor::availableSlots()
{
    if ( !availableSlots_.isEmpty() ) { return availableSlots_; }

    for ( auto index = 0; index < this->metaObject()->methodCount(); ++index )
    {
        const auto &&method = this->metaObject()->method( index );

        if ( method.methodType() != QMetaMethod::Slot ) { continue; }

        const auto &&methodName = method.name();

        if ( exceptionSlots_.contains( methodName ) ) { continue; }

        if ( onpackageReceivedCallbacks_.contains( methodName ) )
        {
            qDebug() << "JQNetworkProcessor::availableSlots: same name slot:" << methodName;
            continue;
        }

        const auto &&slotString = QString( "(%1):(%2)" ).arg( QString( method.parameterTypes().join( "," ) ), QString( method.parameterNames().join( "," ) ) );

        if ( slotString == "(QVariantMap,QVariantMap&):(received,send)" )
        {
            onpackageReceivedCallbacks_[ methodName ] = [ this, methodName ](const auto &connect, const auto &package)
            {
                QVariantMap received = QJsonDocument::fromJson( package->payloadData() ).object().toVariantMap();
                QVariantMap send;

                const auto &&invokeMethodReply = QMetaObject::invokeMethod(
                            this,
                            methodName.data(),
                            Qt::DirectConnection,
                            Q_ARG( QVariantMap, received ),
                            Q_ARG( QVariantMap &, send )
                        );
                if ( !invokeMethodReply )
                {
                    qDebug() << "JQNetworkProcessor: invokeMethod slot error:" << methodName;
                }

                if ( !send.isEmpty() )
                {
                    const auto &&replyReply = connect->replyPayloadData(
                                package->randomFlag(),
                                QJsonDocument( QJsonObject::fromVariantMap( send ) ).toJson( QJsonDocument::Compact )
                            );
                    if ( !replyReply )
                    {
                        qDebug() << "JQNetworkProcessor: replyPayloadData error";
                    }
                }
            };
        }
        else if ( slotString == "(QVariantMap):(received)" )
        {
            onpackageReceivedCallbacks_[ methodName ] = [ this, methodName ](const auto &, const auto &package)
            {
                QVariantMap received = QJsonDocument::fromJson( package->payloadData() ).object().toVariantMap();

                const auto &&invokeMethodReply = QMetaObject::invokeMethod(
                            this,
                            methodName.data(),
                            Qt::DirectConnection,
                            Q_ARG( QVariantMap, received )
                        );
                if ( !invokeMethodReply )
                {
                    qDebug() << "JQNetworkProcessor: invokeMethod slot error:" << methodName;
                }
            };
        }
        else if ( slotString == "():()" )
        {
            onpackageReceivedCallbacks_[ methodName ] = [ this, methodName ](const auto &, const auto &)
            {
                const auto &&invokeMethodReply = QMetaObject::invokeMethod(
                            this,
                            methodName.data(),
                            Qt::DirectConnection
                        );
                if ( !invokeMethodReply )
                {
                    qDebug() << "JQNetworkProcessor: invokeMethod slot error:" << methodName;
                }
            };
        }
        else
        {
            qDebug() << "JQNetworkProcessor::availableSlots: unknow parameter type:" << slotString;
            continue;
        }

        availableSlots_.insert( methodName );
    }

    return availableSlots_;
}

bool JQNetworkProcessor::handlePackage(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package)
{
    auto currentThreadConnect = connectMapByThread_.find( QThread::currentThread() );

    if ( currentThreadConnect == connectMapByThread_.end() )
    {
        qDebug() << "JQNetworkProcessor::onPackageReceived: expectation thread:" << QThread::currentThread();
        return false;
    }

    *currentThreadConnect = connect;

    const auto &&actionFlag = package->metaDataActionFlag();

    auto itForCallback = onpackageReceivedCallbacks_.find( actionFlag );
    if ( itForCallback == onpackageReceivedCallbacks_.end() )
    {
        qDebug() << "JQNetworkProcessor::onPackageReceived: expectation actionFlag:" << actionFlag;
        *currentThreadConnect = nullptr;
        return false;
    }

    ( *itForCallback )( connect, package );

    *currentThreadConnect = nullptr;

    return true;
}

void JQNetworkProcessor::setReceivedPossibleThreads(const QSet< QThread * > &threads)
{
    for ( const auto &thread: threads )
    {
        connectMapByThread_[ thread ] = nullptr;
    }
}

JQNetworkConnectPointer JQNetworkProcessor::currentThreadConnect()
{
    auto currentThreadConnect = connectMapByThread_.find( QThread::currentThread() );

    if ( currentThreadConnect == connectMapByThread_.end() )
    {
        qDebug() << "JQNetworkProcessor::currentThreadConnect: expectation thread:" << QThread::currentThread();
        return nullptr;
    }

    return *currentThreadConnect;
}
