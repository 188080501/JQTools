/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "rsacrypt.h"

// Qt lib import
#include <QByteArray>
#include <QString>

using namespace RsaCrypt;

namespace
{

QByteArray normalizeBase64(const QString &source)
{
    auto result = source.toUtf8();
    result.replace("\r", "");
    result.replace("\n", "");
    result.replace("\t", "");
    result.replace(" ", "");
    return result;
}

bool tryDecodeBase64(
        const QString &source,
        QByteArray &decodedData
        )
{
    auto normalizedData = normalizeBase64(source);

    if (normalizedData.isEmpty()) {
        decodedData.clear();
        return true;
    }

    while ((normalizedData.size() % 4) != 0) {
        normalizedData.append('=');
    }

    decodedData = QByteArray::fromBase64(normalizedData);

    if (decodedData.isEmpty()) {
        return false;
    }

    return true;
}

}

void Manage::setSource(const QString &string)
{
    source_ = string;
    emit sourceChanged();
}

void Manage::setKeyPem(const QString &string)
{
    keyPem_ = string;
    emit keyPemChanged();
}

void Manage::clear()
{
    source_.clear();
    target_.clear();
    keyPem_.clear();
    errorString_.clear();

    emit sourceChanged();
    emit targetChanged();
    emit keyPemChanged();
    emit errorStringChanged();
}

void Manage::pasteSource()
{
    source_ = this->clipboardText();
    emit sourceChanged();
}

void Manage::pasteKeyPem()
{
    keyPem_ = this->clipboardText();
    emit keyPemChanged();
}

void Manage::copyTarget()
{
    this->setClipboardText(target_);
}

void Manage::copyKeyPem()
{
    this->setClipboardText(keyPem_);
}

void Manage::moveTargetToSource()
{
    source_ = target_;
    target_.clear();
    emit sourceChanged();
    emit targetChanged();
}

void Manage::publicKeyEncryptToBase64()
{
    if (keyPem_.trimmed().isEmpty()) {
        errorString_ = "key pem is empty";
        emit errorStringChanged();
        return;
    }

    const auto result = JQMbedTLS::publicKeyEncrypt(source_.toUtf8(), keyPem_);
    if (!result.processSucceed) {
        errorString_ = result.errorString;
        emit errorStringChanged();
        return;
    }

    target_ = result.data.toBase64();
    errorString_.clear();

    emit targetChanged();
    emit errorStringChanged();
}

void Manage::privateKeyDecryptFromBase64()
{
    if (keyPem_.trimmed().isEmpty()) {
        errorString_ = "key pem is empty";
        emit errorStringChanged();
        return;
    }

    QByteArray cipherData;
    if (!tryDecodeBase64(source_, cipherData)) {
        errorString_ = "invalid base64 cipher text";
        emit errorStringChanged();
        return;
    }

    const auto result = JQMbedTLS::privateKeyDecrypt(cipherData, keyPem_);
    if (!result.processSucceed) {
        errorString_ = result.errorString;
        emit errorStringChanged();
        return;
    }

    target_ = QString::fromUtf8(result.data.constData(), result.data.size());
    errorString_.clear();

    emit targetChanged();
    emit errorStringChanged();
}
