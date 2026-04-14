PRO_PATH = $$PWD
PRO_ROOT = $$clean_path($$PWD/../..)
TARGET = JQTools

TEMPLATE = app

QT *= qml quick widgets quickcontrols2

CONFIG += c++11
CONFIG += c++14

include( $$PRO_ROOT/library/JQLibraryImport.pri )
include( $$PRO_ROOT/library/JQToolsLibrary/JQToolsLibrary.pri )
include( $$PRO_ROOT/components/components.pri )

INCLUDEPATH *= \
    $$PWD/cpp/

SOURCES *= \
    $$PWD/cpp/main.cpp

RESOURCES *= \
    $$PRO_ROOT/qml/qml.qrc \
    $$PRO_ROOT/fonts/fonts.qrc \
    $$PRO_ROOT/images/jqcontrolsimages.qrc \
    $$PRO_ROOT/qml/jqcontrolsqml.qrc

QML_IMPORT_PATH *= \
    $$PRO_ROOT/qml

mac {
    ICON = $$PRO_ROOT/icon/icon.icns

    CONFIG += sdk_no_version_check
}

win32 {
    RC_ICONS = $$PRO_ROOT/icon/icon.ico
}

!wasm {
    QT *= concurrent
}

wasm : !isEmpty( PRO_PATH ) {

    versionAtLeast( QT_VERSION, 6.8.3 ) : versionAtMost( QT_VERSION, 6.8.3 ) {

        exists( $$PRO_PATH/shell/copy_wasm_release.bat ) : CONFIG( release, debug | release ) {

            QMAKE_POST_LINK *= $$PRO_PATH/shell/copy_wasm_release.bat $$escape_expand(\\n\\t)
        }
    }
}
