#
#   This file is part of JQLibrary
#
#   Copyright: Jason and others
#
#   Contact email: 188080501@qq.com
#
#   Permission is hereby granted, free of charge, to any person obtaining
#   a copy of this software and associated documentation files (the
#   "Software"), to deal in the Software without restriction, including
#   without limitation the rights to use, copy, modify, merge, publish,
#   distribute, sublicense, and/or sell copies of the Software, and to
#   permit persons to whom the Software is furnished to do so, subject to
#   the following conditions:
#
#   The above copyright notice and this permission notice shall be
#   included in all copies or substantial portions of the Software.
#
#   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
#   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
#   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
#   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
#   LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
#   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
#   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#


QT *= core gui

CONFIG *= c++11

INCLUDEPATH *= \
    $$PWD/include/

exists( $$PWD/src/JQBarcode.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQBarcode.h

        SOURCES *= $$PWD/src/JQBarcode.cpp
    }
}

contains( QT, bluetooth ) : exists( $$PWD/src/JQBluetooth.cpp ) {

    mac | ios {
        DEFINES += JQBLUETOOTH_UUIDMODE
    }

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQBluetooth.h

        SOURCES *= $$PWD/src/JQBluetooth.cpp
    }
}

exists( $$PWD/include/jqchecksum.hpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqchecksum.hpp
    }
}

exists( $$PWD/include/jqdeclare.hpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqdeclare.hpp
    }
}

exists( $$PWD/src/JQExcel.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQExcel.h

        SOURCES *= $$PWD/src/JQExcel.cpp
    }
}

exists( $$PWD/src/JQFile.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQFile.h

        SOURCES *= $$PWD/src/JQFile.cpp
    }
}

unix | linux | mingw {

    exists( $$PWD/src/JQFilePack.cpp ) {

        !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

            HEADERS *= $$PWD/include/JQFilePack.h

            SOURCES *= $$PWD/src/JQFilePack.cpp
        }
    }
}

exists( $$PWD/src/JQFoundation.cpp ) {

    DEFINES += JQFOUNDATION_LIB

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQFoundation.h

        HEADERS *= $$PWD/include/jqdeclare.hpp

        SOURCES *= $$PWD/src/JQFoundation.cpp
    }
}

exists( $$PWD/src/jqgpio.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqgpio.h

        SOURCES *= $$PWD/src/jqgpio.cpp
    }
}

contains( QT, network ) : contains( QT, concurrent ) : exists( $$PWD/src/jqhttpserver.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqhttpserver.h

        SOURCES *= $$PWD/src/jqhttpserver.cpp
    }
}

ios : exists( $$PWD/src/JQiOS.cpp ) {

    LIBS *= -framework Foundation -framework UIKit

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQiOS.h

        OBJECTIVE_SOURCES *= $$PWD/src/JQiOS.mm
    }
}

exists( $$PWD/src/JQLanguage.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQLanguage.h

        SOURCES *= $$PWD/src/JQLanguage.cpp
    }
}

contains( QT, network ) : exists( $$PWD/src/jqnet.cpp ) : !wasm {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqnet.h

        SOURCES *= $$PWD/src/jqnet.cpp
    }
}

contains( QT, serialport ) : exists( $$PWD/src/JQSerialPort.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQSerialPort.h

        SOURCES *= $$PWD/src/JQSerialPort.cpp
    }
}

exists( $$PWD/src/JQSettings.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQSettings.h

        SOURCES *= $$PWD/src/JQSettings.cpp
    }
}

exists( $$PWD/src/JQSms.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQSms.h

        SOURCES *= $$PWD/src/JQSms.cpp
    }
}

contains( QT, network ) : exists( $$PWD/src/JQSystemFlag.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQSystemFlag.h

        SOURCES *= $$PWD/src/JQSystemFlag.cpp
    }
}

exists( $$PWD/src/jqthread.cpp ) : !wasm {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/jqthread.h

        SOURCES *= $$PWD/src/jqthread.cpp
    }
}

contains( QT, webenginewidgets ) : exists( $$PWD/src/JQWebEngine.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQWebEngine.h

        SOURCES *= $$PWD/src/JQWebEngine.cpp
    }
}
