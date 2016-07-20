import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles

MaterialDialog {
    id: dialog

    negativeButtonText: ("Cancel")
    positiveButtonText: ("OK")

    property var callbackOnCancel: null
    property var callbackOnOK: null

    function show(title, message, currentTime, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        if (currentTime)
        {
            timePicker.setIsHours(false);
            timePicker.setDigitsPressed(currentTime.getMinutes());

            timePicker.setIsHours(true);
            timePicker.setDigitsPressed(currentTime.getHours());
        }
        else
        {
            var dateTime = new Date;

            timePicker.setIsHours(false);
            timePicker.setDigitsPressed(dateTime.getMinutes());

            timePicker.setIsHours(true);
            timePicker.setDigitsPressed(dateTime.getHours());
        }

        materialUI.showDarkBackground();
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK( timePicker.getCurrentTime() );
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
        width: timePicker.width
        height: timePicker.height

        MaterialTimePicker {
            id: timePicker
        }
    }
}
