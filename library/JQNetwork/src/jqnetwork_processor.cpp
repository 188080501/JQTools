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

JQNetworkProcessor::JQNetworkProcessor(const bool &invokeMethodByProcessorThread):
    invokeMethodByProcessorThread_( invokeMethodByProcessorThread )
{
    static bool flag = true;
    if ( flag )
    {
        flag = false;
        qRegisterMetaType< QVariantMap >( "QVariantMap" );
    }
}

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
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedArg, const JQNetworkPackageSharedPointer &package) > > receiveArgumentMaker;

        QSharedPointer< std::function< JQNetworkVoidSharedPointer() > > sendArgumentPreparer;
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendArg) > > sendArgumentMaker;
        QSharedPointer< std::function< void(const JQNetworkConnectPointer &connect, const JQNetworkPackageSharedPointer &package, const JQNetworkVoidSharedPointer &sendArg, const QVariantMap &sendAppend) > > sendArgumentAnswer;

        QSharedPointer< std::function< JQNetworkVoidSharedPointer() > > receiveAppendArgumentPreparer;
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedAppendArg, const JQNetworkPackageSharedPointer &package) > > receiveAppendArgumentMaker;

        QSharedPointer< std::function< JQNetworkVoidSharedPointer() > > sendAppendArgumentPreparer;
        QSharedPointer< std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendAppendArg) > > sendAppendArgumentMaker;

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
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &receivedArg, const auto &package)
                {
                    ( *static_cast< QByteArray * >( receivedArg.get() ) ) = package->payloadData();
                    return Q_ARG( const QByteArray &, *static_cast< const QByteArray * >( receivedArg.get() ) );
                } ) );
            }
            else if ( currentSum == "QVariantMap:received" )
            {
                receiveArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QVariantMap, &JQNetworkProcessor::deleteVariantMap );
                } ) );
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &receivedArg, const auto &package)
                {
                    ( *static_cast< QVariantMap * >( receivedArg.get() ) ) = QJsonDocument::fromJson( package->payloadData() ).object().toVariantMap();
                    return Q_ARG( const QVariantMap &, *static_cast< const QVariantMap * >( receivedArg.get() ) );
                } ) );
            }
            else if ( currentSum == "QFileInfo:received" )
            {
                receiveArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QFileInfo, &JQNetworkProcessor::deleteFileInfo);
                } ) );
                receiveArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &receivedArg, const auto &package)
                {
                    ( *static_cast< QFileInfo * >( receivedArg.get() ) ) = QFileInfo( package->localFilePath() );
                    return Q_ARG( const QFileInfo &, *static_cast< const QFileInfo * >( receivedArg.get() ) );
                } ) );
            }
            else if ( !method.parameterNames()[ 0 ].isEmpty() )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
                continue;
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
                sendArgumentAnswer.reset( new std::function< void(
                                              const JQNetworkConnectPointer &connect,
                                              const JQNetworkPackageSharedPointer &package,
                                              const JQNetworkVoidSharedPointer &sendArg,
                                              const QVariantMap &sendAppend
                                          ) >
                                          ( [ ](
                                            const auto &connect,
                                            const auto &package,
                                            const auto &sendArg,
                                            const auto &sendAppend
                                        )
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    if ( !package->randomFlag() )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: when the randomFlag is 0, the reply is not allowed";
                        return;
                    }

                    const auto &&replyReply = connect->replyPayloadData(
                                package->randomFlag(),
                                *static_cast< QByteArray * >( sendArg.get() ),
                                sendAppend
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
                sendArgumentAnswer.reset( new std::function< void(
                                              const JQNetworkConnectPointer &connect,
                                              const JQNetworkPackageSharedPointer &package,
                                              const JQNetworkVoidSharedPointer &sendArg,
                                              const QVariantMap &sendAppend
                                          ) >
                                          ( [ ](
                                            const auto &connect,
                                            const auto &package,
                                            const auto &sendArg,
                                            const auto &sendAppend
                                        )
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    if ( !package->randomFlag() )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: when the randomFlag is 0, the reply is not allowed";
                        return;
                    }

                    const auto &&replyReply = connect->replyPayloadData(
                                package->randomFlag(),
                                QJsonDocument( QJsonObject::fromVariantMap( *static_cast< QVariantMap * >( sendArg.get() ) ) ).toJson( QJsonDocument::Compact ),
                                sendAppend
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
                sendArgumentAnswer.reset( new std::function< void(
                                              const JQNetworkConnectPointer &connect,
                                              const JQNetworkPackageSharedPointer &package,
                                              const JQNetworkVoidSharedPointer &sendArg,
                                              const QVariantMap &sendAppend
                                          ) >
                                          ( [ ](
                                            const auto &connect,
                                            const auto &package,
                                            const auto &sendArg,
                                            const auto &sendAppend
                                        )
                {
                    if ( !connect )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: connect is null";
                        return;
                    }

                    if ( !package->randomFlag() )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: when the randomFlag is 0, the reply is not allowed";
                        return;
                    }

                    const auto &sendFileInfo = *static_cast< QFileInfo * >( sendArg.get() );

                    if ( !sendFileInfo.isFile() )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: current fileinfo is not file:" << sendFileInfo.filePath();
                        return;
                    }

                    const auto &&replyReply = connect->replyFile(
                                package->randomFlag(),
                                sendFileInfo,
                                sendAppend
                            );
                    if ( !replyReply )
                    {
                        qDebug() << "JQNetworkProcessor::availableSlots: replyPayloadData error";
                    }
                } ) );
            }
            else if ( !method.parameterNames()[ 1 ].isEmpty() )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
                continue;
            }
        }

        if ( method.parameterTypes().size() >= 3 )
        {
            const auto &&currentSum = QString( "%1:%2" ).arg( QString( method.parameterTypes()[ 2 ] ), QString( method.parameterNames()[ 2 ] ) );

            if ( currentSum == "QVariantMap:receivedAppend" )
            {
                receiveAppendArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QVariantMap, &JQNetworkProcessor::deleteVariantMap );
                } ) );
                receiveAppendArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &receivedAppendArg, const JQNetworkPackageSharedPointer &package) >
                                            ( [ ](const auto &receivedAppendArg, const auto &package)
                {
                    ( *static_cast< QVariantMap * >( receivedAppendArg.get() ) ) = package->appendData();
                    return Q_ARG( const QVariantMap &, *static_cast< const QVariantMap * >( receivedAppendArg.get() ) );
                } ) );
            }
            else if ( !method.parameterNames()[ 2 ].isEmpty() )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
                continue;
            }
        }

        if ( method.parameterTypes().size() >= 4 )
        {
            const auto &&currentSum = QString( "%1:%2" ).arg( QString( method.parameterTypes()[ 3 ] ), QString( method.parameterNames()[ 3 ] ) );

            if ( currentSum == "QVariantMap&:sendAppend" )
            {
                sendAppendArgumentPreparer.reset( new std::function< JQNetworkVoidSharedPointer() >
                                            ( [ ]()
                {
                    return JQNetworkVoidSharedPointer( new QVariantMap, &JQNetworkProcessor::deleteVariantMap );
                } ) );
                sendAppendArgumentMaker.reset( new std::function< QGenericArgument(const JQNetworkVoidSharedPointer &sendAppendArg) >
                                         ( [ ](const auto &sendAppendArg)
                {
                    return Q_ARG( QVariantMap &, ( QVariantMap & )*( QVariantMap * )sendAppendArg.get() );
                } ) );
            }
            else if ( !method.parameterNames()[ 3 ].isEmpty() )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: Unknow argument:" << currentSum;
                continue;
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
                    sendArgumentAnswer,
                    receiveAppendArgumentPreparer,
                    receiveAppendArgumentMaker,
                    sendAppendArgumentPreparer,
                    sendAppendArgumentMaker
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

            JQNetworkVoidSharedPointer receiveAppendArg;
            if ( receiveAppendArgumentPreparer )
            {
                receiveAppendArg = ( *receiveAppendArgumentPreparer )();
            }

            JQNetworkVoidSharedPointer sendAppendArg;
            if ( sendAppendArgumentPreparer )
            {
                sendAppendArg = ( *sendAppendArgumentPreparer )();
            }

            const auto &&invokeMethodReply = QMetaObject::invokeMethod(
                        this,
                        methodName.data(),
                        ( ( invokeMethodByProcessorThread_ ) ? ( Qt::QueuedConnection ) : ( Qt::DirectConnection ) ),
                        ( ( receiveArgumentMaker ) ? ( ( *receiveArgumentMaker )( receiveArg, package ) ) : ( QGenericArgument() ) ),
                        ( ( sendArgumentMaker ) ? ( ( *sendArgumentMaker )( sendArg ) ) : ( QGenericArgument() ) ),
                        ( ( receiveAppendArgumentMaker ) ? ( ( *receiveAppendArgumentMaker )( receiveAppendArg, package ) ) : ( QGenericArgument() ) ),
                        ( ( sendAppendArgumentMaker ) ? ( ( *sendAppendArgumentMaker )( sendAppendArg ) ) : ( QGenericArgument() ) )
                    );
            if ( !invokeMethodReply )
            {
                qDebug() << "JQNetworkProcessor::availableSlots: invokeMethod slot error:" << methodName;
            }

            if ( sendArgumentAnswer )
            {
                if ( sendAppendArg )
                {
                    ( *sendArgumentAnswer )( connect, package, sendArg, *static_cast< const QVariantMap * >( sendAppendArg.get() ) );
                }
                else
                {
                    ( *sendArgumentAnswer )( connect, package, sendArg, { } );
                }
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

bool JQNetworkProcessor::checkMapContains(const QStringList &keys, const QVariantMap &received, QVariantMap &send)
{
    for ( const auto &key: keys )
    {
        if ( !received.contains( key ) )
        {
            JQNP_FAIL( QString( "error: %1 not contains" ).arg( key ) );
        }
    }

    return true;
}

bool JQNetworkProcessor::checkMapContainsAndNot0(const QStringList &keys, const QVariantMap &received, QVariantMap &send)
{
    for ( const auto &key: keys )
    {
        if ( !received.contains( key ) || !received[ key ].toLongLong() )
        {
            JQNP_FAIL( QString( "error: %1 is 0" ).arg( key ) );
        }
    }

    return true;
}

bool JQNetworkProcessor::checkMapContainsAndNotEmpty(const QStringList &keys, const QVariantMap &received, QVariantMap &send)
{
    for ( const auto &key: keys )
    {
        if ( !received.contains( key ) || received[ key ].toString().isEmpty() )
        {
            JQNP_FAIL( QString( "error: %1 is empty" ).arg( key ) );
        }
    }

    return true;
}

bool JQNetworkProcessor::checkDataContasinsExpectedContent(const QString &key, const QVariantList &expectedContentList, const QVariantMap &received, QVariantMap &send)
{
    if ( !checkMapContains( { key }, received, send ) ) { return false; }

    const auto &&data = received[ key ];

    if ( data.isNull() ) { JQNP_FAIL( QString( "error: %1 is null" ).arg( key ) ) }

    for ( const auto &expectedContent: expectedContentList )
    {
        if ( data == expectedContent )
        {
            return true;
        }
    }

    auto message = QString( "error: %1 not match, expected: " );

    for ( auto index = 0; index < expectedContentList.length(); ++index )
    {
        if ( !index )
        {
            message += "/";
        }

        message += expectedContentList[ index ].toString();
    }

    JQNP_FAIL( message );
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
