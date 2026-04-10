/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import TextDedupSort 1.0

Item {
    id: textDedupSort
    width: 620
    height: 540

    function refreshTarget() {
        targetTextField.text = textDedupSortManage.deduplicateAndSort( sourceTextField.text, outputWrapCheckBox.checked );
    }

    TextDedupSortManage {
        id: textDedupSortManage
    }

    Component.onCompleted: {
        textDedupSort.refreshTarget();
    }

    Row {
        id: topRow
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 10

        JQCheckBox {
            id: outputWrapCheckBox
            anchors.verticalCenter: parent.verticalCenter
            checked: true
            text: "输出换行"

            onCheckedChanged: {
                textDedupSort.refreshTarget();
            }
        }

        JQButton {
            width: 120
            text: "处理"

            onClicked: {
                textDedupSort.refreshTarget();
            }
        }

        JQButton {
            width: 120
            text: "处理剪贴板"

            onClicked: {
                sourceTextField.text = textDedupSortManage.clipboardText();
                textDedupSort.refreshTarget();
                textDedupSortManage.setClipboardText( targetTextField.text );
                JQGlobal.showMessage( "文本去重排序结果已经复制到了剪贴板" );
            }
        }

        JQButton {
            width: 120
            text: "复制结果"

            onClicked: {
                textDedupSortManage.setClipboardText( targetTextField.text );
                JQGlobal.showMessage( "文本去重排序结果已经复制到了剪贴板" );
            }
        }

        JQButton {
            width: 120
            text: "清空所有"

            onClicked: {
                sourceTextField.text = "";
                textDedupSort.refreshTarget();
            }
        }
    }

    JQText {
        text: "源文本"
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
        height: ( textDedupSort.height - topRow.height - 100 ) / 2
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
                text: "aabbdddcc中文中文"

                onTextChanged: {
                    textDedupSort.refreshTarget();
                }
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
        text: "去重结果（Unicode码点升序）"
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
        height: ( textDedupSort.height - topRow.height - 90 ) / 2
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
                text: ""
            }
        }
    }
}
