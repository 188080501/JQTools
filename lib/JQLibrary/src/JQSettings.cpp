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
#include <QSettings>
#include <QDir>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTimer>

using namespace JQSettings;

QString JQSettings::documentsPath(const QString &projectName)
{
    if ( projectName.isEmpty() )
    {
        qDebug() << "JQSettings::documentsPath: warning: projectName is empty";
        return "";
    }

#if (defined Q_OS_IOS)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    dir.cdUp();
    dir.cd( "Library" );
    dir.cd( "Preferences" );
    return dir.path() + "/";

#elif (defined Q_OS_ANDROID)

    return "/sdcard/" + projectName + "/";

#elif (defined Q_OS_MAC)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    dir.cdUp();
    dir.cd( "C" );
    return dir.path() + "/" + projectName + "/";

#elif (defined Q_OS_WIN)

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) );
    dir.cdUp();
    return dir.path() + "/" + projectName + "/";

#else

    QDir dir( QStandardPaths::writableLocation( QStandardPaths::TempLocation ) );
    return dir.path() + "/" + projectName + "/";

#endif
}

QSharedPointer< QSettings > JQSettings::settingsFile(const QString &fileName, const QString &projectName)
{
    if ( fileName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: fileName is empty";
    }

    if ( projectName.isEmpty() )
    {
        qDebug() << "JQSettings::settingsFile: warning: projectName is empty";
    }

    return QSharedPointer< QSettings >( new QSettings( JQSettings::documentsPath( projectName ) + fileName, QSettings::IniFormat ) );
}

Set::Set(const QString &fileName, const QString &defaultGroup, const QString &projectName):
    settingsFilePath_( documentsPath( projectName ) + fileName ),
  defaultGroupName_( defaultGroup )
{
    this->read();
}

Set::Set(const QString &settingsFilePath, const QString &defaultGroup):
    settingsFilePath_( settingsFilePath ),
    defaultGroupName_( defaultGroup )
{
    this->read();
}

Set::~Set()
{
    if ( timerForSaveLater_ )
    {
        if ( timerForSaveLater_->isActive() )
        {
            this->save();
        }
        timerForSaveLater_.clear();
    }
}

JQSettingsSetSharedPointer Set::createSet(const QString &fileName, const QString &defaultGroup, const QString &projectName)
{
    JQSettingsSetSharedPointer result( new Set( fileName, defaultGroup, projectName ) );

    return result;
}

JQSettingsSetSharedPointer Set::createSet(const QString &settingsFilePath, const QString &defaultGroup)
{
    JQSettingsSetSharedPointer result( new Set( settingsFilePath, defaultGroup ) );

    return result;
}

QString Set::settingsFilePath() const
{
    return settingsFilePath_;
}

bool Set::contains(const QString &key)
{
    return allValues_[ defaultGroupName_ ].contains( key );
}

QVariant Set::value(const QString &groupName, const QString &key) const
{
    if ( !allValues_[ groupName ].contains( key ) )
    {
        return { };
    }
    return allValues_[ key ];
}

QVariant Set::value(const QString &key) const
{
    if ( !allValues_[ defaultGroupName_ ].contains( key ) )
    {
        return { };
    }
    return allValues_[ key ];
}

QVariantMap Set::values(const QString &groupName)
{
    if ( !allValues_.contains( groupName ) ) { return { }; }

    return allValues_[ groupName ];
}

QVariantMap Set::values()
{
    if ( !allValues_.contains( defaultGroupName_ ) ) { return { }; }

    return allValues_[ defaultGroupName_ ];
}

void Set::setValue(const QString &groupName, const QString &key, const QVariant &value)
{
    allValues_[ groupName ][ key ] = value;
    this->saveLater();
}

void Set::setValue(const QString &key, const QVariant &value)
{
    allValues_[ defaultGroupName_ ][ key ] = value;
    this->saveLater();
}

void Set::setValues(const QString &groupName, const QVariantMap &values)
{
    allValues_[ groupName ] = values;
    this->saveLater();
}

void Set::setValues(const QVariantMap &values)
{
    allValues_[ defaultGroupName_ ] = values;
    this->saveLater();
}

void Set::save()
{
#ifdef Q_OS_IOS
    QSettings settings( projectName_, fileName_ );
#else
#   ifdef Q_OS_MAC
    QSettings settings( settingsFilePath_, QSettings::NativeFormat );
#   else
    QSettings settings( filePath_ );
#   endif
#endif

    for ( auto itForGroup = allValues_.begin(); itForGroup != allValues_.end(); ++itForGroup )
    {
        settings.beginGroup( itForGroup.key() );

        for ( auto itForData = itForGroup.value().begin(); itForData != itForGroup.value().end(); ++itForData )
        {
            settings.setValue( itForData.key(), itForData.value() );
        }

        settings.endGroup();
    }
}

void Set::saveLater(const int &delayTime)
{
    if ( !timerForSaveLater_ )
    {
        timerForSaveLater_.reset( new QTimer );
        timerForSaveLater_->setSingleShot( true );

        connect( timerForSaveLater_.data(), &QTimer::timeout, this, &Set::save );
    }

    if ( timerForSaveLater_->isActive() )
    {
        timerForSaveLater_->stop();
    }

    timerForSaveLater_->start( delayTime );
}

void Set::read()
{
#ifdef Q_OS_IOS
    QSettings settings( projectName_, fileName_ );
#else
#   ifdef Q_OS_MAC
    QSettings settings( settingsFilePath_, QSettings::NativeFormat );
#   else
    QSettings settings( filePath_ );
#   endif
#endif
    
    allValues_.clear();

    for ( const auto &group: settings.childGroups() )
    {
        settings.beginGroup( group );

        for ( const auto &key: settings.allKeys() )
        {
            allValues_[ group ][ key ] = settings.value( key );
        }

        settings.endGroup();
    }
}
