#
#   This file is part of JQLibrary
#
#   Copyright: Jason and others
#
#   Contact email: 188080501@qq.com
#
#   Permission is hereby granted, free of charge, to any person obtaining
#   a copy of this software and associated documentation files (the
#   "Software"), to deal in the Software without restriction, including
#   without limitation the rights to use, copy, modify, merge, publish,
#   distribute, sublicense, and/or sell copies of the Software, and to
#   permit persons to whom the Software is furnished to do so, subject to
#   the following conditions:
#
#   The above copyright notice and this permission notice shall be
#   included in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
#   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

CONFIG *= c++11
CONFIG *= c++14

INCLUDEPATH *= \
    $$PWD/include/JQMbedTLS/ \
    $$PWD/include/JQMbedTLS/mbedtls/ \
    $$PWD/src/JQMbedTLS/mbedtls/

HEADERS *= \
    $$PWD/include/JQMbedTLS/JQMbedTLS.h

SOURCES *= \
    $$PWD/src/JQMbedTLS/JQMbedTLS.cpp \
    $$PWD/src/JQMbedTLS/mbedtls/aes.c \
    $$PWD/src/JQMbedTLS/mbedtls/asn1parse.c \
    $$PWD/src/JQMbedTLS/mbedtls/asn1write.c \
    $$PWD/src/JQMbedTLS/mbedtls/base64.c \
    $$PWD/src/JQMbedTLS/mbedtls/bignum.c \
    $$PWD/src/JQMbedTLS/mbedtls/constant_time.c \
    $$PWD/src/JQMbedTLS/mbedtls/ctr_drbg.c \
    $$PWD/src/JQMbedTLS/mbedtls/entropy.c \
    $$PWD/src/JQMbedTLS/mbedtls/md.c \
    $$PWD/src/JQMbedTLS/mbedtls/md5.c \
    $$PWD/src/JQMbedTLS/mbedtls/oid.c \
    $$PWD/src/JQMbedTLS/mbedtls/pem.c \
    $$PWD/src/JQMbedTLS/mbedtls/pk.c \
    $$PWD/src/JQMbedTLS/mbedtls/pkparse.c \
    $$PWD/src/JQMbedTLS/mbedtls/pkwrite.c \
    $$PWD/src/JQMbedTLS/mbedtls/pk_wrap.c \
    $$PWD/src/JQMbedTLS/mbedtls/platform.c \
    $$PWD/src/JQMbedTLS/mbedtls/platform_util.c \
    $$PWD/src/JQMbedTLS/mbedtls/rsa.c \
    $$PWD/src/JQMbedTLS/mbedtls/rsa_internal.c \
    $$PWD/src/JQMbedTLS/mbedtls/sha1.c \
    $$PWD/src/JQMbedTLS/mbedtls/sha256.c

!wasm {
    SOURCES *= \
        $$PWD/src/JQMbedTLS/mbedtls/entropy_poll.c
}

DEFINES *= MBEDTLS_CONFIG_FILE=\\\"mbedtls/mbedtls_config_jqmbedtls.h\\\"

wasm {
    DEFINES *= MBEDTLS_NO_PLATFORM_ENTROPY
}
