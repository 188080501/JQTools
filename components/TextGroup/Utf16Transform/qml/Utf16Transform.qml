/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import Utf16Transform 1.0

Item {
    id: utf16Transform
    width: 620
    height: 540

    property bool changingFlag: false

    Utf16TransformManage {
        id: utf16TransformManage
    }

    Row {
        id: topRow
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 12

        JQText {
            anchors.verticalCenter: parent.verticalCenter
            text: "Unicode 转义转换工具，可将文本和 \\uXXXX 互转\n例如将 “中文” 与 “\\u4E2D\\u6587” 互转"
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            width: 50
            height: 1
        }

        JQButton {
            id: processClipboardButton
            width: 140
            text: "处理剪贴板"
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                textFieldForSource.text = utf16TransformManage.clipboardText();
                utf16TransformManage.setClipboardText( textFieldForTarget.text );
                JQGlobal.showMessage( "Unicode 转义字符串已经复制到剪贴板" );
            }
        }
    }

    JQText {
        text: "文本字符串"
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
        height: ( utf16Transform.height - topRow.height - 100 ) / 2
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

                onTextChanged: {
                    if ( utf16Transform.changingFlag ) { return; }

                    utf16Transform.changingFlag = true;

                    textFieldForTarget.text = utf16TransformManage.encodeToUnicodeEscape( textFieldForSource.text );

                    utf16Transform.changingFlag = false;
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
        text: "Unicode转义字符串"
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
        height: ( utf16Transform.height - topRow.height - 90 ) / 2
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        Flickable {
            anchors.fill: parent
            anchors.margins: 5
            contentWidth: textFieldForTarget.paintedWidth
            contentHeight: textFieldForTarget.paintedHeight
            clip: true

            TextEdit {
                id: textFieldForTarget
                width: parent.width
                height: parent.height
                selectByMouse: true
                selectionColor: "#2799f3"

                onTextChanged: {
                    if ( utf16Transform.changingFlag ) { return; }

                    utf16Transform.changingFlag = true;

                    textFieldForSource.text = utf16TransformManage.decodeFromUnicodeEscape( textFieldForTarget.text );

                    utf16Transform.changingFlag = false;
                }
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
}
