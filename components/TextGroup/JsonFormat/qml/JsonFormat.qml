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

    property string lastCheckedText: ""

    function refreshParseErrorMessage() {
        if ( textFieldForSource.text === lastCheckedText )
        {
            return;
        }

        labelForParseError.text = jsonFormatManage.parseErrorString( textFieldForSource.text );
        lastCheckedText = textFieldForSource.text;
    }

    function format() {
        var parseErrorMessage = jsonFormatManage.parseErrorString( textFieldForSource.text );
        lastCheckedText = textFieldForSource.text;
        if ( parseErrorMessage !== "" )
        {
            labelForParseError.text = parseErrorMessage;
            JQGlobal.showMessage( parseErrorMessage );
            return false;
        }

        textFieldForSource.text = jsonFormatManage.format( textFieldForSource.text, checkBoxForCompact.checked );
        labelForParseError.text = "";
        lastCheckedText = textFieldForSource.text;
        return true;
    }

    JsonFormatManage {
        id: jsonFormatManage
    }

    Timer {
        interval: 1000
        repeat: true
        running: true

        onTriggered: {
            jsonFormat.refreshParseErrorMessage();
        }
    }

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: 55
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
                jsonFormatManage.setClipboardText( textFieldForSource.text );
                JQGlobal.showMessage( "格式化后的JSON字符串已经复制到了剪贴板" );
            }
        }
    }

    JQText {
        id: labelForParseError
        x: 10
        y: 72
        width: jsonFormat.width - 20
        color: "#d32f2f"
        wrapMode: Text.WordWrap
        font.pixelSize: 13
    }

    JQPane {
        z: -1
        anchors.fill: itemForSource
        anchors.margins: -3
    }

    Item {
        id: itemForSource
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 110
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: jsonFormat.width - 20
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
}
