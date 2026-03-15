#
#   This file is part of JQTools
#
#   Project introduce: https://github.com/188080501/JQTools
#
#   Copyright: Jason
#
#   Contact email: Jason@JasonServer.com
#
#   GitHub: https://github.com/188080501/
#

TEMPLATE = app

QT *= qml quick widgets quickcontrols2

CONFIG += c++11
CONFIG += c++14

include( $$PWD/library/JQLibraryImport.pri )
include( $$PWD/library/JQToolsLibrary/JQToolsLibrary.pri )
include( $$PWD/components/components.pri )

INCLUDEPATH *= \
    $$PWD/cpp/

SOURCES *= \
    $$PWD/cpp/main.cpp

RESOURCES *= \
    $$PWD/qml/qml.qrc \
    $$PWD/fonts/fonts.qrc \
    $$PWD/images/jqcontrolsimages.qrc \
    $$PWD/qml/jqcontrolsqml.qrc

QML_IMPORT_PATH *= \
    $$PWD/qml

mac {
    ICON = $$PWD/icon/icon.icns

    CONFIG += sdk_no_version_check
}

win32 {
    RC_ICONS = $$PWD/icon/icon.ico
}

!wasm {
    QT *= concurrent
}
