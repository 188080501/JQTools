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

include( $$PWD/lib/JQLibrary/JQLibrary.pri )

mac {
    include( $$PWD/lib/JQLibrary/JQGuetzli.pri )
}

include( $$PWD/lib/JQLibrary/JQQmlLib.pri )
include( $$PWD/lib/JQLibrary/JQQRCodeReader.pri )
include( $$PWD/lib/JQLibrary/JQQRCodeWriter.pri )
include( $$PWD/lib/JQLibrary/JQZopfli.pri )
