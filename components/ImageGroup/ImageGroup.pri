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

include( $$PWD/IconMaker/IconMaker.pri )
include( $$PWD/FontToPng/FontToPng.pri )
include( $$PWD/PngWarningRemover/PngWarningRemover.pri )
include( $$PWD/WebPMaker/WebPMaker.pri )
include( $$PWD/PngOptimize/PngOptimize.pri )
include( $$PWD/JpgOptimize/JpgOptimize.pri )

INCLUDEPATH *= \
    $$PWD/

HEADERS *= \
    $$PWD/imagegroup.h
