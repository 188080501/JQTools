#include "JQMbedTLS.h"

// C++ lib import
#include <cstring>
#include <limits>

// Qt lib import
#include <QtGlobal>

// mbedtls import
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "mbedtls/pk.h"
#include "mbedtls/rsa.h"

namespace
{

struct CtrDrbgContext
{
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctrDrbg;
};

QString makeErrorString(
        const QString &action,
        const int errorCode
        )
{
    return QString("%1 failed, error code: %2")
            .arg(action)
            .arg(errorCode);
}

int initCtrDrbg(CtrDrbgContext &context)
{
    mbedtls_entropy_init(&context.entropy);
    mbedtls_ctr_drbg_init(&context.ctrDrbg);

    static const char *personalization = "JQMbedTLS";

    return mbedtls_ctr_drbg_seed(
                &context.ctrDrbg,
                mbedtls_entropy_func,
                &context.entropy,
                reinterpret_cast<const unsigned char *>(personalization),
                strlen(personalization)
                );
}

void freeCtrDrbg(CtrDrbgContext &context)
{
    mbedtls_ctr_drbg_free(&context.ctrDrbg);
    mbedtls_entropy_free(&context.entropy);
}

QByteArray makePemBytes(const QString &pem)
{
    auto pemBytes = pem.toUtf8();

    if (pemBytes.isEmpty() || (pemBytes.at(pemBytes.size() - 1) != '\0')) {
        pemBytes.append('\0');
    }

    return pemBytes;
}

bool isRsaKey(const mbedtls_pk_context &keyContext)
{
    const auto keyType = mbedtls_pk_get_type(&keyContext);
    return (keyType == MBEDTLS_PK_RSA) || (keyType == MBEDTLS_PK_RSASSA_PSS);
}

int parsePublicKeyPem(
        const QString &publicKeyPem,
        mbedtls_pk_context &publicKeyContext
        )
{
    const auto publicKeyBytes = makePemBytes(publicKeyPem);

    return mbedtls_pk_parse_public_key(
                &publicKeyContext,
                reinterpret_cast<const unsigned char *>(publicKeyBytes.constData()),
                static_cast<size_t>(publicKeyBytes.size())
                );
}

int parsePrivateKeyPem(
        const QString &privateKeyPem,
        mbedtls_pk_context &privateKeyContext
        )
{
    const auto privateKeyBytes = makePemBytes(privateKeyPem);

    return mbedtls_pk_parse_key(
                &privateKeyContext,
                reinterpret_cast<const unsigned char *>(privateKeyBytes.constData()),
                static_cast<size_t>(privateKeyBytes.size()),
                nullptr,
                0
                );
}

}

