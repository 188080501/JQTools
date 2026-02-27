/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "aescrypt.h"

// C++ lib import
#include <cctype>
#include <cstring>

// Qt lib import
#include <QByteArray>
#include <QString>

// mbedtls import
#include "mbedtls/aes.h"
#include "mbedtls/md.h"

using namespace AesCrypt;

namespace
{

QString makeErrorString(
        const QString &action,
        const int errorCode
        )
{
    return QString("%1 失败，错误码: %2")
            .arg(action)
            .arg(errorCode);
}

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

bool isValidHexString(const QByteArray &hexString)
{
    for (const auto character: hexString) {
        if (!std::isxdigit(static_cast<unsigned char>(character))) {
            return false;
        }
    }

    return true;
}

QByteArray normalizeHex(const QString &hexString)
{
    auto data = hexString.toUtf8();
    data.replace("\r", "");
    data.replace("\n", "");
    data.replace("\t", "");
    data.replace(" ", "");
    return data;
}

bool tryDecodeHex(
        const QString &source,
        QByteArray &decodedData
        )
{
    const auto normalizedHex = normalizeHex(source);

    if (normalizedHex.isEmpty()) {
        decodedData.clear();
        return true;
    }

    if ((normalizedHex.size() % 2) != 0) {
        return false;
    }

    if (!isValidHexString(normalizedHex)) {
        return false;
    }

    decodedData = QByteArray::fromHex(normalizedHex);
    return true;
}

bool tryDecodeBinaryString(
        const QString &source,
        QByteArray &decodedData,
        QString &errorString
        )
{
    const auto trimmedSource = source.trimmed();

    if (trimmedSource.startsWith("hex:", Qt::CaseInsensitive)) {
        if (!tryDecodeHex(trimmedSource.mid(4), decodedData)) {
            errorString = QStringLiteral("十六进制格式无效");
            return false;
        }

        return true;
    }

    if (trimmedSource.startsWith("base64:", Qt::CaseInsensitive)) {
        if (!tryDecodeBase64(trimmedSource.mid(7), decodedData)) {
            errorString = QStringLiteral("Base64 格式无效");
            return false;
        }

        return true;
    }

    decodedData = trimmedSource.toUtf8();
    return true;
}

bool isAesKeyLengthValid(const int keyLength)
{
    return (keyLength == 16) || (keyLength == 24) || (keyLength == 32);
}

void xorBlock(
        const char *leftData,
        const char *rightData,
        char *outputData
        )
{
    for (auto index = 0; index < 16; ++index) {
        outputData[index] = static_cast<char>(
                    static_cast<unsigned char>(leftData[index]) ^
                    static_cast<unsigned char>(rightData[index])
                    );
    }
}

QByteArray makePaddedData(const QByteArray &plainData)
{
    auto data = plainData;
    auto paddingLength = 16 - (data.size() % 16);
    if (paddingLength == 0) {
        paddingLength = 16;
    }

    data.append(QByteArray(paddingLength, static_cast<char>(paddingLength)));
    return data;
}

bool removePadding(
        const QByteArray &decryptedData,
        QByteArray &plainData,
        QString &errorString
        )
{
    if (decryptedData.isEmpty()) {
        plainData.clear();
        return true;
    }

    const auto paddingLength = static_cast<unsigned char>(decryptedData.at(decryptedData.size() - 1));
    if ((paddingLength == 0) || (paddingLength > 16)) {
        errorString = QStringLiteral("填充数据无效");
        return false;
    }

    if (paddingLength > decryptedData.size()) {
        errorString = QStringLiteral("填充数据无效");
        return false;
    }

    for (auto index = 0; index < paddingLength; ++index) {
        if (static_cast<unsigned char>(decryptedData.at(decryptedData.size() - 1 - index)) != paddingLength) {
            errorString = QStringLiteral("填充数据无效");
            return false;
        }
    }

    plainData = decryptedData.left(decryptedData.size() - paddingLength);
    return true;
}

bool aesEncrypt(
        const QByteArray &plainData,
        const QByteArray &keyData,
        const QByteArray &ivData,
        QByteArray &encryptedData,
        QString &errorString
        )
{
    mbedtls_aes_context aesContext;
    mbedtls_aes_init(&aesContext);

    const auto returnCode = mbedtls_aes_setkey_enc(
                &aesContext,
                reinterpret_cast<const unsigned char *>(keyData.constData()),
                static_cast<unsigned int>(keyData.size() * 8)
                );
    if (returnCode != 0) {
        errorString = makeErrorString("aes_setkey_enc", returnCode);
        mbedtls_aes_free(&aesContext);
        return false;
    }

    const auto paddedData = makePaddedData(plainData);

    encryptedData = QByteArray(paddedData.size(), '\0');

    auto previousBlock = ivData;
    auto mixedBlock = QByteArray(16, '\0');

    for (auto offset = 0; offset < paddedData.size(); offset += 16) {
        xorBlock(
                    paddedData.constData() + offset,
                    previousBlock.constData(),
                    mixedBlock.data()
                    );

        const auto cryptReturnCode = mbedtls_aes_crypt_ecb(
                    &aesContext,
                    MBEDTLS_AES_ENCRYPT,
                    reinterpret_cast<const unsigned char *>(mixedBlock.constData()),
                    reinterpret_cast<unsigned char *>(encryptedData.data() + offset)
                    );
        if (cryptReturnCode != 0) {
            errorString = makeErrorString("aes_crypt_ecb_encrypt", cryptReturnCode);
            mbedtls_aes_free(&aesContext);
            return false;
        }

        memcpy(previousBlock.data(), encryptedData.constData() + offset, 16);
    }

    mbedtls_aes_free(&aesContext);
    return true;
}

bool aesDecrypt(
        const QByteArray &encryptedData,
        const QByteArray &keyData,
        const QByteArray &ivData,
        QByteArray &plainData,
        QString &errorString
        )
{
    if ((encryptedData.size() % 16) != 0) {
        errorString = QStringLiteral("密文长度无效");
        return false;
    }

    mbedtls_aes_context aesContext;
    mbedtls_aes_init(&aesContext);

    const auto returnCode = mbedtls_aes_setkey_dec(
                &aesContext,
                reinterpret_cast<const unsigned char *>(keyData.constData()),
                static_cast<unsigned int>(keyData.size() * 8)
                );
    if (returnCode != 0) {
        errorString = makeErrorString("aes_setkey_dec", returnCode);
        mbedtls_aes_free(&aesContext);
        return false;
    }

    auto decryptedData = QByteArray(encryptedData.size(), '\0');
    auto decryptedBlock = QByteArray(16, '\0');
    auto previousBlock = ivData;

    for (auto offset = 0; offset < encryptedData.size(); offset += 16) {
        const auto cryptReturnCode = mbedtls_aes_crypt_ecb(
                    &aesContext,
                    MBEDTLS_AES_DECRYPT,
                    reinterpret_cast<const unsigned char *>(encryptedData.constData() + offset),
                    reinterpret_cast<unsigned char *>(decryptedBlock.data())
                    );
        if (cryptReturnCode != 0) {
            errorString = makeErrorString("aes_crypt_ecb_decrypt", cryptReturnCode);
            mbedtls_aes_free(&aesContext);
            return false;
        }

        xorBlock(
                    decryptedBlock.constData(),
                    previousBlock.constData(),
                    decryptedData.data() + offset
                    );

        memcpy(previousBlock.data(), encryptedData.constData() + offset, 16);
    }

    mbedtls_aes_free(&aesContext);
    return removePadding(decryptedData, plainData, errorString);
}

bool calculateHmacSha256(
        const QByteArray &sourceData,
        const QByteArray &keyData,
        QByteArray &hmacValue,
        QString &errorString
        )
{
    const auto mdInfo = mbedtls_md_info_from_type(MBEDTLS_MD_SHA256);
    if (mdInfo == nullptr) {
        errorString = QStringLiteral("HMAC 算法初始化失败");
        return false;
    }

    auto output = QByteArray(32, '\0');
    const auto returnCode = mbedtls_md_hmac(
                mdInfo,
                reinterpret_cast<const unsigned char *>(keyData.constData()),
                static_cast<size_t>(keyData.size()),
                reinterpret_cast<const unsigned char *>(sourceData.constData()),
                static_cast<size_t>(sourceData.size()),
                reinterpret_cast<unsigned char *>(output.data())
                );
    if (returnCode != 0) {
        errorString = makeErrorString("md_hmac", returnCode);
        return false;
    }

    hmacValue = output;
    return true;
}

bool checkKeyAndIv(
        const QString &keyText,
        const QString &ivText,
        QByteArray &keyData,
        QByteArray &ivData,
        QString &errorString
        )
{
    if (!tryDecodeBinaryString(keyText, keyData, errorString)) {
        return false;
    }

    if (!isAesKeyLengthValid(keyData.size())) {
        errorString = QStringLiteral("密钥长度必须为 16/24/32 字节");
        return false;
    }

    if (!tryDecodeBinaryString(ivText, ivData, errorString)) {
        return false;
    }

    if (ivData.size() != 16) {
        errorString = QStringLiteral("IV 长度必须为 16 字节");
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

void Manage::setKey(const QString &string)
{
    key_ = string;
    emit keyChanged();
}

void Manage::setIv(const QString &string)
{
    iv_ = string;
    emit ivChanged();
}

void Manage::clear()
{
    source_.clear();
    target_.clear();
    key_.clear();
    iv_.clear();
    errorString_.clear();

    emit sourceChanged();
    emit targetChanged();
    emit keyChanged();
    emit ivChanged();
    emit errorStringChanged();
}

void Manage::pasteSource()
{
    source_ = this->clipboardText();
    emit sourceChanged();
}

void Manage::pasteKey()
{
    key_ = this->clipboardText();
    emit keyChanged();
}

void Manage::pasteIv()
{
    iv_ = this->clipboardText();
    emit ivChanged();
}

void Manage::copyTarget()
{
    this->setClipboardText(target_);
}

void Manage::copyKey()
{
    this->setClipboardText(key_);
}

void Manage::copyIv()
{
    this->setClipboardText(iv_);
}

void Manage::moveTargetToSource()
{
    source_ = target_;
    target_.clear();

    emit sourceChanged();
    emit targetChanged();
}

void Manage::encryptToBase64()
{
    QByteArray keyData;
    QByteArray ivData;
    if (!checkKeyAndIv(key_, iv_, keyData, ivData, errorString_)) {
        emit errorStringChanged();
        return;
    }

    QByteArray encryptedData;
    if (!aesEncrypt(source_.toUtf8(), keyData, ivData, encryptedData, errorString_)) {
        emit errorStringChanged();
        return;
    }

    target_ = encryptedData.toBase64();
    errorString_.clear();

    emit targetChanged();
    emit errorStringChanged();
}

void Manage::decryptFromBase64()
{
    QByteArray keyData;
    QByteArray ivData;
    if (!checkKeyAndIv(key_, iv_, keyData, ivData, errorString_)) {
        emit errorStringChanged();
        return;
    }

    if (source_.trimmed().isEmpty()) {
        target_.clear();
        errorString_.clear();
        emit targetChanged();
        emit errorStringChanged();
        return;
    }

    QByteArray encryptedData;
    if (!tryDecodeBase64(source_, encryptedData)) {
        errorString_ = QStringLiteral("Base64 密文格式无效");
        emit errorStringChanged();
        return;
    }

    QByteArray plainData;
    if (!aesDecrypt(encryptedData, keyData, ivData, plainData, errorString_)) {
        emit errorStringChanged();
        return;
    }

    target_ = QString::fromUtf8(plainData.constData(), plainData.size());
    errorString_.clear();

    emit targetChanged();
    emit errorStringChanged();
}

void Manage::calculateHmacSha256ToHex()
{
    QByteArray keyData;
    QString decodeErrorString;
    if (!tryDecodeBinaryString(key_, keyData, decodeErrorString)) {
        errorString_ = decodeErrorString;
        emit errorStringChanged();
        return;
    }

    if (keyData.isEmpty()) {
        errorString_ = QStringLiteral("密钥不能为空");
        emit errorStringChanged();
        return;
    }

    QByteArray hmacValue;
    if (!calculateHmacSha256(source_.toUtf8(), keyData, hmacValue, errorString_)) {
        emit errorStringChanged();
        return;
    }

    target_ = hmacValue.toHex();
    errorString_.clear();

    emit targetChanged();
    emit errorStringChanged();
}
