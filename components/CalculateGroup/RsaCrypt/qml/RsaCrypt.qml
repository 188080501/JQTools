/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import RsaCrypt 1.0

Item {
    id: rsaCrypt
    width: 620
    height: 540

    property bool changingFlag: false
    property int panelLabelHeight: 24
    property int panelLabelBottomMargin: 8
    property int panelTopMargin: 130
    property int panelSpacing: 36
    property int panelBottomMargin: 10
    property int panelAreaHeight: height - panelTopMargin - panelBottomMargin - panelSpacing * 2
    property int keyPanelHeight: panelAreaHeight * 2 / 5
    property int sourcePanelHeight: panelAreaHeight * 3 / 10
    property int targetPanelHeight: panelAreaHeight - keyPanelHeight - sourcePanelHeight

    RsaCryptManage {
        id: rsaCryptManage

        onSourceChanged: {
            if ( rsaCrypt.changingFlag ) { return; }

            rsaCrypt.changingFlag = true;
            textFieldForSource.text = rsaCryptManage.source();
            rsaCrypt.changingFlag = false;
        }

        onTargetChanged: {
            if ( rsaCrypt.changingFlag ) { return; }

            rsaCrypt.changingFlag = true;
            textFieldForTarget.text = rsaCryptManage.target();
            rsaCrypt.changingFlag = false;
        }

        onKeyPemChanged: {
            if ( rsaCrypt.changingFlag ) { return; }

            rsaCrypt.changingFlag = true;
            textFieldForKeyPem.text = rsaCryptManage.keyPem();
            rsaCrypt.changingFlag = false;
        }

        onErrorStringChanged: {
            if ( rsaCryptManage.errorString().length > 0 )
            {
                JQGlobal.showMessage( rsaCryptManage.errorString() );
            }
        }
    }

    JQButton {
        x: 10
        y: 10
        width: 120
        text: qsTr("公钥加密")

        onClicked: {
            rsaCryptManage.publicKeyEncryptToBase64();
            if ( rsaCryptManage.errorString().length === 0 )
            {
                JQGlobal.showMessage( qsTr("RSA 公钥加密成功") );
            }
        }
    }

    JQButton {
        x: 140
        y: 10
        width: 120
        text: qsTr("私钥解密")

        onClicked: {
            rsaCryptManage.privateKeyDecryptFromBase64();
            if ( rsaCryptManage.errorString().length === 0 )
            {
                JQGlobal.showMessage( qsTr("RSA 私钥解密成功") );
            }
        }
    }

    JQButton {
        x: 270
        y: 10
        width: 120
        text: qsTr("输出覆盖输入")

        onClicked: {
            rsaCryptManage.moveTargetToSource();
        }
    }

    JQButton {
        x: 400
        y: 10
        width: 100
        text: qsTr("清空全部")

        onClicked: {
            rsaCryptManage.clear();
        }
    }

    JQButton {
        x: 10
        y: 54
        width: 100
        text: qsTr("粘贴输入")

        onClicked: {
            rsaCryptManage.pasteSource();
        }
    }

    JQButton {
        x: 120
        y: 54
        width: 100
        text: qsTr("粘贴密钥")

        onClicked: {
            rsaCryptManage.pasteKeyPem();
        }
    }

    JQButton {
        x: 230
        y: 54
        width: 100
        text: qsTr("复制输出")

        onClicked: {
            rsaCryptManage.copyTarget();
            JQGlobal.showMessage( qsTr("已将输出内容复制到剪贴板") );
        }
    }

    JQButton {
        x: 340
        y: 54
        width: 100
        text: qsTr("复制密钥")

        onClicked: {
            rsaCryptManage.copyKeyPem();
            JQGlobal.showMessage( qsTr("已将密钥复制到剪贴板") );
        }
    }

    JQText {
        text: qsTr("密钥 PEM（公钥加密，私钥解密）")
        height: panelLabelHeight
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: itemForKeyPem.top
        anchors.bottomMargin: panelLabelBottomMargin
        anchors.horizontalCenter: itemForKeyPem.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    JQPane {
        z: -1
        anchors.fill: itemForKeyPem
    }

    Item {
        id: itemForKeyPem
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: panelTopMargin
        height: keyPanelHeight
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
            contentWidth: textFieldForKeyPem.paintedWidth
            contentHeight: textFieldForKeyPem.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForKeyPem
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"

                onTextChanged: {
                    if ( rsaCrypt.changingFlag ) { return; }

                    rsaCrypt.changingFlag = true;
                    rsaCryptManage.setKeyPem( textFieldForKeyPem.text );
                    rsaCrypt.changingFlag = false;
                }
            }
        }

        MouseArea {
            anchors.fill: parent
            visible: !textFieldForKeyPem.focus

            onClicked: {
                textFieldForKeyPem.focus = true;
            }
        }
    }

    JQText {
        text: qsTr("输入内容（解密时请填 Base64 密文）")
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
        anchors.top: itemForKeyPem.bottom
        anchors.topMargin: panelSpacing
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
                    if ( rsaCrypt.changingFlag ) { return; }

                    rsaCrypt.changingFlag = true;
                    rsaCryptManage.setSource( textFieldForSource.text );
                    rsaCrypt.changingFlag = false;
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
        text: qsTr("输出内容")
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
