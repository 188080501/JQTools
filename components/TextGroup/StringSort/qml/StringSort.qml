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

    Row {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        anchors.verticalCenterOffset: 55
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
        width: stringSort.width - 20
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
