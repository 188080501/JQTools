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

include( $$PWD/Utf16Transform/Utf16Transform.pri )
include( $$PWD/RgbStringTransform/RgbStringTransform.pri )
include( $$PWD/UrlEncode/UrlEncode.pri )
include( $$PWD/RandomPassword/RandomPassword.pri )
include( $$PWD/RandomUuid/RandomUuid.pri )
include( $$PWD/CaseTransform/CaseTransform.pri )
include( $$PWD/JsonFormat/JsonFormat.pri )
include( $$PWD/StringSort/StringSort.pri )

INCLUDEPATH *= \
    $$PWD/

HEADERS *= \
    $$PWD/textgroup.h
