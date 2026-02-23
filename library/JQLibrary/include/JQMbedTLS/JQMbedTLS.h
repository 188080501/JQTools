/*
    This file is part of JQLibrary

    Copyright: Jason and others

    Contact email: 188080501@qq.com

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
    LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
    OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef JQMBEDTLS_H_
#define JQMBEDTLS_H_

// Qt lib import
#include <QByteArray>
#include <QString>

namespace JQMbedTLS
{

struct RsaKeyPairResult
{
    bool generateSucceed = false;
    QString publicKeyPem;
    QString privateKeyPem;
    QString errorString;
};

struct RsaCryptoResult
{
    bool processSucceed = false;
    QByteArray data;
    QString errorString;
};

RsaKeyPairResult generateRsaKeyPair(
        int keyBits = 2048,
        int exponent = 65537
        );

RsaCryptoResult publicKeyEncrypt(
        const QByteArray &plainData,
        const QString &publicKeyPem
        );

RsaCryptoResult privateKeyDecrypt(
        const QByteArray &cipherData,
        const QString &privateKeyPem
        );

}

#endif//JQMBEDTLS_H_
