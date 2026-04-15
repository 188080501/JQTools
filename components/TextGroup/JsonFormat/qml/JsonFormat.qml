/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import JsonFormat 1.0

Item {
    id: jsonFormat
    width: 620
    height: 540

    function format() {
        var parseErrorMessage = jsonFormatManage.parseErrorString( textFieldForSource.text );
        if ( parseErrorMessage !== "" )
        {
            JQGlobal.showMessage( parseErrorMessage );
            return false;
        }

        targetTextField.text = jsonFormatManage.format( textFieldForSource.text, checkBoxForCompact.checked );
        return true;
    }

    JsonFormatManage {
        id: jsonFormatManage
    }

    Row {
        id: topRow
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 32

        JQCheckBox {
            id: checkBoxForCompact
            anchors.verticalCenter: parent.verticalCenter
            text: "压缩模式"
        }

        JQButton {
            anchors.verticalCenter: parent.verticalCenter
            width: 120
            text: "格式化"

            onClicked: jsonFormat.format();
        }

        JQButton {
            anchors.verticalCenter: parent.verticalCenter
            width: 140
            text: "处理剪贴板"

            onClicked: {
                textFieldForSource.text = jsonFormatManage.clipboardText();
                if ( !jsonFormat.format() ) { return; }
                jsonFormatManage.setClipboardText( targetTextField.text );
                JQGlobal.showMessage( "格式化后的JSON字符串已经复制到剪贴板" );
            }
        }
    }

    JQText {
        text: "源JSON"
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
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: topRow.bottom
        anchors.topMargin: 40
        height: ( jsonFormat.height - topRow.height - 100 ) / 2
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        Flickable {
            anchors.fill: parent
            anchors.margins: 5
            contentWidth: textFieldForSource.paintedWidth
            contentHeight: textFieldForSource.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForSource
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"
                text: "{}"
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
        text: "格式化结果"
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
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        height: ( jsonFormat.height - topRow.height - 90 ) / 2
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        Flickable {
            anchors.fill: parent
            anchors.margins: 5
            contentWidth: targetTextField.paintedWidth
            contentHeight: targetTextField.paintedHeight
            clip: true

            TextEdit {
                id: targetTextField
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"
                readOnly: true
            }
        }

        MouseArea {
            anchors.fill: parent
            visible: !targetTextField.focus

            onClicked: {
                targetTextField.focus = true;
            }
        }
    }
}
