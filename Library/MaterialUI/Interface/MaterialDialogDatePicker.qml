import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles

MaterialDialog {
    id: dialog

    negativeButtonText: qsTr("Cancel")
    positiveButtonText: qsTr("OK")

    property var callbackOnCancel: null
    property var callbackOnOK: null

    function show(title, message, currentDate, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        if (currentDate)
        {
            datePicker.selectedDate = currentDate;
        }
        else
        {
            datePicker.selectedDate = new Date;
        }

        materialUI.showDarkBackground();
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK( datePicker.selectedDate );
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
        width: datePicker.width
        height: datePicker.height

        MaterialDatePicker {
            id: datePicker
        }
    }
}
