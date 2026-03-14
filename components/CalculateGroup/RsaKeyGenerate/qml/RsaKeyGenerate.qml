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
import RsaKeyGenerate 1.0
import JQControls 1.0

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
                materialUI.showSnackbarMessage( rsaKeyGenerateManage.errorString() );
            }
        }
    }

    MaterialLabel {
        x: 20
        y: 18
        text: "\u5BC6\u94A5\u4F4D\u6570\uFF1A"
        font.pixelSize: 16
        height: 56
        verticalAlignment: Text.AlignVCenter
    }

    MaterialMenuField {
        id: menuFieldForKeyBits
        x: 95
        y: 19
        width: 120
        model: [
            "2048",
            "1024",
            "3072",
            "4096"
        ]
    }

    MaterialButton {
        x: 230
        y: 26
        width: 120
        text: "\u751F\u6210\u5BC6\u94A5"

        onClicked: {
            rsaKeyGenerateManage.generate( menuFieldForKeyBits.selectedText );
            if ( rsaKeyGenerateManage.errorString().length === 0 )
            {
                materialUI.showSnackbarMessage( "RSA \u5BC6\u94A5\u751F\u6210\u6210\u529F" );
            }
        }
    }

    MaterialButton {
        x: 370
        y: 26
        width: 100
        text: "\u590D\u5236\u516C\u94A5"

        onClicked: {
            rsaKeyGenerateManage.copyPublicKeyPem();
            materialUI.showSnackbarMessage( "\u5DF2\u5C06\u516C\u94A5\u590D\u5236\u5230\u526A\u8D34\u677F" );
        }
    }

    MaterialButton {
        x: 485
        y: 26
        width: 100
        text: "\u590D\u5236\u79C1\u94A5"

        onClicked: {
            rsaKeyGenerateManage.copyPrivateKeyPem();
            materialUI.showSnackbarMessage( "\u5DF2\u5C06\u79C1\u94A5\u590D\u5236\u5230\u526A\u8D34\u677F" );
        }
    }

    RectangularGlow {
        z: -1
        anchors.fill: itemForPublicKey
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    MaterialLabel {
        text: "\u516C\u94A5 PEM"
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

    RectangularGlow {
        z: -1
        anchors.fill: itemForPrivateKey
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    MaterialLabel {
        text: "\u79C1\u94A5 PEM"
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
