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
        targetTextField.text = stringSortManage.sort( sourceTextField.text, descOrderCheckBox.checked );
        return true;
    }

    StringSortManage {
        id: stringSortManage
    }

    Row {
        id: topRow
        anchors.top: parent.top
        anchors.topMargin: 10
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
                stringSortManage.setClipboardText( targetTextField.text );
                JQGlobal.showMessage( "排序后的字符串已经复制到剪贴板" );
            }
        }
    }

    JQText {
        text: "源字符串"
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
        height: ( stringSort.height - topRow.height - 100 ) / 2
        clip: true

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

    JQText {
        text: "排序结果"
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
        height: ( stringSort.height - topRow.height - 90 ) / 2
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

    Component.onCompleted: {
        stringSort.sort();
    }
}