JQMbedTLS::RsaKeyPairResult JQMbedTLS::generateRsaKeyPair(
        int keyBits,
        int exponent
        )
{
    RsaKeyPairResult result;

    if (keyBits < 1024) {
        result.errorString = "invalid keyBits";
        return result;
    }

    if ((exponent < 3) || ((exponent % 2) == 0)) {
        result.errorString = "invalid exponent";
        return result;
    }

    CtrDrbgContext randomContext;
    auto returnCode = initCtrDrbg(randomContext);
    if (returnCode != 0) {
        result.errorString = makeErrorString("ctr_drbg_seed", returnCode);
        return result;
    }

    mbedtls_pk_context keyContext;
    mbedtls_pk_init(&keyContext);

    returnCode = mbedtls_pk_setup(
                &keyContext,
                mbedtls_pk_info_from_type(MBEDTLS_PK_RSA)
                );
    if (returnCode != 0) {
        result.errorString = makeErrorString("pk_setup", returnCode);
        mbedtls_pk_free(&keyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    returnCode = mbedtls_rsa_gen_key(
                mbedtls_pk_rsa(keyContext),
                mbedtls_ctr_drbg_random,
                &randomContext.ctrDrbg,
                static_cast<unsigned int>(keyBits),
                exponent
                );
    if (returnCode != 0) {
        result.errorString = makeErrorString("rsa_gen_key", returnCode);
        mbedtls_pk_free(&keyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    auto publicKeyPemBuffer = QByteArray(32 * 1024, '\0');
    returnCode = mbedtls_pk_write_pubkey_pem(
                &keyContext,
                reinterpret_cast<unsigned char *>(publicKeyPemBuffer.data()),
                static_cast<size_t>(publicKeyPemBuffer.size())
                );
    if (returnCode != 0) {
        result.errorString = makeErrorString("write_pubkey_pem", returnCode);
        mbedtls_pk_free(&keyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    auto privateKeyPemBuffer = QByteArray(32 * 1024, '\0');
    returnCode = mbedtls_pk_write_key_pem(
                &keyContext,
                reinterpret_cast<unsigned char *>(privateKeyPemBuffer.data()),
                static_cast<size_t>(privateKeyPemBuffer.size())
                );
    if (returnCode != 0) {
        result.errorString = makeErrorString("write_key_pem", returnCode);
        mbedtls_pk_free(&keyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    result.publicKeyPem = QString::fromUtf8(publicKeyPemBuffer.constData());
    result.privateKeyPem = QString::fromUtf8(privateKeyPemBuffer.constData());
    result.generateSucceed = true;

    mbedtls_pk_free(&keyContext);
    freeCtrDrbg(randomContext);

    return result;
}

JQMbedTLS::RsaCryptoResult JQMbedTLS::publicKeyEncrypt(
        const QByteArray &plainData,
        const QString &publicKeyPem
        )
{
    RsaCryptoResult result;

    if (plainData.isEmpty()) {
        result.processSucceed = true;
        return result;
    }

    CtrDrbgContext randomContext;
    auto returnCode = initCtrDrbg(randomContext);
    if (returnCode != 0) {
        result.errorString = makeErrorString("ctr_drbg_seed", returnCode);
        return result;
    }

    mbedtls_pk_context publicKeyContext;
    mbedtls_pk_init(&publicKeyContext);

    returnCode = parsePublicKeyPem(publicKeyPem, publicKeyContext);
    if (returnCode != 0) {
        result.errorString = makeErrorString("parse_public_key", returnCode);
        mbedtls_pk_free(&publicKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    if (!isRsaKey(publicKeyContext)) {
        result.errorString = "key is not RSA";
        mbedtls_pk_free(&publicKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    const auto keyLength = static_cast<int>(mbedtls_pk_get_len(&publicKeyContext));
    if (keyLength <= 11) {
        result.errorString = "invalid RSA key length";
        mbedtls_pk_free(&publicKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    const auto chunkLength = keyLength - 11;
    QByteArray encryptedData;
    encryptedData.reserve((plainData.size() / chunkLength + 1) * keyLength);

    auto offset = 0;
    while (offset < plainData.size()) {
        const auto remainLength = plainData.size() - offset;
        const auto plainChunkLength = qMin(chunkLength, remainLength);

        auto encryptedChunk = QByteArray(keyLength, '\0');
        size_t encryptedChunkLength = 0;

        returnCode = mbedtls_pk_encrypt(
                    &publicKeyContext,
                    reinterpret_cast<const unsigned char *>(plainData.constData() + offset),
                    static_cast<size_t>(plainChunkLength),
                    reinterpret_cast<unsigned char *>(encryptedChunk.data()),
                    &encryptedChunkLength,
                    static_cast<size_t>(encryptedChunk.size()),
                    mbedtls_ctr_drbg_random,
                    &randomContext.ctrDrbg
                    );
        if (returnCode != 0) {
            result.errorString = makeErrorString("pk_encrypt", returnCode);
            mbedtls_pk_free(&publicKeyContext);
            freeCtrDrbg(randomContext);
            return result;
        }

        if (encryptedChunkLength > static_cast<size_t>(std::numeric_limits<int>::max())) {
            result.errorString = "encrypted chunk is too large";
            mbedtls_pk_free(&publicKeyContext);
            freeCtrDrbg(randomContext);
            return result;
        }

        encryptedData.append(encryptedChunk.constData(), static_cast<int>(encryptedChunkLength));
        offset += plainChunkLength;
    }

    result.data = encryptedData;
    result.processSucceed = true;

    mbedtls_pk_free(&publicKeyContext);
    freeCtrDrbg(randomContext);

    return result;
}

JQMbedTLS::RsaCryptoResult JQMbedTLS::privateKeyDecrypt(
        const QByteArray &cipherData,
        const QString &privateKeyPem
        )
{
    RsaCryptoResult result;

    if (cipherData.isEmpty()) {
        result.processSucceed = true;
        return result;
    }

    CtrDrbgContext randomContext;
    auto returnCode = initCtrDrbg(randomContext);
    if (returnCode != 0) {
        result.errorString = makeErrorString("ctr_drbg_seed", returnCode);
        return result;
    }

    mbedtls_pk_context privateKeyContext;
    mbedtls_pk_init(&privateKeyContext);

    returnCode = parsePrivateKeyPem(privateKeyPem, privateKeyContext);
    if (returnCode != 0) {
        result.errorString = makeErrorString("parse_private_key", returnCode);
        mbedtls_pk_free(&privateKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    if (!isRsaKey(privateKeyContext)) {
        result.errorString = "key is not RSA";
        mbedtls_pk_free(&privateKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    const auto keyLength = static_cast<int>(mbedtls_pk_get_len(&privateKeyContext));
    if ((keyLength <= 0) || ((cipherData.size() % keyLength) != 0)) {
        result.errorString = "cipherData size is invalid for RSA key";
        mbedtls_pk_free(&privateKeyContext);
        freeCtrDrbg(randomContext);
        return result;
    }

    QByteArray decryptedData;
    decryptedData.reserve(cipherData.size());

    auto offset = 0;
    while (offset < cipherData.size()) {
        auto plainChunk = QByteArray(keyLength, '\0');
        size_t plainChunkLength = 0;

        returnCode = mbedtls_pk_decrypt(
                    &privateKeyContext,
                    reinterpret_cast<const unsigned char *>(cipherData.constData() + offset),
                    static_cast<size_t>(keyLength),
                    reinterpret_cast<unsigned char *>(plainChunk.data()),
                    &plainChunkLength,
                    static_cast<size_t>(plainChunk.size()),
                    mbedtls_ctr_drbg_random,
                    &randomContext.ctrDrbg
                    );
        if (returnCode != 0) {
            result.errorString = makeErrorString("pk_decrypt", returnCode);
            mbedtls_pk_free(&privateKeyContext);
            freeCtrDrbg(randomContext);
            return result;
        }

        if (plainChunkLength > static_cast<size_t>(std::numeric_limits<int>::max())) {
            result.errorString = "decrypted chunk is too large";
            mbedtls_pk_free(&privateKeyContext);
            freeCtrDrbg(randomContext);
            return result;
        }

        decryptedData.append(plainChunk.constData(), static_cast<int>(plainChunkLength));
        offset += keyLength;
    }

    result.data = decryptedData;
    result.processSucceed = true;

    mbedtls_pk_free(&privateKeyContext);
    freeCtrDrbg(randomContext);

    return result;
}
