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

#ifndef __JQSettings_h__
#define __JQSettings_h__

// C lib import
#include <assert.h>

// Qt lib import
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QSharedPointer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>

#define JQSettings_DefaultProjectGroupName "JasonQt"

namespace JQSettings
{

QString documentsPath(const QString &projectName, const QString &projectGroupName = JQSettings_DefaultProjectGroupName);

QSharedPointer<QSettings> settingsFile(const QString &fileName, const QString &projectName, const QString &projectGroupName = JQSettings_DefaultProjectGroupName);

class Set: public QObject
{
    Q_OBJECT

public:
    Set(const QString &fileName, const QString &groupName, const QString &projectName, const QString &projectGroupName = JQSettings_DefaultProjectGroupName);

    ~Set(void);

    QJsonValue operator[](const QString &key);

    QString filePath(void) const;

public slots:
    bool contains(const QString &key);

    QJsonValue value(const QString &key, const QJsonValue &defaultValue);

    QJsonValue value(const QString &key);

    void setValue(const QString &key, const QJsonValue &data);

    void save(void);

    void readySave(const int &wait = 1000);

    void read(void);

private:
    QString filePath_;
    QString groupName_;

    QMap< QString, QJsonValue > datas_;

    QTimer *timer_;
};

}

#endif//__JQSettings_h__
