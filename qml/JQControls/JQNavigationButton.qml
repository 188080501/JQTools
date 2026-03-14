import QtQuick 2.15
import QtQuick.Controls.Material 2.15
import JQControls 1.0

Item {
    id: jqNavigationButton
    width: 80
    height: 90

    property string text
    property url    iconSource

    signal clicked()

    JQButton {
        anchors.fill: parent
        flat: true
        Material.elevation: 0
        Material.background: Material.White

        onClicked: {
            jqNavigationButton.clicked();
        }

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -12
            width: 50
            height: 50
            source: jqNavigationButton.iconSource
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 25
            font.pixelSize: 15
            color: "#111111"
            text: jqNavigationButton.text
        }
    }
}

