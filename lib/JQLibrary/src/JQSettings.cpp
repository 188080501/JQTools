/*
    This file is part of JQLibrary

    Copyright: Jason

    Contact email: 188080501@qq.com

    GNU Lesser General Public License Usage
    Alternatively, this file may be used under the terms of the GNU Lesser
    General Public License version 2.1 or version 3 as published by the Free
    Software Foundation and appearing in the file LICENSE.LGPLv21 and
    LICENSE.LGPLv3 included in the packaging of this file. Please review the
    following information to ensure the GNU Lesser General Public License
    requirements will be met: https://www.gnu.org/licenses/lgpl.html and
    http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
*/

#include "JQSettings.h"

// Qt lib import
#include <QDir>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTimer>

using namespace JQSettings;

QString JQSettings::documentsPath(const QString &projectName, const QString &projectGroupName)
{
    if ( projectName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: projectName is empty";
    }

    if ( projectGroupName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: projectGroupName is empty";
    }

#if (defined Q_OS_IOS)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    dir.cdUp();
    dir.cd( "Library" );
    dir.cd( "Preferences" );
    return dir.path() + "/";

#elif (defined Q_OS_ANDROID)

    return "/sdcard/" + projectGroupName + "_" + projectName + "/";

#elif (defined Q_OS_MAC)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    dir.cdUp();
    dir.cd( "C" );
    return dir.path() + "/" + projectGroupName + "_" + projectName + "/";

#elif (defined Q_OS_WIN)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) );
    dir.cdUp();
    return dir.path() + "/" + projectGroupName + "_" + projectName + "/";

#else

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    return dir.path() + "/" + projectGroupName + "_" + projectName + "/";

#endif
}

QSharedPointer< QSettings > JQSettings::settingsFile(
        const QString &fileName,
        const QString &projectName,
        const QString &projectGroupName
    )
{
    if ( fileName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: fileName is empty";
    }

    if ( projectName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: projectName is empty";
    }

    if ( projectGroupName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: projectGroupName is empty";
    }

    return QSharedPointer< QSettings >( new QSettings( JQSettings::documentsPath( projectName, projectGroupName ) + fileName, QSettings::IniFormat ) );
}

Set::Set(
        const QString &fileName,
        const QString &groupName,
        const QString &projectName,
        const QString &projectGroupName
    ):
    fileName_( fileName ),
    groupName_( groupName ),
    projectName_( projectName ),
    filePath_( documentsPath( projectName, projectGroupName ) + fileName )
{
    this->read();
}

Set::~Set()
{
    if ( timer_ )
    {
        if ( timer_->isActive() )
        {
            this->save();
        }
        timer_.clear();
    }
}

QVariant Set::operator[](const QString &key) const
{
    if ( !datas_.contains( key ) )
    {
        return { };
    }
    return datas_[ key ];
}

QVariant Set::operator[](const QString &key)
{
    if ( !datas_.contains( key ) )
    {
        return { };
    }
    return datas_[ key ];
}

QString Set::filePath() const
{
    return filePath_;
}

bool Set::contains(const QString &key)
{
    return datas_.contains( key );
}

QVariant Set::value(const QString &key, const QVariant &defaultValue)
{
    if ( !datas_.contains( key ) )
    {
        this->setValue(key, defaultValue);
    }
    return datas_[ key ];
}

QVariant Set::value(const QString &key) const
{
    if ( !datas_.contains( key ) )
    {
        return { };
    }
    return datas_[ key ];
}

void Set::setValue(const QString &key, const QVariant &data)
{
    datas_[ key ] = data;
    this->readySave();
}

void Set::save()
{
#ifdef Q_OS_IOS
    QSettings settings( projectName_, fileName_ );
#else
#   ifdef Q_OS_MAC
    QSettings settings( filePath_, QSettings::NativeFormat );
#   else
    QSettings settings( filePath_ );
#   endif
#endif

    settings.beginGroup( groupName_ );

    for (auto it = datas_.begin(); it != datas_.end(); it++)
    {
        settings.setValue( it.key(), it.value() );
    }
    
    settings.endGroup();
}

void Set::readySave(const int &delayTime)
{
    if ( !timer_ )
    {
        timer_.reset( new QTimer );
        timer_->setSingleShot( true );

        connect( timer_.data(), &QTimer::timeout, this, &Set::save );
    }

    if ( timer_->isActive() )
    {
        timer_->stop();
    }

    timer_->start( delayTime );
}

void Set::read()
{
#ifdef Q_OS_IOS
    QSettings settings( projectName_, fileName_ );
#else
#   ifdef Q_OS_MAC
    QSettings settings( filePath_, QSettings::NativeFormat );
#   else
    QSettings settings( filePath_ );
#   endif
#endif

    settings.beginGroup( groupName_ );
    
    datas_.clear();

    for ( const auto &key: settings.allKeys() )
    {
        datas_[ key ] = settings.value( key );
    }
    
    settings.endGroup();
}
