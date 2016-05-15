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

using namespace JQSettings;

QString JQSettings::documentsPath(const QString &projectName, const QString &projectGroupName)
{
    assert(!projectName.isEmpty());
    assert(!projectGroupName.isEmpty());

#if (defined Q_OS_IOS)

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    dir.cdUp();
    dir.cd("Documents");
    return dir.path() + "/";

#elif (defined Q_OS_ANDROID)

    return "/sdcard/" + projectGroupName + "." + projectName + "/";

#elif (defined Q_OS_MAC)

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    dir.cdUp();
    dir.cd("C");
    return dir.path() + "/" + projectGroupName + "." + projectName + "/";

#elif (defined Q_OS_WIN)

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    dir.cdUp();
    return dir.path() + "/" + projectGroupName + "." + projectName + "/";

#else

    QDir dir(QStandardPaths::writableLocation(QStandardPaths::TempLocation));
    return dir.path() + "/" + projectGroupName + "." + projectName + "/";

#endif
}

QSharedPointer<QSettings> JQSettings::settingsFile(const QString &fileName, const QString &projectName, const QString &projectGroupName)
{
    assert(!fileName.isEmpty());

    return QSharedPointer<QSettings>(new QSettings(JQSettings::documentsPath(projectName, projectGroupName) + fileName, QSettings::IniFormat));
}

Set::Set(const QString &fileName, const QString &groupName, const QString &projectName, const QString &projectGroupName):
    filePath_(documentsPath(projectName, projectGroupName) + fileName),
    groupName_(groupName),
    timer_(nullptr)
{
    this->read();
}

Set::~Set(void)
{
    if (timer_)
    {
        if (timer_->isActive())
        {
            this->save();
        }
        delete timer_;
    }
}

QJsonValue Set::operator[](const QString &key)
{
    if (!datas_.contains(key))
    {
        this->readySave();
    }
    return datas_[key];
}

QString Set::filePath(void) const
{
    return filePath_;
}

bool Set::contains(const QString &key)
{
    return datas_.contains(key);
}

QJsonValue Set::value(const QString &key, const QJsonValue &defaultValue)
{
    if (!datas_.contains(key))
    {
        this->setValue(key, defaultValue);
    }
    return datas_[key];
}

QJsonValue Set::value(const QString &key)
{
    if (!datas_.contains(key))
    {
        return QJsonValue();
    }
    return datas_[key];
}

void Set::setValue(const QString &key, const QJsonValue &data)
{
    datas_[key] = data;
    this->readySave();
}

void Set::save(void)
{
    QSettings settings(filePath_);
    
    settings.beginGroup(groupName_);
    
    for (auto it = datas_.begin(); it != datas_.end(); it++)
    {
        QJsonObject buf;
        buf["type"] = (int)it.value().type();
        buf["data"] = it.value();
        settings.setValue(it.key(), QJsonDocument(buf).toJson());
    }
    
    settings.endGroup();
}

void Set::readySave(const int &wait)
{
    if (!timer_)
    {
        timer_ = new QTimer;
        timer_->setSingleShot(true);

        connect(timer_, SIGNAL(timeout()), this, SLOT(save()));
    }

    if (timer_->isActive())
    {
        timer_->stop();
    }

    timer_->start(wait);
}

void Set::read(void)
{
    QSettings settings(filePath_);
    
    settings.beginGroup(groupName_);
    
    datas_.clear();
    foreach (const auto &now, settings.allKeys())
    {
        const auto &&data = QJsonDocument::fromJson(settings.value(now).toByteArray()).object();
        switch (data["type"].toInt())
        {
            case QJsonValue::Bool:
            {
                datas_[now] = data["data"].toBool();
                break;
            }
            case QJsonValue::Double:
            {
                datas_[now] = data["data"].toDouble();
                break;
            }
            case QJsonValue::String:
            {
                datas_[now] = data["data"].toString();
                break;
            }
            default: { break; }
        }
    }
    
    settings.endGroup();
}
