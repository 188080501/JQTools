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

include( $$PWD/library/JQLibrary/JQLibrary.pri )
include( $$PWD/library/JQLibrary/JQQRCodeReader.pri )
include( $$PWD/library/JQLibrary/JQQRCodeWriter.pri )
include( $$PWD/library/JQLibrary/JQZopfli.pri )

mac {
    include( $$PWD/library/JQLibrary/JQGuetzli.pri )
}
