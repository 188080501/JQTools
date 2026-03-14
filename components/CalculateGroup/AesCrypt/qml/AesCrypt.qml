/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import AesCrypt 1.0

Item {
    id: aesCrypt
    width: 620
    height: 540

    property bool changingFlag: false
    property int panelLabelHeight: 24
    property int panelLabelBottomMargin: 8
    property int panelTopMargin: 200
    property int panelSpacing: 36
    property int panelBottomMargin: 10
    property int panelAreaHeight: height - panelTopMargin - panelBottomMargin - panelSpacing
    property int sourcePanelHeight: panelAreaHeight / 2
    property int targetPanelHeight: panelAreaHeight - sourcePanelHeight

    AesCryptManage {
        id: aesCryptManage

        onSourceChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            textFieldForSource.text = aesCryptManage.source();
            aesCrypt.changingFlag = false;
        }

        onTargetChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            textFieldForTarget.text = aesCryptManage.target();
            aesCrypt.changingFlag = false;
        }

        onKeyChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            keyTextField.text = aesCryptManage.key();
            aesCrypt.changingFlag = false;
        }

        onIvChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            ivTextField.text = aesCryptManage.iv();
            aesCrypt.changingFlag = false;
        }

        onErrorStringChanged: {
            if ( aesCryptManage.errorString().length > 0 )
            {
                JQGlobal.showMessage( aesCryptManage.errorString() );
            }
        }
    }

    JQButton {
        x: 10
        y: 10
        width: 120
        text: qsTr("AES加密")

        onClicked: {
            aesCryptManage.encryptToBase64();
            if ( aesCryptManage.errorString().length === 0 )
            {
                JQGlobal.showMessage( qsTr("AES-CBC 加密成功") );
            }
        }
    }

    JQButton {
        x: 140
        y: 10
        width: 120
        text: qsTr("AES解密")

        onClicked: {
            aesCryptManage.decryptFromBase64();
            if ( aesCryptManage.errorString().length === 0 )
            {
                JQGlobal.showMessage( qsTr("AES-CBC 解密成功") );
            }
        }
    }

    JQButton {
        x: 270
        y: 10
        width: 120
        text: qsTr("HMAC计算")

        onClicked: {
            aesCryptManage.calculateHmacSha256ToHex();
            if ( aesCryptManage.errorString().length === 0 )
            {
                JQGlobal.showMessage( qsTr("HMAC-SHA256 计算成功") );
            }
        }
    }

    JQButton {
        x: 400
        y: 10
        width: 100
        text: qsTr("输出覆盖输入")

        onClicked: {
            aesCryptManage.moveTargetToSource();
        }
    }

    JQButton {
        x: 510
        y: 10
        width: 100
        text: qsTr("清空全部")

        onClicked: {
            aesCryptManage.clear();
        }
    }

    JQButton {
        x: 10
        y: 64
        width: 90
        text: qsTr("粘贴输入")

        onClicked: {
            aesCryptManage.pasteSource();
        }
    }

    JQButton {
        x: 110
        y: 64
        width: 90
        text: qsTr("粘贴密钥")

        onClicked: {
            aesCryptManage.pasteKey();
        }
    }

    JQButton {
        x: 210
        y: 64
        width: 90
        text: qsTr("粘贴IV")

        onClicked: {
            aesCryptManage.pasteIv();
        }
    }

    JQButton {
        x: 310
        y: 64
        width: 90
        text: qsTr("复制输出")

        onClicked: {
            aesCryptManage.copyTarget();
            JQGlobal.showMessage( qsTr("已将输出复制到剪贴板") );
        }
    }

    JQButton {
        x: 410
        y: 64
        width: 90
        text: qsTr("复制密钥")

        onClicked: {
            aesCryptManage.copyKey();
            JQGlobal.showMessage( qsTr("已将密钥复制到剪贴板") );
        }
    }

    JQButton {
        x: 510
        y: 64
        width: 90
        text: qsTr("复制IV")

        onClicked: {
            aesCryptManage.copyIv();
            JQGlobal.showMessage( qsTr("已将 IV 复制到剪贴板") );
        }
    }

    JQTextField {
        id: keyTextField
        x: 16
        y: 106
        width: 286
        placeholderText: qsTr("密钥（16/24/32字节）")

        onTextChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            aesCryptManage.setKey( keyTextField.text );
            aesCrypt.changingFlag = false;
        }
    }

    JQTextField {
        id: ivTextField
        x: 316
        y: 106
        width: 286
        placeholderText: qsTr("IV（16字节）")

        onTextChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            aesCryptManage.setIv( ivTextField.text );
            aesCrypt.changingFlag = false;
        }
    }

    JQText {
        text: qsTr("输入（加密明文 / 解密时 Base64 密文 / HMAC 原文）")
        height: panelLabelHeight
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: itemForSource.top
        anchors.bottomMargin: panelLabelBottomMargin
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
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: panelTopMargin
        height: sourcePanelHeight
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
                    if ( aesCrypt.changingFlag ) { return; }

                    aesCrypt.changingFlag = true;
                    aesCryptManage.setSource( textFieldForSource.text );
                    aesCrypt.changingFlag = false;
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
        text: qsTr("输出")
        height: panelLabelHeight
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: itemForTarget.top
        anchors.bottomMargin: panelLabelBottomMargin
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
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: itemForSource.bottom
        anchors.topMargin: panelSpacing
        height: targetPanelHeight
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
                readOnly: true
            }
        }
    }
}
