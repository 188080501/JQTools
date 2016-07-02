#ifndef __IconMaker_h__
#define __IconMaker_h__

// Qt lib import
#include <QImage>

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define ICONMAKER_INITIALIZA                                                     \
{                                                                               \
    qmlRegisterType<IconMaker::Manage>("IconMaker", 1, 0, "IconMakerManage");   \
}

namespace IconMaker
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage();

    ~Manage() = default;

public slots:
    inline QString targetSavePath() const { return targetSavePath_; }

    inline QString sourceIconFilePath() const { return sourceIconFilePath_; }

    inline int sourceIconImageWidht() const { return sourceIconImage_.width(); }

    inline int sourceIconImageHeight() const { return sourceIconImage_.height(); }

    QString chooseTargetSavePath();

    QString choostSourceIconFilePath();

    QString makeAll();

    QString makeOSX();

    QString makeIOS();

    QString makeWindows();

    QString makeWP();

    QString makeAndroid();

private:
    void realMakeOSX();

    void realMakeIOS();

    void realMakeWindows();

    void realMakeWP();

    void realMakeAndroid();

    void saveToIco(const QString &targetFilePath, const QSize &size);

    void saveToPng(const QString &targetFilePath, const QSize &size);

    void saveToEmptyPng(const QString &targetFilePath, const QSize &size);

    void saveToJpg(const QString &targetFilePath, const QSize &size);

signals:
    void targetSavePathChanged();

    void sourceIconFilePathChanged();

private:
    QString targetSavePath_;
    QString sourceIconFilePath_;

    QImage sourceIconImage_;
};

}

#endif//__IconMaker_h__
