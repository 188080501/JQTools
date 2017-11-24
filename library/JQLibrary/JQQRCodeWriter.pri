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
lessThan( QT_MAJOR_VERSION, 5 ) | lessThan( QT_MINOR_VERSION, 7 ) {
    error( JQQRCodeWriter request minimum Qt version is 5.7.0 )
}

# 准备bin库目录
JQQRCODEWRITER_BIN_NO1_DIR = JQQRCodeWriter$$JQQRCODEWRITER_VERSIONSTRING/Qt$$[QT_VERSION]
JQQRCODEWRITER_BIN_NO2_DIR = $$QT_ARCH
JQQRCODEWRITER_BIN_NO3_DIR = $$[QMAKE_XSPEC]
JQQRCODEWRITER_BIN_NO3_DIR ~= s/g\+\+/gcc

# 根据编译参数，追加static名称
contains( CONFIG, static ) {
    JQQRCODEWRITER_BIN_NO3_DIR = $$JQQRCODEWRITER_BIN_NO3_DIR-static
}

JQQRCODEWRITER_BIN_DIR = $$PWD/bin/$$JQQRCODEWRITER_BIN_NO1_DIR/$$JQQRCODEWRITER_BIN_NO2_DIR/$$JQQRCODEWRITER_BIN_NO3_DIR
#message($$JQQRCODEWRITER_BIN_DIR)

# 若bin目录不存在则创建
!exists( $$JQQRCODEWRITER_BIN_DIR ) {
    mkpath( $$JQQRCODEWRITER_BIN_DIR )
}

# 根据不同系统，选择合适的名字
unix | linux | mingw {
    CONFIG( debug, debug | release ) {
        JQQRCODEWRITER_LIB_FILENAME = libJQQRCodeWriterd.a
    }
    CONFIG( release, debug | release ) {
        JQQRCODEWRITER_LIB_FILENAME = libJQQRCodeWriter.a
    }
}
else: msvc {
    CONFIG( debug, debug | release ) {
        JQQRCODEWRITER_LIB_FILENAME = JQQRCodeWriterd.lib
    }
    CONFIG( release, debug | release ) {
        JQQRCODEWRITER_LIB_FILENAME = JQQRCodeWriter.lib
    }
}
else {
    error( unknow platfrom )
}

# 生成bin路径
JQQRCODEWRITER_LIB_FILEPATH = $$JQQRCODEWRITER_BIN_DIR/$$JQQRCODEWRITER_LIB_FILENAME

# 如果未指定编译模式，并且本地存在bin文件，那么使用bin文件
!equals(JQQRCODEWRITER_COMPILE_MODE, SRC) {
    exists($$JQQRCODEWRITER_LIB_FILEPATH) {
        JQQRCODEWRITER_COMPILE_MODE = LIB
    }
    else {
        JQQRCODEWRITER_COMPILE_MODE = SRC
    }
}

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
else : equals(JQQRCODEWRITER_COMPILE_MODE,LIB) {

    LIBS *= $$JQQRCODEWRITER_LIB_FILEPATH
}
else {
    error(unknow JQQRCODEWRITER_COMPILE_MODE: $$JQQRCODEWRITER_COMPILE_MODE)
}

DEFINES *= JQQRCODEWRITER_COMPILE_MODE_STRING=\\\"$$JQQRCODEWRITER_COMPILE_MODE\\\"
DEFINES *= JQQRCODEWRITER_VERSIONSTRING=\\\"$$JQQRCODEWRITER_VERSIONSTRING\\\"
