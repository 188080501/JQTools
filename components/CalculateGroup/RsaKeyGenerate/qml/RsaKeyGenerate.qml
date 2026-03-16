/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import RsaKeyGenerate 1.0

Item {
    id: rsaKeyGenerate
    width: 620
    height: 540

    property bool changingFlag: false
    property int keyLabelHeight: 28
    property int keyLabelBottomMargin: 10
    property int keyPanelSpacing: 46
    property int keyPanelTopMargin: 114
    property int keyPanelBottomMargin: 10
    property int keyPanelAreaHeight: height - keyPanelTopMargin - keyPanelBottomMargin - keyPanelSpacing

    RsaKeyGenerateManage {
        id: rsaKeyGenerateManage

        onPublicKeyPemChanged: {
            if ( rsaKeyGenerate.changingFlag ) { return; }

            rsaKeyGenerate.changingFlag = true;
            textFieldForPublicKey.text = rsaKeyGenerateManage.publicKeyPem();
            rsaKeyGenerate.changingFlag = false;
        }

        onPrivateKeyPemChanged: {
            if ( rsaKeyGenerate.changingFlag ) { return; }

            rsaKeyGenerate.changingFlag = true;
            textFieldForPrivateKey.text = rsaKeyGenerateManage.privateKeyPem();
            rsaKeyGenerate.changingFlag = false;
        }

        onErrorStringChanged: {
            if ( rsaKeyGenerateManage.errorString().length > 0 )
            {
                JQGlobal.showMessage( rsaKeyGenerateManage.errorString() );
            }
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: 40
        spacing: 16

        JQText {
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr( "密钥位数：" )
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
        }

        JQComboBox {
            id: menuFieldForKeyBits
            anchors.verticalCenter: parent.verticalCenter
            width: 120
            model: [
                "2048",
                "1024",
                "3072",
                "4096"
            ]
        }

        JQButton {
            anchors.verticalCenter: parent.verticalCenter
            width: 130
            text: qsTr( "生成密钥" )

            onClicked: {
                rsaKeyGenerateManage.generate( menuFieldForKeyBits.currentText );
                if ( rsaKeyGenerateManage.errorString().length === 0 )
                {
                    JQGlobal.showMessage( qsTr( "RSA 密钥生成成功" ) );
                }
            }
        }

        JQButton {
            anchors.verticalCenter: parent.verticalCenter
            width: 130
            text: qsTr( "复制公钥" )

            onClicked: {
                rsaKeyGenerateManage.copyPublicKeyPem();
                JQGlobal.showMessage( qsTr( "已将公钥复制到剪贴板" ) );
            }
        }

        JQButton {
            anchors.verticalCenter: parent.verticalCenter
            width: 130
            text: qsTr( "复制私钥" )

            onClicked: {
                rsaKeyGenerateManage.copyPrivateKeyPem();
                JQGlobal.showMessage( qsTr( "已将私钥复制到剪贴板" ) );
            }
        }
    }

    JQPane {
        z: -1
        anchors.fill: itemForPublicKey
    }

    JQText {
        text: qsTr( "公钥 PEM" )
        height: keyLabelHeight
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: itemForPublicKey.top
        anchors.bottomMargin: keyLabelBottomMargin
        anchors.horizontalCenter: itemForPublicKey.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Item {
        id: itemForPublicKey
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: keyPanelTopMargin
        height: keyPanelAreaHeight * 2 / 5
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
            contentWidth: textFieldForPublicKey.paintedWidth
            contentHeight: textFieldForPublicKey.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForPublicKey
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"
                readOnly: true
            }
        }
    }

    JQPane {
        z: -1
        anchors.fill: itemForPrivateKey
    }

    JQText {
        text: qsTr( "私钥 PEM" )
        height: keyLabelHeight
        verticalAlignment: Text.AlignVCenter
        anchors.bottom: itemForPrivateKey.top
        anchors.bottomMargin: keyLabelBottomMargin
        anchors.horizontalCenter: itemForPrivateKey.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Item {
        id: itemForPrivateKey
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: itemForPublicKey.bottom
        anchors.topMargin: keyPanelSpacing
        height: keyPanelAreaHeight * 3 / 5
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
            contentWidth: textFieldForPrivateKey.paintedWidth
            contentHeight: textFieldForPrivateKey.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForPrivateKey
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"
                readOnly: true
            }
        }
    }
}
