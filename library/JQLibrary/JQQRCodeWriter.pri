#
#   This file is part of JQLibrary
#
#   Library introduce: https://github.com/188080501/JQLibrary
#
#   Copyright: Jason
#
#   Contact email: Jason@JasonServer.com
#
#   GitHub: https://github.com/188080501/
#

INCLUDEPATH *= \
    $$PWD/include/JQQRCodeWriter/

# 定义JQQRCodeWriter的版本
JQQRCODEWRITER_VERSIONSTRING = 1.6

# 判断Qt版本，小于等于5.6就报错
!versionAtLeast( QT_VERSION, 5.7.0 ) {
    error( JQQRCodeWriter request minimum Qt version is 5.7.0 )
}

# 固定使用源码编译
JQQRCODEWRITER_COMPILE_MODE = SRC

equals(JQQRCODEWRITER_COMPILE_MODE,SRC) {

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

}

DEFINES *= JQQRCODEWRITER_COMPILE_MODE_STRING=\\\"$$JQQRCODEWRITER_COMPILE_MODE\\\"
DEFINES *= JQQRCODEWRITER_VERSIONSTRING=\\\"$$JQQRCODEWRITER_VERSIONSTRING\\\"
