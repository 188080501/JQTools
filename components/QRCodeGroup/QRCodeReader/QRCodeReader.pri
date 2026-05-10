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
    $$PWD/cpp/qrcodereader.h

SOURCES *= \
    $$PWD/cpp/qrcodereader_.cpp # 因为文件名冲突，所以这里加一个下划线 #

RESOURCES *= \
    $$PWD/qml/QRCodeReaderQml.qrc \
    $$PWD/resources/images/QRCodeReaderImages.qrc
