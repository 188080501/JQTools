/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "rsakeygenerate.h"

// Qt lib import
#include <QString>

using namespace RsaKeyGenerate;

void Manage::generate(const QString &keyBitsString)
{
    auto targetKeyBitsString = keyBitsString.trimmed();
    if (targetKeyBitsString.isEmpty()) {
        targetKeyBitsString = "2048";
    }

    bool stringToIntSucceed = false;
    const auto keyBits = targetKeyBitsString.toInt(&stringToIntSucceed);

    if (!stringToIntSucceed) {
        errorString_ = "invalid key bits";
        emit errorStringChanged();
        return;
    }

    const auto result = JQMbedTLS::generateRsaKeyPair(keyBits, 65537);

    publicKeyPem_ = result.publicKeyPem;
    privateKeyPem_ = result.privateKeyPem;
    errorString_ = result.errorString;

    emit publicKeyPemChanged();
    emit privateKeyPemChanged();
    emit errorStringChanged();
}

void Manage::clear()
{
    publicKeyPem_.clear();
    privateKeyPem_.clear();
    errorString_.clear();

    emit publicKeyPemChanged();
    emit privateKeyPemChanged();
    emit errorStringChanged();
}

void Manage::copyPublicKeyPem()
{
    this->setClipboardText(publicKeyPem_);
}

void Manage::copyPrivateKeyPem()
{
    this->setClipboardText(privateKeyPem_);
}
