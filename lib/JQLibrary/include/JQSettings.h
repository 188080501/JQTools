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

#ifndef __JQSETTINGS_H__
#define __JQSETTINGS_H__

// Qt lib import
#include <QSettings>
#include <QSharedPointer>
#include <QVariant>

#define JQSETTINGS_DEFAULTPROJECTGROUPNAME "JasonQt"

class QTimer;

namespace JQSettings
{

QString documentsPath(const QString &projectName, const QString &projectGroupName = JQSETTINGS_DEFAULTPROJECTGROUPNAME);

QSharedPointer< QSettings > settingsFile(
        const QString &fileName,
        const QString &projectName,
        const QString &projectGroupName = JQSETTINGS_DEFAULTPROJECTGROUPNAME
    );

class Set: public QObject
{
    Q_OBJECT

public:
    Set(
            const QString &fileName,
            const QString &groupName,
            const QString &projectName,
            const QString &projectGroupName = JQSETTINGS_DEFAULTPROJECTGROUPNAME
        );

    ~Set();

    QVariant operator[](const QString &key) const;

    QVariant operator[](const QString &key);

    QString filePath() const;

public slots:
    bool contains(const QString &key);

    QVariant value(const QString &key, const QVariant &defaultValue);

    QVariant value(const QString &key) const;

    void setValue(const QString &key, const QVariant &data);

    void save();

    void readySave(const int &delayTime = 1000);

    void read();

private:
    QString fileName_;
    QString groupName_;
    QString projectName_;
    QString filePath_;

    QMap< QString, QVariant > datas_;

    QSharedPointer< QTimer > timer_;
};

}

#endif//__JQSETTINGS_H__
