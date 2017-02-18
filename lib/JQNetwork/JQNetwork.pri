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

lessThan(QT_MAJOR_VERSION, 5) | lessThan(QT_MINOR_VERSION, 7) {
    error( JQNetwork request minimum Qt version is 5.7.0 )
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
        $$PWD/include/*.h \
        $$PWD/include/*.inc

    SOURCES += \
        $$PWD/src/*.cpp

}
else : equals(JQNETWORK_COMPILE_MODE,LIB) {
    LIBS *= $$JQNETWORK_LIB_FILEPATH
}
else {
    error(unknow JQNETWORK_COMPILE_MODE: $$JQNETWORK_COMPILE_MODE)
}

DEFINES += JQNETWORK_COMPILE_MODE_STRING=\\\"$$JQNETWORK_COMPILE_MODE\\\"
