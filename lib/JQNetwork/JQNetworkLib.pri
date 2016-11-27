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

macx {

    exists( $$OUT_PWD/../../builder/JQNetworkLibBuilder/libJQNetwork.a ) {
        LIBS += $$OUT_PWD/../../builder/JQNetworkLibBuilder/libJQNetwork.a
    }
}
