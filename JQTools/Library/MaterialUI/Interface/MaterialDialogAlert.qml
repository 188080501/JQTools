import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles

MaterialDialog {
    id: dialog

    negativeButtonText: ""
    positiveButtonText: qsTr("OK")

    property var callbackOnOK: null

    function show(title, message, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        materialUI.showDarkBackground(function() {
            dialog.close();
            materialUI.hideDarkBackground();

            if (dialog.callbackOnOK)
            {
                dialog.callbackOnOK();
            }
        });
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

        if (callbackOnOK)
        {
            callbackOnOK();
        }
    }
}
