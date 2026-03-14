import QtQuick 2.15
import QtQuick.Controls 2.15
import "./"

Item {
    id: jqLoadingIndicator

    property bool running: true
    property string text
    property bool showText: true
    property int spacing: 8
    property int indicatorSize: 48
    property color textColor: "#000000"

    implicitWidth: jqContentRow.implicitWidth
    implicitHeight: jqContentRow.implicitHeight

    Column {
        id: jqContentRow
        spacing: jqLoadingIndicator.spacing
        anchors.centerIn: parent

        BusyIndicator {
            id: jqIndicator
            width: jqLoadingIndicator.indicatorSize
            height: jqLoadingIndicator.indicatorSize
            running: jqLoadingIndicator.running
        }

        JQText {
            id: jqTextItem
            text: jqLoadingIndicator.text
            color: jqLoadingIndicator.textColor
            visible: jqLoadingIndicator.showText && ( jqLoadingIndicator.text.length > 0 )
            verticalAlignment: Text.AlignVCenter
        }
    }
}


