#
#   This file is part of JQLibrary
#
#   Copyright: Jason
#
#   Contact email: 188080501@qq.com
#
#   GNU Lesser General Public License Usage
#   Alternatively, this file may be used under the terms of the GNU Lesser
#   General Public License version 2.1 or version 3 as published by the Free
#   Software Foundation and appearing in the file LICENSE.LGPLv21 and
#   LICENSE.LGPLv3 included in the packaging of this file. Please review the
#   following information to ensure the GNU Lesser General Public License
#   requirements will be met: https://www.gnu.org/licenses/lgpl.html and
#   http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
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

exists( $$PWD/src/JQChecksum.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQChecksum.h

        SOURCES *= $$PWD/src/JQChecksum.cpp
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

contains( QT, network ) : contains( QT, concurrent ) : exists( $$PWD/src/JQHttpServer.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQHttpServer.h

        SOURCES *= $$PWD/src/JQHttpServer.cpp
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

contains( QT, network ) : exists( $$PWD/src/JQNet.cpp ) {

    !contains( DEFINES, JQLIBRARY_EXPORT_ENABLE ) | contains( DEFINES, JQLIBRARY_EXPORT_MODE ) {

        HEADERS *= $$PWD/include/JQNet.h

        SOURCES *= $$PWD/src/JQNet.cpp
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

exists( $$PWD/src/jqthread.cpp ) {

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
