/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_CALCULATEGROUP_AESCRYPT_CPP_AESCRYPT_H_
#define GROUP_CALCULATEGROUP_AESCRYPT_CPP_AESCRYPT_H_

// JQToolsLibrary import
#include <JQToolsLibrary>

#define AESCRYPT_INITIALIZA                                                       \
{                                                                                 \
    qmlRegisterType<AesCrypt::Manage>("AesCrypt", 1, 0, "AesCryptManage");       \
}

namespace AesCrypt
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

    inline QString key() const { return key_; }

    inline QString iv() const { return iv_; }

    inline QString errorString() const { return errorString_; }

public slots:
    void setSource(const QString &string);

    void setKey(const QString &string);

    void setIv(const QString &string);

    void clear();

    void pasteSource();

    void pasteKey();

    void pasteIv();

    void copyTarget();

    void copyKey();

    void copyIv();

    void moveTargetToSource();

    void encryptToBase64();

    void decryptFromBase64();

    void calculateHmacSha256ToHex();

signals:
    void sourceChanged();

    void targetChanged();

    void keyChanged();

    void ivChanged();

    void errorStringChanged();

private:
    QString source_;
    QString target_;
    QString key_;
    QString iv_;
    QString errorString_;
};

}

#endif//GROUP_CALCULATEGROUP_AESCRYPT_CPP_AESCRYPT_H_
