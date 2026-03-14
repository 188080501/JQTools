/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import FileHashCalculate 1.0
import JQControls 1.0

Item {
    id: fileHashCalculate
    width: 620
    height: 540
    property string filePathValue: ""
    property string md5Value: ""
    property string sha1Value: ""
    property string sha256Value: ""

    FileHashCalculateManage {
        id: fileHashCalculateManage

        onFilePathChanged: {
            fileHashCalculate.filePathValue = fileHashCalculateManage.filePath();
        }

        onMd5ValueChanged: {
            fileHashCalculate.md5Value = fileHashCalculateManage.md5Value();
        }

        onSha1ValueChanged: {
            fileHashCalculate.sha1Value = fileHashCalculateManage.sha1Value();
        }

        onSha256ValueChanged: {
            fileHashCalculate.sha256Value = fileHashCalculateManage.sha256Value();
        }
    }

    MaterialLabel {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 32
        text: qsTr( "\u9009\u62e9\u5355\u4e2a\u6587\u4ef6\u540e\uff0c\u8ba1\u7b97 MD5\u3001SHA1 \u4e0e SHA256 \u54c8\u5e0c\u503c" )
    }

    MaterialButton {
        x: 48
        y: 78
        width: 120
        height: 40
        text: qsTr( "\u9009\u62e9\u6587\u4ef6" )

        onClicked: {
            fileHashCalculateManage.chooseFile();
        }
    }

    MaterialButton {
        x: 182
        y: 78
        width: 120
        height: 40
        text: qsTr( "\u8ba1\u7b97\u54c8\u5e0c" )

        onClicked: {
            var reply = fileHashCalculateManage.calculate();

            switch( reply )
            {
                case "OK":
                    materialUI.showSnackbarMessage( qsTr( "\u54c8\u5e0c\u503c\u8ba1\u7b97\u5b8c\u6210" ) );
                    break;
                case "empty file path":
                    materialUI.showSnackbarMessage( qsTr( "\u8bf7\u5148\u9009\u62e9\u6587\u4ef6" ) );
                    break;
                case "file not exist":
                    materialUI.showSnackbarMessage( qsTr( "\u6587\u4ef6\u4e0d\u5b58\u5728\uff0c\u8bf7\u91cd\u65b0\u9009\u62e9" ) );
                    break;
                case "calculate hash error":
                    materialUI.showSnackbarMessage( qsTr( "\u6587\u4ef6\u8bfb\u53d6\u5931\u8d25\uff0c\u65e0\u6cd5\u8ba1\u7b97\u54c8\u5e0c\u503c" ) );
                    break;
            }
        }
    }

    MaterialButton {
        x: 316
        y: 78
        width: 120
        height: 40
        text: qsTr( "\u6e05\u7a7a" )

        onClicked: {
            fileHashCalculateManage.clear();
        }
    }

    RectangularGlow {
        x: 40
        y: 142
        width: 540
        height: 230
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    Rectangle {
        x: 40
        y: 142
        width: 540
        height: 230
        color: "#ffffff"
    }

    MaterialLabel {
        x: 58
        y: 160
        width: 504
        text: qsTr( "\u6587\u4ef6\u8def\u5f84\uff1a" ) + fileHashCalculate.filePathValue
        elide: Text.ElideMiddle
    }

    MaterialLabel {
        x: 58
        y: 206
        width: 400
        text: qsTr( "MD5\uff1a" ) + fileHashCalculate.md5Value
        elide: Text.ElideRight
    }

    MaterialButton {
        x: 468
        y: 194
        width: 94
        height: 36
        text: qsTr( "\u590d\u5236 MD5" )

        onClicked: {
            if ( fileHashCalculate.md5Value.length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr( "\u5f53\u524d\u6ca1\u6709\u53ef\u590d\u5236\u7684 MD5 \u7ed3\u679c" ) );
                return;
            }

            fileHashCalculateManage.copyMd5();
            materialUI.showSnackbarMessage( qsTr( "MD5 \u7ed3\u679c\u5df2\u590d\u5236\u5230\u526a\u8d34\u677f" ) );
        }
    }

    MaterialLabel {
        x: 58
        y: 258
        width: 400
        text: qsTr( "SHA1\uff1a" ) + fileHashCalculate.sha1Value
        elide: Text.ElideRight
    }

    MaterialButton {
        x: 468
        y: 246
        width: 94
        height: 36
        text: qsTr( "\u590d\u5236 SHA1" )

        onClicked: {
            if ( fileHashCalculate.sha1Value.length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr( "\u5f53\u524d\u6ca1\u6709\u53ef\u590d\u5236\u7684 SHA1 \u7ed3\u679c" ) );
                return;
            }

            fileHashCalculateManage.copySha1();
            materialUI.showSnackbarMessage( qsTr( "SHA1 \u7ed3\u679c\u5df2\u590d\u5236\u5230\u526a\u8d34\u677f" ) );
        }
    }

    MaterialLabel {
        x: 58
        y: 310
        width: 400
        text: qsTr( "SHA256\uff1a" ) + fileHashCalculate.sha256Value
        elide: Text.ElideRight
    }

    MaterialButton {
        x: 468
        y: 298
        width: 94
        height: 36
        text: qsTr( "\u590d\u5236 SHA256" )

        onClicked: {
            if ( fileHashCalculate.sha256Value.length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr( "\u5f53\u524d\u6ca1\u6709\u53ef\u590d\u5236\u7684 SHA256 \u7ed3\u679c" ) );
                return;
            }

            fileHashCalculateManage.copySha256();
            materialUI.showSnackbarMessage( qsTr( "SHA256 \u7ed3\u679c\u5df2\u590d\u5236\u5230\u526a\u8d34\u677f" ) );
        }
    }
}
