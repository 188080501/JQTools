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

include( $$PWD/BatchReplacement/BatchReplacement.pri )

!wasm {
    include( $$PWD/LinesStatistics/LinesStatistics.pri )
    include( $$PWD/ScreenColorPicker/ScreenColorPicker.pri )
}

INCLUDEPATH *= \
    $$PWD/

HEADERS *= \
    $$PWD/toolsgroup.h
