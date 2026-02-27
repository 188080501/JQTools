/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_CALCULATEGROUP_FILEHASHCALCULATE_CPP_FILEHASHCALCULATE_H_
#define GROUP_CALCULATEGROUP_FILEHASHCALCULATE_CPP_FILEHASHCALCULATE_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define FILEHASHCALCULATE_INITIALIZA                                                                \
{                                                                                                   \
    qmlRegisterType<FileHashCalculate::Manage>("FileHashCalculate", 1, 0, "FileHashCalculateManage"); \
}

namespace FileHashCalculate
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    inline QString filePath() const { return filePath_; }

    inline QString md5Value() const { return md5Value_; }

    inline QString sha1Value() const { return sha1Value_; }

    inline QString sha256Value() const { return sha256Value_; }

public slots:
    void chooseFile();

    QString calculate();

    void clear();

    void copyMd5();

    void copySha1();

    void copySha256();

signals:
    void filePathChanged();

    void md5ValueChanged();

    void sha1ValueChanged();

    void sha256ValueChanged();

private:
    QString filePath_;
    QString md5Value_;
    QString sha1Value_;
    QString sha256Value_;
};

}

#endif//GROUP_CALCULATEGROUP_FILEHASHCALCULATE_CPP_FILEHASHCALCULATE_H_
