import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

TextField {
    id: jqTextField
    width: 200
    height: 40
    opacity: enabled ? 1 : 0.5
    leftPadding: 6
    rightPadding: 6
    readOnly: false
    selectByMouse: true
    text: defaultText

    property string defaultText
    property bool copyEnabled: true

    Keys.onPressed: function(event) {
        if (
            !jqTextField.copyEnabled &&
            (
                event.matches(StandardKey.Copy) ||
                event.matches(StandardKey.Cut)
            )
        ) {
            event.accepted = true;
        }
    }
}

