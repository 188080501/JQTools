#ifndef __GROUP_CALCULATE_HASHCALCULATE_CPP_HASHCALCULATE_H__
#define __GROUP_CALCULATE_HASHCALCULATE_CPP_HASHCALCULATE_H__

// JQToolsLibrary import
#include "JQToolsLibrary.h"

#define HASHCALCULATE_INITIALIZA                                                            \
{                                                                                           \
    qmlRegisterType<HashCalculate::Manage>("HashCalculate", 1, 0, "HashCalculateManage");   \
}

namespace HashCalculate
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    inline QString source() const { return source_; }

    inline QString target() const { return target_; }

public slots:
    void setSource(const QString &string);

    void resetSource();

    void resetTarget();

    void pause();

    void clear();

    void copy();

    void cut();

    void calculateToBase64();

    void calculateFromBase64();

    void calculateMD4();

    void calculateMD5();

    void calculateSha1();

    void calculateSha224();

    void calculateSha256();

    void calculateSha384();

    void calculateSha512();

    void calculateSha3_224();

    void calculateSha3_256();

    void calculateSha3_384();

    void calculateSha3_512();

signals:
    void sourceChanged();

    void targetChanged();

private:
    QString source_;
    QString target_;
};

}

#endif//__GROUP_CALCULATE_HASHCALCULATE_CPP_HASHCALCULATE_H__
