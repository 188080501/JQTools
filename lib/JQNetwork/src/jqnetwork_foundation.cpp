/*
    This file is part of JQNetwork
    
    Library introduce: https://github.com/188080501/JQNetwork

    Copyright: Jason

    Contact email: Jason@JasonServer.com
    
    GitHub: https://github.com/188080501/
*/

#include "jqnetwork_foundation.h"

// Qt lib import
#include <QDebug>
#include <QThreadPool>
#include <QSemaphore>
#include <QVector>
#include <QCryptographicHash>
#include <QHostInfo>
#include <QtConcurrent>
#include <QLocale>
#include <QTime>

// JQNetworkThreadPoolHelper
JQNetworkThreadPoolHelper::JQNetworkThreadPoolHelper():
    waitForRunCallbacks_( new std::vector< std::function< void() > > )
{ }

void JQNetworkThreadPoolHelper::run(const std::function< void() > &callback)
{
    mutex_.lock();

    waitForRunCallbacks_->push_back( callback );

    if ( !alreadyCall_ )
    {
        alreadyCall_ = true;
        QMetaObject::invokeMethod(
                    this,
                    "onRun",
                    Qt::QueuedConnection
                );
    }

    mutex_.unlock();
}

void JQNetworkThreadPoolHelper::onRun()
{
    auto currentTime = QDateTime::currentMSecsSinceEpoch();

    if ( ( ( currentTime - lastRunTime_ ) < 5 ) && ( lastRunCallbackCount_ > 10 ) )
    {
        QThread::msleep( 5 );
    }

    std::vector< std::function< void() > > callbacks;

    mutex_.lock();

    callbacks = *waitForRunCallbacks_;
    waitForRunCallbacks_->clear();

    alreadyCall_ = false;

    lastRunTime_ = currentTime;
    lastRunCallbackCount_ = callbacks.size();

    mutex_.unlock();

    for ( const auto &callback: callbacks )
    {
        callback();
    }
}

// JQNetworkThreadPool
JQNetworkThreadPool::JQNetworkThreadPool(const int &threadCount):
    threadPool_( new QThreadPool ),
    eventLoops_( new QVector< QPointer< QEventLoop > > ),
    helpers_( new QVector< QPointer< JQNetworkThreadPoolHelper > > )
{
    threadPool_->setMaxThreadCount( threadCount );
    eventLoops_->resize( threadCount );
    helpers_->resize( threadCount );

    QSemaphore semaphoreForThreadStart;

    for ( auto index = 0; index < threadCount; ++index )
    {
        QtConcurrent::run(
                    threadPool_.data(),
                    [
                        this,
                        index,
                        &semaphoreForThreadStart
                    ]()
                    {
                        QEventLoop eventLoop;
                        JQNetworkThreadPoolHelper helper;

                        ( *this->eventLoops_ )[ index ] = &eventLoop;
                        ( *this->helpers_ )[ index ] = &helper;

                        semaphoreForThreadStart.release( 1 );
                        eventLoop.exec();
                    }
                );
    }

    semaphoreForThreadStart.acquire( threadCount );
}

JQNetworkThreadPool::~JQNetworkThreadPool()
{
    for ( const auto &eventLoop: *eventLoops_ )
    {
        QMetaObject::invokeMethod( eventLoop.data(), "quit" );
    }

    threadPool_->waitForDone();
}

int JQNetworkThreadPool::run(const std::function< void() > &callback, const int &threadIndex)
{
    if ( threadIndex == -1 )
    {
        rotaryIndex_ = ( rotaryIndex_ + 1 ) % helpers_->size();
    }

    const auto index = ( threadIndex == -1 ) ? ( rotaryIndex_ ) : ( threadIndex );

    ( *helpers_ )[ index ]->run( callback );

    return index;
}

int JQNetworkThreadPool::waitRun(const std::function<void ()> &callback, const int &threadIndex)
{
    QSemaphore semaphore;

    auto index = this->run(
                [
                    &semaphore,
                    &callback
                ]()
                {
                    callback();
                    semaphore.release( 1 );
                },
                threadIndex
    );

    semaphore.acquire( 1 );

    return index;
}

// JQNetworkNodeMark
qint64 JQNetworkNodeMark::applicationStartTime_ = QDateTime::currentMSecsSinceEpoch();
QString JQNetworkNodeMark::applicationFilePath_;
QString JQNetworkNodeMark::localHostName_;

JQNetworkNodeMark::JQNetworkNodeMark(const QString &dutyMark):
    nodeMarkCreatedTime_( QDateTime::currentMSecsSinceEpoch() ),
    nodeMarkClassAddress_( QString::number( (qint64)this, 16 ) ),
    dutyMark_( dutyMark )
{
    if ( applicationFilePath_.isEmpty() )
    {
        applicationFilePath_ = qApp->applicationFilePath();
        localHostName_ = QHostInfo::localHostName();
    }

    nodeMarkSummary_ = QCryptographicHash::hash(
                QString( "%1:%2:%3:%4:%5:%6" ).arg(
                    QString::number( applicationStartTime_ ),
                    applicationFilePath_,
                    localHostName_,
                    QString::number( nodeMarkCreatedTime_ ),
                    nodeMarkClassAddress_,
                    dutyMark_
                    ).toUtf8(),
                QCryptographicHash::Md5
            ).toHex();
}

QString JQNetworkNodeMark::calculateNodeMarkSummary(const QString &dutyMark)
{
    JQNetworkNodeMark nodeMark( dutyMark );
    return nodeMark.nodeMarkSummary();
}

// JQNetwork
void JQNetwork::printVersionInformation(const char *jqNetworkCompileModeString)
{
    qDebug() << "JQNetwork library version:" << ( JQNETWORK_VERSIONNUMBER.toString() )
#ifdef __STDC__
             << ", build in:" << QDateTime(
                    QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " " ), "MMM dd yyyy"),
                    QTime::fromString( __TIME__, "hh:mm:ss" )
                ).toString( "yyyy-MM-dd hh:mm:ss" )
#endif
            << ", compile mode:" << jqNetworkCompileModeString;
}
