#
#   This file is part of JQLibrary
#
#   Copyright: Jason
#
#   Contact email: 188080501@qq.com
#
#   GNU Lesser General Public License Usage
#   Alternatively, this file may be used under the terms of the GNU Lesser
#   General Public License version 2.1 or version 3 as published by the Free
#   Software Foundation and appearing in the file LICENSE.LGPLv21 and
#   LICENSE.LGPLv3 included in the packaging of this file. Please review the
#   following information to ensure the GNU Lesser General Public License
#   requirements will be met: https://www.gnu.org/licenses/lgpl.html and
#   http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
#

INCLUDEPATH *= \
    $$PWD/include/JQQRCodeWriter/

HEADERS *= \
    $$PWD/src/JQQRCodeWriter/qrencode/qrencode.h \
    $$PWD/src/JQQRCodeWriter/qrencode/bitstream.h \
    $$PWD/src/JQQRCodeWriter/qrencode/mask.h \
    $$PWD/src/JQQRCodeWriter/qrencode/mmask.h \
    $$PWD/src/JQQRCodeWriter/qrencode/mqrspec.h \
    $$PWD/src/JQQRCodeWriter/qrencode/qrencode_inner.h \
    $$PWD/src/JQQRCodeWriter/qrencode/qrinput.h \
    $$PWD/src/JQQRCodeWriter/qrencode/qrspec.h \
    $$PWD/src/JQQRCodeWriter/qrencode/rscode.h \
    $$PWD/src/JQQRCodeWriter/qrencode/split.h \
    $$PWD/src/JQQRCodeWriter/qrencode/config.h \
    $$PWD/include/JQQRCodeWriter/JQQRCodeWriter.h

SOURCES *= \
    $$PWD/src/JQQRCodeWriter/qrencode/qrencode.c \
    $$PWD/src/JQQRCodeWriter/qrencode/bitstream.c \
    $$PWD/src/JQQRCodeWriter/qrencode/mask.c \
    $$PWD/src/JQQRCodeWriter/qrencode/mmask.c \
    $$PWD/src/JQQRCodeWriter/qrencode/mqrspec.c \
    $$PWD/src/JQQRCodeWriter/qrencode/qrinput.c \
    $$PWD/src/JQQRCodeWriter/qrencode/qrspec.c \
    $$PWD/src/JQQRCodeWriter/qrencode/rscode.c \
    $$PWD/src/JQQRCodeWriter/qrencode/split.c \
    $$PWD/src/JQQRCodeWriter/JQQRCodeWriter.cpp
