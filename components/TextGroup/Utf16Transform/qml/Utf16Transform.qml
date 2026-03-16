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

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 12

        Row {
            id: topRow
            width: parent.width
            spacing: 12

            JQText {
                width: topRow.width - processClipboardButton.width - topRow.spacing
                text:
"Unicode 转义转换工具，可以将文本和 \\uXXXX 之间互转
例如将 “中文” 与 “\\u4E2D\\u6587” 互转"
                verticalAlignment: Text.AlignVCenter
            }

            JQButton {
                id: processClipboardButton
                width: 140
                text: "处理剪贴板"
                anchors.verticalCenter: parent.verticalCenter

                onClicked: {
                    textFieldForSource.text = utf16TransformManage.clipboardText();
                    utf16TransformManage.setClipboardText( textFieldForTarget.text );
                    JQGlobal.showMessage( "Unicode 转义字符串已经复制到了剪贴板" );
                }
            }
        }

        Row {
            id: titleRow
            width: parent.width
            spacing: 20

            JQText {
                width: ( titleRow.width - titleRow.spacing ) / 2
                text: "文本字符串"
                horizontalAlignment: Text.AlignHCenter
            }

            JQText {
                width: ( titleRow.width - titleRow.spacing ) / 2
                text: "Unicode转义字符串"
                horizontalAlignment: Text.AlignHCenter
            }
        }

        Row {
            id: editorRow
            width: parent.width
            height: Math.max( 0, parent.height - topRow.height - titleRow.height - parent.spacing * 2 )
            spacing: 20

            Item {
                id: itemForSource
                width: ( editorRow.width - editorRow.spacing ) / 2
                height: editorRow.height
                clip: true

                JQPane {
                    z: -1
                    anchors.fill: parent
                    anchors.margins: -3
                }

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

            Item {
                id: itemForTarget
                width: ( editorRow.width - editorRow.spacing ) / 2
                height: editorRow.height
                clip: true

                JQPane {
                    z: -1
                    anchors.fill: parent
                    anchors.margins: -3
                }

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
    }
}
