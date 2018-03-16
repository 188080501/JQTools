/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_TOOLSGROUP_WEBPMAKER_CPP_WEBPMAKER_H_
#define GROUP_TOOLSGROUP_WEBPMAKER_CPP_WEBPMAKER_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define WEBPMAKER_INITIALIZA                                                    \
{                                                                               \
    qmlRegisterType<WebPMaker::Manage>("WebPMaker", 1, 0, "WebPMakerManage");   \
}

namespace WebPMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString makeWebPByFilePaths(const bool &coverOldFile, const QJsonArray &filePaths);

    QString makeWebPByOpenFiles(const bool &coverOldFile);

    QString makeWebPByOpenDirectory(const bool &coverOldFile);

    void startMake(const QString &currentFilePath);

    QString urlToLocalPngFilePath(const QVariant &url);

private:
    QString makeWebP(const bool &coverOldFile, const QStringList &filePaths);

signals:
    void makeStart(const QJsonArray fileList);

    void makeWebPStart(const QString currentFilePath);

    void makeWebPFinish(const QString currentFilePath, const QJsonObject makeResult);

    void makeEnd();

private:
    QMap< QString, std::function< void() > > waitMakeQueue_; // fileName -> package
};

}

#endif//GROUP_TOOLSGROUP_WEBPMAKER_CPP_WEBPMAKER_H_
