/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_CALCULATEGROUP_RSAKEYGENERATE_CPP_RSAKEYGENERATE_H_
#define GROUP_CALCULATEGROUP_RSAKEYGENERATE_CPP_RSAKEYGENERATE_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

// JQLibrary import
#include <JQMbedTLS.h>

#define RSAKEYGENERATE_INITIALIZA                                                                      \
{                                                                                                      \
    qmlRegisterType<RsaKeyGenerate::Manage>("RsaKeyGenerate", 1, 0, "RsaKeyGenerateManage");         \
}

namespace RsaKeyGenerate
{

class Manage: public AbstractTool
{
    Q_OBJECT
    Q_DISABLE_COPY(Manage)

public:
    Manage() = default;

    ~Manage() = default;

public slots:
    inline QString publicKeyPem() const { return publicKeyPem_; }

    inline QString privateKeyPem() const { return privateKeyPem_; }

    inline QString errorString() const { return errorString_; }

public slots:
    void generate(const QString &keyBitsString);

    void clear();

    void copyPublicKeyPem();

    void copyPrivateKeyPem();

signals:
    void publicKeyPemChanged();

    void privateKeyPemChanged();

    void errorStringChanged();

private:
    QString publicKeyPem_;
    QString privateKeyPem_;
    QString errorString_;
};

}

#endif//GROUP_CALCULATEGROUP_RSAKEYGENERATE_CPP_RSAKEYGENERATE_H_
