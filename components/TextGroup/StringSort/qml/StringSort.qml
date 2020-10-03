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

    MaterialButton {
        x: 386
        text: "格式化"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: stringSort.sort();
    }

    MaterialButton {
        x: 386
        text: "处理剪切板内容"
        anchors.horizontalCenterOffset: 172
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: {
            sourceTextField.text = stringSortManage.clipboardText();
            if ( !stringSort.sort() ) { return; }
            stringSortManage.setClipboardText( sourceTextField.text );
            materialUI.showSnackbarMessage( "排序后的字符串已经复制到了剪切板" );
        }
    }

    MaterialCheckBox {
        id: descOrderCheckBox
        x: 192
        text: "降序排序"
        anchors.horizontalCenterOffset: -147
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
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
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: stringSort.width - 20
        height: stringSort.height - 110
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
