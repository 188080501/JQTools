TEMPLATE = app

QT += qml quick widgets concurrent

CONFIG += c++11
CONFIG += c++14

include($$PWD/lib/JQLibrary/JQLibrary.pri)
include($$PWD/lib/MaterialUI/MaterialUI.pri)
include($$PWD/lib/JQToolsLibrary/JQToolsLibrary.pri)
include($$PWD/components/components.pri)

INCLUDEPATH += \
    $$PWD/cpp/

HEADERS += \
    $$PWD/cpp/*.hpp

SOURCES += \
    $$PWD/cpp/*.cpp

RESOURCES += \
    $$PWD/qml/qml.qrc

macx{
    ICON = $$PWD/resources/Icon/Icon.icns
}

win32{
    RC_FILE = $$PWD/resources/Icon/Icon.rc
}
