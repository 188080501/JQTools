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

lessThan(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 6) {
    error( JQNetwork request minimum Qt version is 5.6.0 )
}

equals(QT_VERSION, 5.6.0) : win32-g++ : contains( CONFIG, static ) {
    JQNETWORK_LIB_DIR = $$PWD/lib/5.6.0_windows_x86_gcc_static
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetworkd.a
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetwork.a
    }
}
else : equals(QT_VERSION, 5.6.0) : win32-g++ {
    JQNETWORK_LIB_DIR = $$PWD/lib/5.6.0_windows_x86_gcc
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetworkd.a
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetwork.a
    }
}
else : equals(QT_VERSION, 5.7.0) : mac {
    JQNETWORK_LIB_DIR = $$PWD/lib/5.7.0_macos_x64_clang
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetworkd.a
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetwork.a
    }
}
else {
    JQNETWORK_LIB_DIR = $$PWD/lib/unknow_unknow_unknow
    CONFIG( debug, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetworkd.a
    }
    CONFIG( release, debug | release ) {
        JQNETWORK_LIB_FILENAME = libJQNetwork.a
    }
}

JQNETWORK_LIB_FILEPATH = $$JQNETWORK_LIB_DIR/$$JQNETWORK_LIB_FILENAME

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
        $$PWD/include/jqnetwork_lan.inc \
        $$PWD/include/jqnetwork_encrypt.h \
        $$PWD/include/jqnetwork_encrypt.inc \
        $$PWD/include/jqnetwork_forwarf.h \
        $$PWD/include/jqnetwork_forwarf.inc

    SOURCES += \
        $$PWD/src/jqnetwork_foundation.cpp \
        $$PWD/src/jqnetwork_package.cpp \
        $$PWD/src/jqnetwork_connect.cpp \
        $$PWD/src/jqnetwork_connectpool.cpp \
        $$PWD/src/jqnetwork_server.cpp \
        $$PWD/src/jqnetwork_processor.cpp \
        $$PWD/src/jqnetwork_client.cpp \
        $$PWD/src/jqnetwork_lan.cpp \
        $$PWD/src/jqnetwork_encrypt.cpp \
        $$PWD/src/jqnetwork_forwarf.cpp

}
else : equals(JQNETWORK_COMPILE_MODE,LIB) {
    LIBS *= $$JQNETWORK_LIB_FILEPATH
}
else {
    error(unknow JQNETWORK_COMPILE_MODE: $$JQNETWORK_COMPILE_MODE)
}

DEFINES += JQNETWORK_COMPILE_MODE_STRING=\\\"$$JQNETWORK_COMPILE_MODE\\\"
