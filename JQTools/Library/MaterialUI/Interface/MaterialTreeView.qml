import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import "../Element"

TreeView {
    id: tableView
    width: 400
    height: 400
    enabled: modelForTableView.count > -1

    alternatingRowColors: false
    backgroundVisible: false
    headerVisible: true
    sortIndicatorVisible: true
    frameVisible: false

    horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
    verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

    property real itemHeight: 35
    property real headerHeight: 40

    property bool branchEnabled: true

    model: ListModel {
        id: modelForTableView
    }

    style: TreeViewStyle {

        branchDelegate: Label {
            x: 3
            width: 16
            height: 16
            visible: styleData.column === 0 && styleData.hasChildren
            text: styleData.isExpanded ? "\uF1B4" : "\uF1B6"
            color: "#000000"
            font.family: "Material-Design-Iconic-Font"
            font.pixelSize: 18
            renderType: Text.NativeRendering

            MouseArea {
                anchors.fill: parent
                visible: !branchEnabled
            }
        }
    }

    headerDelegate: Rectangle {
        width: 80
        height: headerHeight
        color: "#ffffff"
        radius: 3

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: "#00000000"
            border.width: 1
            border.color: "#e1e1e1"
        }

        Label {
            anchors.fill: parent
            text: styleData.value
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#606060"

            font.family: {
                switch (Qt.platform.os)
                {
                    case "windows": return "微软雅黑";
                    default: return "Roboto";
                }
            }
        }
    }

    itemDelegate: Rectangle {
        color: (styleData.selected) ? ("#f3f3f3") : ("#00000000")

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: "#00000000"
            border.width: 1
            border.color: "#e1e1e1"
        }

        Label {
            id: label
            anchors.fill: parent
            clip: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#000000"
            font.pixelSize: 14
            elide: Text.ElideRight

            font.family: {
                switch (Qt.platform.os)
                {
                    case "windows": return "微软雅黑";
                    default: return "Roboto";
                }
            }
        }

        Connections {
            target: styleData

            onValueChanged: {
                if (((typeof styleData.value) !== "string") && ((typeof styleData.value) !== "number")) { return; }

                label.text = styleData.value;
            }
        }
    }

    rowDelegate: Item {
        height: itemHeight
    }

    function appendText(texts) {
        var buf = new Object;
        for (var index = 0; index < texts.length; index++)
        {
            buf["text" + index] = texts[index];
        }
        model.append(buf)
    }

    RectangularGlow {
        x: 0
        y: 1
        z: -1
        width: parent.width
        height: parent.height
        glowRadius: 2
        spread: 0.22
        color: "#30000000"
        cornerRadius: 3
    }

    Rectangle {
        z: -1
        id: rectangleForBacaground
        anchors.fill: parent
        color: "#ffffff"
        radius: 3
    }
}
