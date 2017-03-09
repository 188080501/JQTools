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

lessThan( QT_MAJOR_VERSION, 5 ) | lessThan( QT_MINOR_VERSION, 7 ) {
    error( JQNetwork request minimum Qt version is 5.7.0 )
}


JQNETWORK_BIN_NO1_DIR = $$[QT_VERSION]
JQNETWORK_BIN_NO2_DIR = $$QT_ARCH
JQNETWORK_BIN_NO3_DIR = $$[QMAKE_XSPEC]

ios {
    CONFIG( iphonesimulator, iphonesimulator | iphoneos ) {
        JQNETWORK_BIN_NO3_DIR = macx-iphonesimulator-clang
    }
    else {
        JQNETWORK_BIN_NO3_DIR = macx-iphoneos-clang
    }
}

contains( CONFIG, static ) {
    JQNETWORK_BIN_NO3_DIR = $$JQNETWORK_BIN_NO3_DIR-static
}

JQNETWORK_BIN_DIR = $$PWD/bin/$$JQNETWORK_BIN_NO1_DIR/$$JQNETWORK_BIN_NO2_DIR/$$JQNETWORK_BIN_NO3_DIR

#message($$JQNETWORK_BIN_DIR)

!exists( $$JQNETWORK_BIN_DIR ) {
    mkpath( $$JQNETWORK_BIN_DIR )
}

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

JQNETWORK_LIB_FILEPATH = $$JQNETWORK_BIN_DIR/$$JQNETWORK_LIB_FILENAME

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

contains( QT, qml ) {

    HEADERS *= \
        $$PWD/include/jqnetwork_clientforqml.h \
        $$PWD/include/jqnetwork_clientforqml.inc

    SOURCES *= \
        $$PWD/src/jqnetwork_clientforqml.cpp
}

DEFINES += JQNETWORK_COMPILE_MODE_STRING=\\\"$$JQNETWORK_COMPILE_MODE\\\"
