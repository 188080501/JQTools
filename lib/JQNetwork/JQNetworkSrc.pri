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

HEADERS *= \
    $$PWD/include/jqnetwork_foundation.h \
    $$PWD/include/jqnetwork_package.h \
    $$PWD/include/jqnetwork_connect.h \
    $$PWD/include/jqnetwork_connectpool.h \
    $$PWD/include/jqnetwork_server.h \
    $$PWD/include/jqnetwork_processor.h \
    $$PWD/include/jqnetwork_client.h \
    $$PWD/include/jqnetwork_lan.h \
    $$PWD/include/jqnetwork_encrypt.h \
    $$PWD/include/jqnetwork_forwarf.h

HEADERS *= \
    $$PWD/include/jqnetwork_foundation.inc \
    $$PWD/include/jqnetwork_package.inc \
    $$PWD/include/jqnetwork_connect.inc \
    $$PWD/include/jqnetwork_connectpool.inc \
    $$PWD/include/jqnetwork_server.inc \
    $$PWD/include/jqnetwork_processor.inc \
    $$PWD/include/jqnetwork_client.inc \
    $$PWD/include/jqnetwork_lan.inc \
    $$PWD/include/jqnetwork_encrypt.inc \
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
