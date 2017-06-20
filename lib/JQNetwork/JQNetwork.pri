#
#   This file is part of JQNetwork
#
#   Library introduce: https://github.com/188080501/JQNetwork
#
#   Copyright: Jason
#
#   Contact email: Jason@JasonServer.com
#
#   GitHub: https://github.com/188080501/
#

QT *= core network concurrent

CONFIG *= c++11
CONFIG *= c++14

INCLUDEPATH *= \
    $$PWD/include/

# 定义JQNetwork的版本
JQNETWORK_VERSIONSTRING = 0.6.4

# 判断Qt版本，小于等于5.6就报错
lessThan( QT_MAJOR_VERSION, 5 ) | lessThan( QT_MINOR_VERSION, 7 ) {
    error( JQNetwork request minimum Qt version is 5.7.0 )
}

# 准备bin库目录
JQNETWORK_BIN_NO1_DIR = JQNetwork$$JQNETWORK_VERSIONSTRING/Qt$$[QT_VERSION]
JQNETWORK_BIN_NO2_DIR = $$QT_ARCH
JQNETWORK_BIN_NO3_DIR = $$[QMAKE_XSPEC]
JQNETWORK_BIN_NO3_DIR ~= s/g\+\+/gcc

# 根据编译参数，追加static名称
contains( CONFIG, static ) {
    JQNETWORK_BIN_NO3_DIR = $$JQNETWORK_BIN_NO3_DIR-static
}

JQNETWORK_BIN_DIR = $$PWD/bin/$$JQNETWORK_BIN_NO1_DIR/$$JQNETWORK_BIN_NO2_DIR/$$JQNETWORK_BIN_NO3_DIR
#message($$JQNETWORK_BIN_DIR)

# 若bin目录不存在则创建
!exists( $$JQNETWORK_BIN_DIR ) {
    mkpath( $$JQNETWORK_BIN_DIR )
}

# 根据不同系统，选择合适的名字
unix | linux | mingw {
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetworkd.a
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetwork.a
    }
}
else: msvc {
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = JQNetworkd.lib
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = JQNetwork.lib
    }
}
else {
    error( unknow platfrom )
}

# 生成bin路径
JQNETWORK_LIB_FILEPATH = $$JQNETWORK_BIN_DIR/$$JQNETWORK_LIB_FILENAME

# 如果未指定编译模式，并且本地存在bin文件，那么使用bin文件
!equals(JQNETWORK_COMPILE_MODE, SRC) {
    exists($$JQNETWORK_LIB_FILEPATH) {
        JQNETWORK_COMPILE_MODE = LIB
    }
    else {
        JQNETWORK_COMPILE_MODE = SRC
    }
}

equals(JQNETWORK_COMPILE_MODE,SRC) {

    HEADERS *= \
        $$PWD/include/jqnetwork_foundation.h \
        $$PWD/include/jqnetwork_foundation.inc \
        $$PWD/include/jqnetwork_package.h \
        $$PWD/include/jqnetwork_package.inc \
        $$PWD/include/jqnetwork_connect.h \
        $$PWD/include/jqnetwork_connect.inc \
        $$PWD/include/jqnetwork_connectpool.h \
        $$PWD/include/jqnetwork_connectpool.inc \
        $$PWD/include/jqnetwork_server.h \
        $$PWD/include/jqnetwork_server.inc \
        $$PWD/include/jqnetwork_processor.h \
        $$PWD/include/jqnetwork_processor.inc \
        $$PWD/include/jqnetwork_client.h \
        $$PWD/include/jqnetwork_client.inc \
        $$PWD/include/jqnetwork_lan.h \
        $$PWD/include/jqnetwork_lan.inc

    SOURCES *= \
        $$PWD/src/jqnetwork_foundation.cpp \
        $$PWD/src/jqnetwork_package.cpp \
        $$PWD/src/jqnetwork_connect.cpp \
        $$PWD/src/jqnetwork_connectpool.cpp \
        $$PWD/src/jqnetwork_server.cpp \
        $$PWD/src/jqnetwork_processor.cpp \
        $$PWD/src/jqnetwork_client.cpp \
        $$PWD/src/jqnetwork_lan.cpp

}
else : equals(JQNETWORK_COMPILE_MODE,LIB) {

    LIBS *= $$JQNETWORK_LIB_FILEPATH
}
else {
    error(unknow JQNETWORK_COMPILE_MODE: $$JQNETWORK_COMPILE_MODE)
}

# 如果开启了qml模块，那么引入JQNetwork的qml扩展部分
contains( QT, qml ) {

    HEADERS *= \
        $$PWD/include/jqnetwork_clientforqml.h \
        $$PWD/include/jqnetwork_clientforqml.inc

    SOURCES *= \
        $$PWD/src/jqnetwork_clientforqml.cpp

    RESOURCES *= \
        $$PWD/qml/JQNetworkQml.qrc

    QML_IMPORT_PATH *= \
        $$PWD/qml/
}

DEFINES *= JQNETWORK_COMPILE_MODE_STRING=\\\"$$JQNETWORK_COMPILE_MODE\\\"
DEFINES *= JQNETWORK_VERSIONSTRING=\\\"$$JQNETWORK_VERSIONSTRING\\\"
