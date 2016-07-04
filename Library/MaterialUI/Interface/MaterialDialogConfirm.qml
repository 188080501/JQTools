import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles

MaterialDialog {
    id: dialog

    negativeButtonText: qsTr("Cancel")
    positiveButtonText: qsTr("OK")

    property var callbackOnCancel: null
    property var callbackOnOK: null

    function show(title, message, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        materialUI.showDarkBackground();
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK();
        }
    }

    onRejected: {
        materialUI.hideDarkBackground();

        if (callbackOnCancel)
        {
            callbackOnCancel();
        }
    }
}
