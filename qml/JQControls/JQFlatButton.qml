import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

MouseArea {
    id: jqFlatButton
    width: 70
    height: 35

    property alias text:  jqLabel.text
    property alias color: jqLabel.color

    property alias borderColor: jqRect.border.color

    Rectangle {
        id: jqRect
        anchors.fill: parent
        z: -1
        border.color: "#a1a1a1"
        border.width: 1
        radius: 4
        color: {
            if ( jqFlatButton.pressed ) { return "#e0e0e0"; }

            return "#ffffff";
        }

        Behavior on color { ColorAnimation { duration: 200 } }
    }

    Text {
        id: jqLabel
        anchors.centerIn: parent
        font.pixelSize: 13
        color: "#000000"
    }
}


