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

include( $$PWD/LinesStatistics/LinesStatistics.pri )
include( $$PWD/LanFileTransport/LanFileTransport.pri )
include( $$PWD/PngOptimize/PngOptimize.pri )
mac {
    include( $$PWD/JpgOptimize/JpgOptimize.pri )
}
include( $$PWD/QRCodeReader/QRCodeReader.pri )
include( $$PWD/BatchReplacement/BatchReplacement.pri )
include( $$PWD/ScreenColorPicker/ScreenColorPicker.pri )

INCLUDEPATH *= \
    $$PWD/

HEADERS *= \
    $$PWD/toolsgroup.h
