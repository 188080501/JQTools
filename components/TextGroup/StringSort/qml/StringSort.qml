/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import StringSort 1.0

Item {
    id: stringSort
    width: 620
    height: 540

    function sort() {
        sourceTextField.text = stringSortManage.sort( sourceTextField.text, descOrderCheckBox.checked );
        return true;
    }

    StringSortManage {
        id: stringSortManage
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 12

        Row {
            id: topRow
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 32

            JQCheckBox {
                id: descOrderCheckBox
                anchors.verticalCenter: parent.verticalCenter
                text: "降序排序"
            }

            JQButton {
                anchors.verticalCenter: parent.verticalCenter
                width: 120
                text: "排序"

                onClicked: stringSort.sort();
            }

            JQButton {
                width: 140
                anchors.verticalCenter: parent.verticalCenter
                text: "处理剪贴板"

                onClicked: {
                    sourceTextField.text = stringSortManage.clipboardText();
                    if ( !stringSort.sort() ) { return; }
                    stringSortManage.setClipboardText( sourceTextField.text );
                    JQGlobal.showMessage( "排序后的字符串已经复制到了剪贴板" );
                }
            }
        }

        Item {
            id: itemForSource
            width: parent.width
            height: Math.max( 0, parent.height - topRow.height - parent.spacing )
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
                contentWidth: sourceTextField.paintedWidth
                contentHeight: sourceTextField.paintedHeight
                clip: true

                TextEdit {
                    id: sourceTextField
                    width: parent.width
                    height: parent.height
                    selectByMouse: true
                    selectionColor: "#2799f3"
                    text: "JQTools\nQt\nHello\n123\nABC"
                }
            }

            MouseArea {
                anchors.fill: parent
                visible: !sourceTextField.focus

                onClicked: {
                    sourceTextField.focus = true;
                }
            }
        }
    }
}
