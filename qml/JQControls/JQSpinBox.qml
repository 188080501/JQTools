import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

SpinBox {
    id: jqSpinBox
    width: 150
    height: 40
    editable: true
    from: 0
    to: 100
    stepSize: 1
    value: defaultValue
    Material.accent: Material.LightBlue
    up.indicator.visible: stepButtonVisible
    down.indicator.visible: stepButtonVisible

    property int defaultValue: from

    property int          decimals:      0
    readonly property int decimalFactor: Math.pow( 10, decimals )

    property string labelText
    property string suffixText
    property bool stepButtonVisible: true

    readonly property real currentValue: {
        if ( contentItem.focus )
        {
            if ( contentItem.text === "" ) { return 0; }

            return jqSpinBox.valueFromText( contentItem.text, jqSpinBox.locale ) / decimalFactor;
        }

        return value / decimalFactor;
    }

    function addStep(incrementValue) {
        value = Math.min( to, value + incrementValue );
        valueApply();
    }

    function minusStep(incrementValue) {
        value = Math.max( from, value + incrementValue );
        valueApply();
    }

    signal valueApply()

    onValueChanged: {
        if ( !focus ) { return; }

        valueApply();
    }

    Component.onCompleted: {
        contentItem.selectByMouse = true;
    }

    states: [
        State {
            name: "compact"
            when: !stepButtonVisible

            PropertyChanges {
                target: jqSpinBox
                leftPadding: 6
                rightPadding: 6
            }

            PropertyChanges {
                target: up.indicator
                width: 0
                height: 0
            }

            PropertyChanges {
                target: down.indicator
                width: 0
                height: 0
            }
        }
    ]

    MouseArea {
        x: 36
        z: 1
        width: parent.width - x * 2
        height: parent.height
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.PointingHandCursor

        onWheel: (wheel)=>{
            if ( wheel.angleDelta.y > 0 )
            {
                jqSpinBox.addStep( jqSpinBox.stepSize * ( ( wheel.modifiers === Qt.ControlModifier ) ? ( 10 ) : ( 1 ) ) );
            }
            else if ( wheel.angleDelta.y < 0 )
            {
                jqSpinBox.minusStep( -jqSpinBox.stepSize * ( ( wheel.modifiers === Qt.ControlModifier ) ? ( 10 ) : ( 1 ) ) );
            }
        }

        onClicked: {
            forceActiveFocus();
        }
    }

    Text {
        anchors.right: parent.left
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 15
        text: labelText
        color: "#000000"
    }

    Text {
        anchors.left: parent.right
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 15
        text: suffixText
        color: "#000000"
    }
}
