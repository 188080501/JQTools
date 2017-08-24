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

#ifndef JQSETTINGS_H_
#define JQSETTINGS_H_

// Qt lib import
#include <QSharedPointer>
#include <QVariant>

class QTimer;
class QSettings;

namespace JQSettings{ class Set; }

typedef QSharedPointer< JQSettings::Set > JQSettingsSetSharedPointer;

namespace JQSettings
{

QString documentsPath(const QString &projectName);

QSharedPointer< QSettings > settingsFile(const QString &fileName, const QString &projectName);

class Set: public QObject
{
    Q_OBJECT

private:
    Set(const QString &fileName, const QString &defaultGroup, const QString &projectName);

    Set(const QString &settingsFilePath, const QString &defaultGroup);

public:
    ~Set();

    static JQSettingsSetSharedPointer createSet(const QString &fileName, const QString &defaultGroup, const QString &projectName);

    static JQSettingsSetSharedPointer createSet(const QString &settingsFilePath, const QString &defaultGroup);

    QString settingsFilePath() const;

public slots:
    bool contains(const QString &key);

    QVariant value(const QString &groupName, const QString &key) const;

    QVariant value(const QString &key) const;

    QVariantMap values(const QString &groupName);

    QVariantMap values();

    void setValue(const QString &groupName, const QString &key, const QVariant &value);

    void setValue(const QString &key, const QVariant &value);

    void setValues(const QString &groupName, const QVariantMap &values);

    void setValues(const QVariantMap &values);

    void save();

    void saveLater(const int &delayTime = 1000);

    void read();

private:
    QString settingsFilePath_;
    QString defaultGroupName_;

    QMap< QString, QVariantMap > allValues_; // group -> key -> value
    QSharedPointer< QTimer > timerForSaveLater_;
};

}

#endif//JQSETTINGS_H_
