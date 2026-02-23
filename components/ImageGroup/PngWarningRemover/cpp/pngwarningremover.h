/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_IMAGEGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H_
#define GROUP_IMAGEGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H_

// Qt lib import
#include <QStringList>

// JQToolsLibrary import
#include <JQToolsLibrary>

#define PNGWARNINGREMOVER_INITIALIZA                                                                     \
{                                                                                                       \
    qmlRegisterType<PngWarningRemover::Manage>("PngWarningRemover", 1, 0, "PngWarningRemoverManage");   \
}

namespace PngWarningRemover
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    QString convertPng();

    QString convertPngByOpenDirectory();

    inline QString lastErrorFileName() { return lastErrorFileName_; }

private:
    QString convertPng(const QStringList &filePaths);

    QString lastErrorFileName_;
};

}

#endif//GROUP_IMAGEGROUP_PNGWARNINGREMOVER_CPP_PNGWARNINGREMOVER_H_
