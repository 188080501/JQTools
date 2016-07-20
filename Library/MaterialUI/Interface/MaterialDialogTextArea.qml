import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles

MaterialDialog {
    id: dialog

    negativeButtonText: ("Cancel")
    positiveButtonText: ("OK")

    Component.onCompleted: {
        dialog.open()
    }

    property var callbackOnCancel: null
    property var callbackOnOK: null

    function show(title, message, currentText, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        textArea.text = currentText;

        materialUI.showDarkBackground();
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK(textArea.text);
        }
    }

    onRejected: {
        materialUI.hideDarkBackground();

        if (callbackOnCancel)
        {
            callbackOnCancel();
        }
    }

    Item {
        width: 300
        height: 300
        clip: true

        Controls.TextArea {
            id: textArea
            x: -5
            y: -5
            width: parent.width + 10
            height: parent.height + 10
            wrapMode: TextInput.WordWrap
            textMargin: 10

            style: ControlStyles.TextAreaStyle {
                selectedTextColor: "#ffffff"
                selectionColor: "#2799f3"
                textColor: "#000000"
            }
        }

        Rectangle {
            x: 1
            y: 1
            width: parent.width - 2
            height: parent.height - 2
            border.color: "#a1a1a1"
            border.width: 1
            color: "#00000000"
        }
    }
}
