import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtGraphicalEffects 1.0
import "../Element"

Controls.TableView {
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

    property real headerHeight: 40
    property real itemHeight: 35

    property real rectangularGlowCornerRadius: 3

    model: ListModel {
        id: modelForTableView
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

        Controls.Label {
            anchors.fill: parent
            text: styleData.value
            font.pixelSize: 15
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#606060"
            elide: Text.ElideRight

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
        id: itemForTableView
        color: (styleData.selected) ? ("#f3f3f3") : ("#00000000")

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 1
            color: "#00000000"
            border.width: 1
            border.color: "#e1e1e1"
        }

        Controls.Label {
            anchors.fill: parent
            text: styleData.value
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: "#000000"
            font.pixelSize: 13
            elide: Text.ElideRight

            font.family: {
                switch (Qt.platform.os)
                {
                    case "windows": return "微软雅黑";
                    default: return "Roboto";
                }
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
        modelForTableView.append(buf)
    }

    function setText(row, texts) {
        if (modelForTableView.count <= row)
        {
            appendText(texts);
        }
        else
        {
            for (var index = 0; index < texts.length; index++)
            {
                modelForTableView.get(row)["text" + index] = texts[index];
            }
        }
    }

    function clear() {
        modelForTableView.clear();
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
    }

    Rectangle {
        z: -1
        id: rectangleForBacaground
        anchors.fill: parent
        color: "#ffffff"
        radius: tableView.rectangularGlowCornerRadius
    }
}
