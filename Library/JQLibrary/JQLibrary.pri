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

exists($$PWD/src/JQBarcode.cpp) {
    SOURCES *= $$PWD/src/JQBarcode.cpp
    HEADERS *= $$PWD/include/JQBarcode.h
}

exists($$PWD/src/JQContainer.cpp) {
    SOURCES *= $$PWD/src/JQContainer.cpp
    HEADERS *= $$PWD/include/JQContainer.h
}

contains( QT, sql ) {
    exists($$PWD/src/JQDatabase.cpp) {
        SOURCES *= $$PWD/src/JQDatabase.cpp
        HEADERS *= $$PWD/include/JQDatabase.h
    }
}

contains( QT, sql ) {
    exists($$PWD/src/JQDatabaseFactory.cpp) {
        SOURCES *= $$PWD/src/JQDatabaseFactory.cpp
        HEADERS *= $$PWD/include/JQDatabaseFactory.h
    }
}

exists($$PWD/src/JQDraw.cpp) {
    SOURCES *= $$PWD/src/JQDraw.cpp
    HEADERS *= $$PWD/include/JQDraw.h
}

exists($$PWD/src/JQEncrypt.cpp) {
    SOURCES *= $$PWD/src/JQEncrypt.cpp
    HEADERS *= $$PWD/include/JQEncrypt.h
}

exists($$PWD/src/JQExcel.cpp) {
    SOURCES *= $$PWD/src/JQExcel.cpp
    HEADERS *= $$PWD/include/JQExcel.h
}

exists($$PWD/src/JQFile.cpp) {
    SOURCES *= $$PWD/src/JQFile.cpp
    HEADERS *= $$PWD/include/JQFile.h
}

exists($$PWD/src/JQFilePack.cpp) {
    SOURCES *= $$PWD/src/JQFilePack.cpp
    HEADERS *= $$PWD/include/JQFilePack.h
}

exists($$PWD/src/JQFoundation.cpp) {
    SOURCES *= $$PWD/src/JQFoundation.cpp
    HEADERS *= $$PWD/include/JQFoundation.h
}

contains(QT, network) {
    contains(QT, concurrent) {
        exists($$PWD/src/JQHttpServer.cpp) {
            SOURCES *= $$PWD/src/JQHttpServer.cpp
            HEADERS *= $$PWD/include/JQHttpServer.h
        }
    }
}

exists($$PWD/src/JQIODevice.cpp) {
    SOURCES *= $$PWD/src/JQIODevice.cpp
    HEADERS *= $$PWD/include/JQIODevice.h
}

ios {
    exists($$PWD/src/JQiOS.cpp) {
        LIBS *= -framework Foundation -framework UIKit
        OBJECTIVE_SOURCES *= $$PWD/src/JQiOS.mm
        HEADERS *= $$PWD/include/JQiOS.h
    }
}

exists($$PWD/JQgSoap.pri) {
    include($$PWD/JQgSoap.pri)
}

exists($$PWD/src/JQJsonStream.cpp) {
    SOURCES *= $$PWD/src/JQJsonStream.cpp
    HEADERS *= $$PWD/include/JQJsonStream.h
}

exists($$PWD/src/JQLanguage.cpp) {
    SOURCES *= $$PWD/src/JQLanguage.cpp
    HEADERS *= $$PWD/include/JQLanguage.h
}

exists($$PWD/src/JQNet.cpp) {
    SOURCES *= $$PWD/src/JQNet.cpp
    HEADERS *= $$PWD/include/JQNet.h
}

contains(QT, opengl) {
    exists($$PWD/src/JQOpenGL.cpp) {
        SOURCES *= $$PWD/src/JQOpenGL.cpp
        HEADERS *= $$PWD/include/JQOpenGL.h
    }
}

exists($$PWD/src/JQPropertyAnimation.cpp) {
    SOURCES *= $$PWD/src/JQPropertyAnimation.cpp
    HEADERS *= $$PWD/include/JQPropertyAnimation.h
}

contains(QT, qml) {
    exists($$PWD/src/JQQml.cpp) {
        SOURCES *= $$PWD/src/JQQml.cpp
        HEADERS *= $$PWD/include/JQQml.h
    }
}

contains(QT, qml) {
    exists($$PWD/JQQMLLib.pri) {
        include($$PWD/JQQMLLib.pri)
    }
}

contains(QT, qml) {
    exists($$PWD/JQQRCodeReader.pri) {
        include($$PWD/JQQRCodeReader.pri)
    }
}

exists($$PWD/JQQRCodeWriter.pri) {
    include($$PWD/JQQRCodeWriter.pri)
}

contains(QT, serialport) {
    exists($$PWD/src/JQSerialPort.cpp) {
        SOURCES *= $$PWD/src/JQSerialPort.cpp
        HEADERS *= $$PWD/include/JQSerialPort.h
    }
}

exists($$PWD/src/JQSettings.cpp) {
    SOURCES *= $$PWD/src/JQSettings.cpp
    HEADERS *= $$PWD/include/JQSettings.h
}

contains(QT, network) {
    exists($$PWD/JQSjf.pri) {
        include($$PWD/JQSjf.pri)
    }
}

exists($$PWD/src/JQSms.cpp) {
    SOURCES *= $$PWD/src/JQSms.cpp
    HEADERS *= $$PWD/include/JQSms.h
}

contains(QT, network) {
    exists($$PWD/src/JQTcpSocket.cpp) {
        SOURCES *= $$PWD/src/JQTcpSocket.cpp
        HEADERS *= $$PWD/include/JQTcpSocket.h
    }
}

exists($$PWD/src/JQTranslation.cpp) {
    SOURCES *= $$PWD/src/JQTranslation.cpp
    HEADERS *= $$PWD/include/JQTranslation.h
}

exists($$PWD/src/JQTrie.cpp) {
    SOURCES *= $$PWD/src/JQTrie.cpp
    HEADERS *= $$PWD/include/JQTrie.h
}

contains(QT, multimedia | concurrent) {
    exists($$PWD/src/JQVop.cpp) {
        SOURCES *= $$PWD/src/JQVop.cpp
        HEADERS *= $$PWD/include/JQVop.h
    }
}

exists($$PWD/src/JQWeather.cpp) {
    SOURCES *= $$PWD/src/JQWeather.cpp
    HEADERS *= $$PWD/include/JQWeather.h
}

contains(QT, webenginewidgets) {
    exists($$PWD/src/JQWebEngine.cpp) {
        SOURCES *= $$PWD/src/JQWebEngine.cpp
        HEADERS *= $$PWD/include/JQWebEngine.h
    }
}

win32 {
    exists($$PWD/JQWinPcap.pri) {
        include($$PWD/JQWinPcap.pri)
    }
}

exists($$PWD/src/JQXmlToJson.cpp) {
    SOURCES *= $$PWD/src/JQXmlToJson.cpp
    HEADERS *= $$PWD/include/JQXmlToJson.h
}
