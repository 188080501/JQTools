import QtQuick 2.15

Item {
    id: jqSnakeBar
    x: 30
    y: ( parent ) ? ( parent.height - height ) : ( 0 )
    z: 999
    width: jqLabel.contentWidth + 50
    height: jqLabel.contentHeight + 30

    property alias text: jqLabel.text

    BorderImage {
        x: -18
        width: parent.width + 18 + 19
        height: parent.height + 41
        border.left: 25
        border.right: 25
        border.top: 5
        border.bottom: 50
        source: "qrc:/jqcontrolsimages/JQSnakeBar/Frame.png"
    }

    MouseArea {
        id: jqMouseArea
        anchors.fill: parent
        hoverEnabled: true
    }

    TextEdit {
        id: jqLabel
        x: 25
        y: 15
        enabled: false
        width: 400
        wrapMode: TextEdit.Wrap
    }

    SequentialAnimation {
        running: true

        NumberAnimation {
            target: jqSnakeBar
            property: "y"
            to: parent.height - height - 30
            easing.type: Easing.OutQuad
            duration: 250
        }
    }

    SequentialAnimation {
        running: !jqMouseArea.containsMouse

        PauseAnimation {
            duration: 4000
        }

        ParallelAnimation {

            NumberAnimation {
                target: jqSnakeBar
                property: "opacity"
                to: 0
                duration: 250
            }

            NumberAnimation {
                target: jqSnakeBar
                property: "scale"
                to: 0.8
                easing.type: Easing.InQuad
                duration: 250
            }
        }

        ScriptAction {

            script: {
                jqSnakeBar.destroy();
            }
        }
    }
}
