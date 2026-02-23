/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_IMAGEGROUP_ICONMAKER_CPP_ICONMAKER_H_
#define GROUP_IMAGEGROUP_ICONMAKER_CPP_ICONMAKER_H_

// Qt lib import
#include <QImage>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define ICONMAKER_INITIALIZA                                                    \
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

    inline int sourceIconImageWidth() const { return sourceIconImage_.width(); }

    inline int sourceIconImageHeight() const { return sourceIconImage_.height(); }

    QString chooseTargetSavePath();

    QString chooseSourceIconFilePath();

    QString makeAll();

    QString makeOSX();

    QString makeIOS();

    QString makeWindows();

    QString makeAndroid();

    QString makePWA();

private:
    void generateOSXIconAssets();

    void generateIOSIconAssets();

    void generateWindowsIconAsset();

    void generateAndroidIconAssets();

    void generatePWAIconAssets();

    void saveToPng(const QString &targetFilePath, const QSize &size);

signals:
    void targetSavePathChanged();

    void sourceIconFilePathChanged();

private:
    QString targetSavePath_;
    QString sourceIconFilePath_;

    QImage sourceIconImage_;
};

}

#endif//GROUP_IMAGEGROUP_ICONMAKER_CPP_ICONMAKER_H_
