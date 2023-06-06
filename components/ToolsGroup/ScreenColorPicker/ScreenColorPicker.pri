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

INCLUDEPATH *= \
    $$PWD/cpp/

HEADERS *= \
    $$PWD/cpp/colorpicker.h\
    $$PWD/cpp/mousedropper.h \
    $$PWD/cpp/screenColorPicker.h
    $$PWD/cpp/screenColorPicker.h


SOURCES *= \
    $$PWD/cpp/colorpicker.cpp\
    $$PWD/cpp/mousedropper.cpp\
    $$PWD/cpp/screenColorPicker.cpp


RESOURCES *= \
    $$PWD/qml/ScreenColorPicker.qrc

DISTFILES += \
    $$PWD/res/ico/ColorPickerPen.png
