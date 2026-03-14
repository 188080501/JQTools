import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Pane {
    id: jqPane
    Material.elevation: 2
    Material.background: "#fdfdfd"

    MouseArea {
        anchors.fill: parent

        onClicked: {
            forceActiveFocus();
        }
    }
}
