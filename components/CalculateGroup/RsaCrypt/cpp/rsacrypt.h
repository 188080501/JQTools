/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_CALCULATEGROUP_RSACRYPT_CPP_RSACRYPT_H_
#define GROUP_CALCULATEGROUP_RSACRYPT_CPP_RSACRYPT_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

// JQLibrary import
#include <JQMbedTLS.h>

#define RSACRYPT_INITIALIZA                                                         \
{                                                                                   \
    qmlRegisterType<RsaCrypt::Manage>("RsaCrypt", 1, 0, "RsaCryptManage");         \
}

namespace RsaCrypt
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

    inline QString keyPem() const { return keyPem_; }

    inline QString errorString() const { return errorString_; }

public slots:
    void setSource(const QString &string);

    void setKeyPem(const QString &string);

    void clear();

    void pasteSource();

    void pasteKeyPem();

    void copyTarget();

    void copyKeyPem();

    void moveTargetToSource();

    void publicKeyEncryptToBase64();

    void privateKeyDecryptFromBase64();

signals:
    void sourceChanged();

    void targetChanged();

    void keyPemChanged();

    void errorStringChanged();

private:
    QString source_;
    QString target_;
    QString keyPem_;
    QString errorString_;
};

}

#endif//GROUP_CALCULATEGROUP_RSACRYPT_CPP_RSACRYPT_H_
