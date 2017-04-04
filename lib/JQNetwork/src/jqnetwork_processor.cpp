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
#include <QFileInfo>

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

        QSharedPointer< std::function< JQNetworkVoidSharedPointer() > > receiveArgumentPreparer;
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg, const JQNetworkPackageSharedPointer &package) > > receiveArgumentMaker;

        QSharedPointer< std::function< JQNetworkVoidSharedPointer() > > sendArgumentPreparer;
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg) > > sendArgumentMaker;
        QSharedPointer< std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package, const JQNetworkVoidSharedPointer &sendArg) > > sendArgumentAnswer;

        if ( method.parameterTypes().size() >= 1 )
        {
            const auto &&currentSum = QString( "%1:%2" ).arg( QString( method.parameterTypes()[ 0 ] ), QString( method.parameterNames()[ 0 ] ) );

            if ( currentSum == "QByteArray:received" )
            {
                receiveArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QByteArray, &JQNetworkProcessor::deleteByteArray );
                } ) );
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &sendArg, const auto &package)
                {
                    ( *( QByteArray * )sendArg.get() ) = package->payloadData();
                    return Q_ARG( const QByteArray &, *( const QByteArray * )sendArg.get() );
                } ) );
            }
            else if ( currentSum == "QVariantMap:received" )
            {
                receiveArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QVariantMap, &JQNetworkProcessor::deleteVariantMap );
                } ) );
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &sendArg, const auto &package)
                {
                    ( *( QVariantMap * )sendArg.get() ) = QJsonDocument::fromJson( package->payloadData() ).object().toVariantMap();
                    return Q_ARG( const QVariantMap &, *( const QVariantMap * )sendArg.get() );
                } ) );
            }
            else if ( currentSum == "QFileInfo:received" )
            {
                receiveArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QFileInfo, &JQNetworkProcessor::deleteFileInfo);
                } ) );
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &sendArg, const auto &package)
                {
                    ( *( QFileInfo * )sendArg.get() ) = QFileInfo( package->localFilePath() );
                    return Q_ARG( const QFileInfo &, *( const QFileInfo * )sendArg.get() );
                } ) );
            }
            else
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
            }
        }

        if ( method.parameterTypes().size() >= 2 )
        {
            const auto &&currentSum = QString( "%1:%2" ).arg( QString( method.parameterTypes()[ 1 ] ), QString( method.parameterNames()[ 1 ] ) );

            if ( currentSum == "QByteArray&:send" )
            {
                sendArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QByteArray, &JQNetworkProcessor::deleteByteArray );
                } ) );
                sendArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg) >
                                         ( [ ](const auto &sendArg)
                {
                    return Q_ARG( QByteArray &, ( QByteArray & )*( QByteArray * )sendArg.get() );
                } ) );
                sendArgumentAnswer.reset( new std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package, const JQNetworkVoidSharedPointer &sendArg) >
                                          ( [ ](const auto &connect, const auto &package, const auto &sendArg)
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    const auto &&replyReply = connect->replyPayloadData(
                                package->randomFlag(),
                                *( QByteArray * )sendArg.get()
                            );
                    if ( !replyReply )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: replyPayloadData error";
                    }
                } ) );
            }
            else if ( currentSum == "QVariantMap&:send" )
            {
                sendArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QVariantMap, &JQNetworkProcessor::deleteVariantMap );
                } ) );
                sendArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg) >
                                         ( [ ](const auto &sendArg)
                {
                    return Q_ARG( QVariantMap &, ( QVariantMap & )*( QVariantMap * )sendArg.get() );
                } ) );
                sendArgumentAnswer.reset( new std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package, const JQNetworkVoidSharedPointer &sendArg) >
                                          ( [ ](const auto &connect, const auto &package, const auto &sendArg)
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    const auto &&replyReply = connect->replyPayloadData(
                                package->randomFlag(),
                                QJsonDocument( QJsonObject::fromVariantMap( *( QVariantMap * )sendArg.get() ) ).toJson( QJsonDocument::Compact )
                            );
                    if ( !replyReply )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: replyPayloadData error";
                    }
                } ) );
            }
            else if ( currentSum == "QFileInfo&:send" )
            {
                sendArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QFileInfo, &JQNetworkProcessor::deleteFileInfo );
                } ) );
                sendArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg) >
                                         ( [ ](const auto &sendArg)
                {
                    return Q_ARG( QFileInfo &, ( QFileInfo & )*( QFileInfo * )sendArg.get() );
                } ) );
                sendArgumentAnswer.reset( new std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package, const JQNetworkVoidSharedPointer &sendArg) >
                                          ( [ ](const auto &connect, const auto &package, const auto &sendArg)
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    const auto &sendFileInfo = *( QFileInfo * )sendArg.get();

                    if ( !sendFileInfo.isFile() )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: not file:" << sendFileInfo.filePath();
                        return;
                    }

                    const auto &&replyReply = connect->replyFile(
                                package->randomFlag(),
                                sendFileInfo
                            );
                    if ( !replyReply )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: replyPayloadData error";
                    }
                } ) );
            }
            else
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
            }
        }

        onpackageReceivedCallbacks_[ methodName ] =
                [
                    this,
                    methodName,
                    receiveArgumentPreparer,
                    receiveArgumentMaker,
                    sendArgumentPreparer,
                    sendArgumentMaker,
                    sendArgumentAnswer
                ]
                (const auto &connect, const auto &package)
        {
            JQNetworkVoidSharedPointer receiveArg;
            if ( receiveArgumentPreparer )
            {
                receiveArg = ( *receiveArgumentPreparer )();
            }

            JQNetworkVoidSharedPointer sendArg;
            if ( sendArgumentPreparer )
            {
                sendArg = ( *sendArgumentPreparer )();
            }

            const auto &&invokeMethodReply = QMetaObject::invokeMethod(
                        this,
                        methodName.data(),
                        Qt::DirectConnection,
                        ( ( receiveArgumentMaker ) ? ( ( *receiveArgumentMaker )( receiveArg, package ) ) : ( QGenericArgument() ) ),
                        ( ( sendArgumentMaker ) ? ( ( *sendArgumentMaker )( sendArg ) ) : ( QGenericArgument() ) )
                    );
            if ( !invokeMethodReply )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: invokeMethod slot error:" << methodName;
            }

            if ( sendArgumentAnswer )
            {
                ( *sendArgumentAnswer )( connect, package, sendArg );
            }
        };

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

    const auto &&targetActionFlag = package->targetActionFlag();

    auto itForCallback = onpackageReceivedCallbacks_.find( targetActionFlag );
    if ( itForCallback == onpackageReceivedCallbacks_.end() )
    {
        qDebug() << "JQNetworkProcessor::onPackageReceived: expectation targetActionFlag:" << targetActionFlag;
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

void JQNetworkProcessor::deleteFileInfo(QFileInfo *ptr)
{
    delete ptr;
}
