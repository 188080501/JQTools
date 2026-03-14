/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import HashCalculate 1.0

Item {
    id: hashCalculate
    width: 620
    height: 540

    property bool changingFlag: false

    HashCalculateManage {
        id: hashCalculateManage

        onSourceChanged: {
            if ( hashCalculate.changingFlag ) { return; }

            hashCalculate.changingFlag = true;

            textFieldForSource.text = hashCalculateManage.source();

            hashCalculate.changingFlag = false;
        }

        onTargetChanged: {
            if ( hashCalculate.changingFlag ) { return; }

            hashCalculate.changingFlag = true;

            textFieldForTarget.text = hashCalculateManage.target();

            hashCalculate.changingFlag = false;
        }
    }

    JQText {
        text: "源字符串"
        anchors.horizontalCenterOffset: 0
        anchors.bottom: itemForSource.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: itemForSource.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    JQPane {
        z: -1
        anchors.fill: itemForSource
    }

    Item {
        id: itemForSource
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 40
        width: hashCalculate.width - 280
        height: (hashCalculate.height - 100) / 2
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        Flickable {
            x: 5
            y: 5
            width: parent.width - 10
            height: parent.height - 10
            contentWidth: textFieldForSource.paintedWidth
            contentHeight: textFieldForSource.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForSource
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"

                onTextChanged: {
                    if ( hashCalculate.changingFlag ) { return; }

                    hashCalculate.changingFlag = true;

                    hashCalculateManage.setSource( textFieldForSource.text );

                    hashCalculate.changingFlag = false;
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            visible: !textFieldForSource.focus

            onClicked: {
                textFieldForSource.focus = true;
            }
        }
    }

    JQText {
        text: "计算结果"
        anchors.horizontalCenterOffset: 0
        anchors.bottom: itemForTarget.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: itemForTarget.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    JQPane {
        z: -1
        anchors.fill: itemForTarget
    }

    Item {
        id: itemForTarget
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: hashCalculate.width - 280
        height: (hashCalculate.height - 100) / 2
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        Flickable {
            x: 5
            y: 5
            width: parent.width - 10
            height: parent.height - 10
            contentWidth: textFieldForTarget.paintedWidth
            contentHeight: textFieldForTarget.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForTarget
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"
            }
        }

        MouseArea {
            anchors.fill: parent
            visible: !textFieldForTarget.focus

            onClicked: {
                textFieldForTarget.focus = true;
            }
        }
    }

    Item {
        id: itemForButtons
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: 250
        height: 430

        JQButton {
            x: 8
            y: 1
            width: 110
            height: 50
            text: "粘贴内容"

            onClicked: {
                hashCalculateManage.paste();
            }
        }

        JQButton {
            x: 8
            y: 47
            width: 110
            height: 50
            text: "清空所有"

            onClicked: {
                hashCalculateManage.clear();
            }
        }

        JQButton {
            x: 124
            y: 1
            width: 110
            height: 50
            text: "复制结果"

            onClicked: {
                hashCalculateManage.copy();
                JQGlobal.showMessage( "已将计算结果复制到了系统剪贴板" );
            }
        }

        JQButton {
            x: 124
            y: 47
            width: 110
            height: 50
            text: "剪切到源"

            onClicked: {
                hashCalculateManage.moveTargetToSource();
            }
        }

        JQButton {
            x: 8
            y: 93
            width: 110
            height: 50
            text: "To Base64"

            onClicked: {
                hashCalculateManage.encodeToBase64();
            }
        }

        JQButton {
            x: 124
            y: 93
            width: 110
            height: 50
            text: "From Base64"

            onClicked: {
                hashCalculateManage.decodeFromBase64();
            }
        }

        JQButton {
            x: 8
            y: 139
            width: 110
            height: 50
            text: "MD4"

            onClicked: {
                hashCalculateManage.calculateMD4();
            }
        }

        JQButton {
            x: 124
            y: 139
            width: 110
            height: 50
            text: "MD5"

            onClicked: {
                hashCalculateManage.calculateMD5();
            }
        }

        JQButton {
            x: 8
            y: 185
            width: 110
            height: 50
            text: "Sha1"

            onClicked: {
                hashCalculateManage.calculateSha1();
            }
        }

        JQButton {
            x: 124
            y: 185
            width: 110
            height: 50
            text: "Sha224"

            onClicked: {
                hashCalculateManage.calculateSha224();
            }
        }

        JQButton {
            x: 8
            y: 231
            width: 110
            height: 50
            text: "Sha256"

            onClicked: {
                hashCalculateManage.calculateSha256();
            }
        }

        JQButton {
            x: 124
            y: 231
            width: 110
            height: 50
            text: "Sha384"

            onClicked: {
                hashCalculateManage.calculateSha384();
            }
        }

        JQButton {
            x: 8
            y: 277
            width: 110
            height: 50
            text: "Sha512"

            onClicked: {
                hashCalculateManage.calculateSha512();
            }
        }

        JQButton {
            x: 124
            y: 277
            width: 110
            height: 50
            text: "Sha3_224"

            onClicked: {
                hashCalculateManage.calculateSha3_224();
            }
        }

        JQButton {
            x: 8
            y: 323
            width: 110
            height: 50
            text: "Sha3_256"

            onClicked: {
                hashCalculateManage.calculateSha3_256();
            }
        }

        JQButton {
            x: 124
            y: 323
            width: 110
            height: 50
            text: "Sha3_384"

            onClicked: {
                hashCalculateManage.calculateSha3_384();
            }
        }

        JQButton {
            x: 8
            y: 369
            width: 110
            height: 50
            text: "Sha3_512"

            onClicked: {
                hashCalculateManage.calculateSha3_512();
            }
        }

        JQButton {
            x: 8
            y: 415
            width: 110
            height: 50
            font.pixelSize: 14
            text: "压缩 & Base64"

            onClicked: {
                hashCalculateManage.compressAndEncodeBase64();
            }
        }

        JQButton {
            x: 124
            y: 415
            width: 110
            height: 50
            font.pixelSize: 14
            text: "解压 & Base64"

            onClicked: {
                hashCalculateManage.decodeBase64AndDecompress();
            }
        }
    }
}
