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
import AesCrypt 1.0

Item {
    id: aesCrypt
    width: 620
    height: 540

    property bool changingFlag: false

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
                materialUI.showSnackbarMessage( aesCryptManage.errorString() );
            }
        }
    }

    MaterialButton {
        x: 10
        y: 10
        width: 120
        text: qsTr("AES加密")

        onClicked: {
            aesCryptManage.encryptToBase64();
            if ( aesCryptManage.errorString().length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr("AES-CBC 加密成功") );
            }
        }
    }

    MaterialButton {
        x: 140
        y: 10
        width: 120
        text: qsTr("AES解密")

        onClicked: {
            aesCryptManage.decryptFromBase64();
            if ( aesCryptManage.errorString().length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr("AES-CBC 解密成功") );
            }
        }
    }

    MaterialButton {
        x: 270
        y: 10
        width: 120
        text: qsTr("HMAC计算")

        onClicked: {
            aesCryptManage.calculateHmacSha256ToHex();
            if ( aesCryptManage.errorString().length === 0 )
            {
                materialUI.showSnackbarMessage( qsTr("HMAC-SHA256 计算成功") );
            }
        }
    }

    MaterialButton {
        x: 400
        y: 10
        width: 100
        text: qsTr("输出覆盖输入")

        onClicked: {
            aesCryptManage.moveTargetToSource();
        }
    }

    MaterialButton {
        x: 510
        y: 10
        width: 100
        text: qsTr("清空全部")

        onClicked: {
            aesCryptManage.clear();
        }
    }

    MaterialButton {
        x: 10
        y: 54
        width: 90
        text: qsTr("粘贴输入")

        onClicked: {
            aesCryptManage.pasteSource();
        }
    }

    MaterialButton {
        x: 110
        y: 54
        width: 90
        text: qsTr("粘贴密钥")

        onClicked: {
            aesCryptManage.pasteKey();
        }
    }

    MaterialButton {
        x: 210
        y: 54
        width: 90
        text: qsTr("粘贴IV")

        onClicked: {
            aesCryptManage.pasteIv();
        }
    }

    MaterialButton {
        x: 310
        y: 54
        width: 90
        text: qsTr("复制输出")

        onClicked: {
            aesCryptManage.copyTarget();
            materialUI.showSnackbarMessage( qsTr("已将输出复制到剪贴板") );
        }
    }

    MaterialButton {
        x: 410
        y: 54
        width: 90
        text: qsTr("复制密钥")

        onClicked: {
            aesCryptManage.copyKey();
            materialUI.showSnackbarMessage( qsTr("已将密钥复制到剪贴板") );
        }
    }

    MaterialButton {
        x: 510
        y: 54
        width: 90
        text: qsTr("复制IV")

        onClicked: {
            aesCryptManage.copyIv();
            materialUI.showSnackbarMessage( qsTr("已将 IV 复制到剪贴板") );
        }
    }

    MaterialTextField {
        id: keyTextField
        x: 16
        y: 106
        width: 286
        placeholderText: qsTr("密钥（16/24/32字节）")
        helperText: qsTr("支持 hex: / base64: 前缀，不带前缀按文本处理")

        onTextChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            aesCryptManage.setKey( keyTextField.text );
            aesCrypt.changingFlag = false;
        }
    }

    MaterialTextField {
        id: ivTextField
        x: 316
        y: 106
        width: 286
        placeholderText: qsTr("IV（16字节）")
        helperText: qsTr("支持 hex: / base64: 前缀，不带前缀按文本处理")

        onTextChanged: {
            if ( aesCrypt.changingFlag ) { return; }

            aesCrypt.changingFlag = true;
            aesCryptManage.setIv( ivTextField.text );
            aesCrypt.changingFlag = false;
        }
    }

    MaterialLabel {
        text: qsTr("输入（加密明文 / 解密时 Base64 密文 / HMAC 原文）")
        anchors.bottom: itemForSource.top
        anchors.bottomMargin: 8
        anchors.horizontalCenter: itemForSource.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    RectangularGlow {
        z: -1
        anchors.fill: itemForSource
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    Item {
        id: itemForSource
        x: 10
        y: 230
        width: parent.width - 20
        height: 156
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

    MaterialLabel {
        text: qsTr("输出")
        anchors.bottom: itemForTarget.top
        anchors.bottomMargin: 8
        anchors.horizontalCenter: itemForTarget.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    RectangularGlow {
        z: -1
        anchors.fill: itemForTarget
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    Item {
        id: itemForTarget
        x: 10
        y: 430
        width: parent.width - 20
        height: 156
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
