/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import FileHashCalculate 1.0

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

    JQText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 32
        text: qsTr( "选择单个文件后，计算 MD5、SHA1 与 SHA256 哈希值" )
    }

    JQButton {
        x: 48
        y: 78
        width: 120
        height: 50
        text: qsTr( "选择文件" )

        onClicked: {
            fileHashCalculateManage.chooseFile();
        }
    }

    JQButton {
        x: 182
        y: 78
        width: 120
        height: 50
        text: qsTr( "计算哈希" )

        onClicked: {
            var reply = fileHashCalculateManage.calculate();

            switch( reply )
            {
                case "OK":
                    JQGlobal.showMessage( qsTr( "哈希值计算完成" ) );
                    break;
                case "empty file path":
                    JQGlobal.showMessage( qsTr( "请先选择文件" ) );
                    break;
                case "file not exist":
                    JQGlobal.showMessage( qsTr( "文件不存在，请重新选择" ) );
                    break;
                case "calculate hash error":
                    JQGlobal.showMessage( qsTr( "文件读取失败，无法计算哈希值" ) );
                    break;
            }
        }
    }

    JQButton {
        x: 316
        y: 78
        width: 120
        height: 50
        text: qsTr( "清空" )

        onClicked: {
            fileHashCalculateManage.clear();
        }
    }

    JQPane {
        x: 40
        y: 142
        width: 560
        height: 230
    }

    Rectangle {
        x: 40
        y: 142
        width: 540
        height: 230
        color: "#ffffff"
    }

    JQText {
        x: 58
        y: 160
        width: 504
        text: qsTr( "文件路径：" ) + fileHashCalculate.filePathValue
        elide: Text.ElideMiddle
    }

    JQText {
        x: 58
        y: 206
        width: 400
        text: qsTr( "MD5：" ) + fileHashCalculate.md5Value
        elide: Text.ElideRight
    }

    JQButton {
        x: 468
        y: 194
        width: 110
        height: 50
        text: qsTr( "复制 MD5" )

        onClicked: {
            if ( fileHashCalculate.md5Value.length === 0 )
            {
                JQGlobal.showMessage( qsTr( "当前没有可复制的 MD5 结果" ) );
                return;
            }

            fileHashCalculateManage.copyMd5();
            JQGlobal.showMessage( qsTr( "MD5 结果已复制到剪贴板" ) );
        }
    }

    JQText {
        x: 58
        y: 258
        width: 400
        text: qsTr( "SHA1：" ) + fileHashCalculate.sha1Value
        elide: Text.ElideRight
    }

    JQButton {
        x: 468
        y: 246
        width: 110
        height: 50
        text: qsTr( "复制 SHA1" )

        onClicked: {
            if ( fileHashCalculate.sha1Value.length === 0 )
            {
                JQGlobal.showMessage( qsTr( "当前没有可复制的 SHA1 结果" ) );
                return;
            }

            fileHashCalculateManage.copySha1();
            JQGlobal.showMessage( qsTr( "SHA1 结果已复制到剪贴板" ) );
        }
    }

    JQText {
        x: 58
        y: 310
        width: 400
        text: qsTr( "SHA256：" ) + fileHashCalculate.sha256Value
        elide: Text.ElideRight
    }

    JQButton {
        x: 468
        y: 298
        width: 110
        height: 50
        text: qsTr( "复制 SHA256" )

        onClicked: {
            if ( fileHashCalculate.sha256Value.length === 0 )
            {
                JQGlobal.showMessage( qsTr( "当前没有可复制的 SHA256 结果" ) );
                return;
            }

            fileHashCalculateManage.copySha256();
            JQGlobal.showMessage( qsTr( "SHA256 结果已复制到剪贴板" ) );
        }
    }
}
