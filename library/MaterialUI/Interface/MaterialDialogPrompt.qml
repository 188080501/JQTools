import QtQuick 2.5
import QtQuick.Layouts 1.1

MaterialDialog {
    id: dialog

    negativeButtonText: ("Cancel")
    positiveButtonText: ("OK")

    property var callbackOnCancel: null
    property var callbackOnOK: null

    function show(title, message, placeholderText, currentText, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        textField.placeholderText = placeholderText;
        textField.text = currentText;

        materialUI.showDarkBackground();
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK(textField.text);
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
        width: parent.width
        height: 64

        MaterialTextField {
            id: textField
            y: 0
            z: 2
            width: parent.width
            height: 56
        }
    }
}
