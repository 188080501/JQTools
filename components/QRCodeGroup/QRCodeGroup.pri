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

include( $$PWD/QRCodeMaker/QRCodeMaker.pri )
include( $$PWD/BarcodeMaker/BarcodeMaker.pri )
include( $$PWD/QRCodeReader/QRCodeReader.pri )

INCLUDEPATH *= \
    $$PWD/

HEADERS *= \
    $$PWD/qrcodegroup.h
