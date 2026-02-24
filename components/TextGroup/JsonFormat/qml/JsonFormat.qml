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
            materialUI.showSnackbarMessage( parseErrorMessage );
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

    MaterialButton {
        x: 386
        text: "格式化"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: jsonFormat.format();
    }

    MaterialButton {
        x: 386
        text: "处理剪贴板内容"
        anchors.horizontalCenterOffset: 172
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: {
            textFieldForSource.text = jsonFormatManage.clipboardText();
            if ( !jsonFormat.format() ) { return; }
            jsonFormatManage.setClipboardText( textFieldForSource.text );
            materialUI.showSnackbarMessage( "格式化后的JSON字符串已经复制到了剪贴板" );
        }
    }

    MaterialCheckBox {
        id: checkBoxForCompact
        x: 192
        text: "压缩模式"
        anchors.horizontalCenterOffset: -147
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MaterialLabel {
        id: labelForParseError
        x: 10
        y: 72
        width: jsonFormat.width - 20
        color: "#d32f2f"
        wrapMode: Text.WordWrap
        font.pixelSize: 13
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
