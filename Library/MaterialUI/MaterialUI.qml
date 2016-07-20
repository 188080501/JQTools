import QtQuick 2.5
import "./Element"
import "./Interface"

Item {
    id: materialUI

    // Theme.qml

    property color primaryColor: "#FAFAFA"

    /*!
       A darker version of the primary color used for the window titlebar (if client-side
       decorations are not used), unless a \l Page specifies its own primary and primary dark
       colors. This can be customized via the \l ApplicationWindow::theme group property. According
       to the Material Design guidelines, this should normally be the 700 color version of your
       aplication's primary color, taken from one of the color palettes at
       \l {http://www.google.com/design/spec/style/color.html#color-color-palette}.
    */
    property color primaryDarkColor: Qt.rgba(0,0,0, 0.54)

    /*!
       The accent color complements the primary color, and is used for any primary action buttons
       along with switches, sliders, and other components that do not specifically set a color.
       This can be customized via the  \l ApplicationWindow::theme group property. According
       to the Material Design guidelines, this should taken from a second color palette that
       complements the primary color palette at
       \l {http://www.google.com/design/spec/style/color.html#color-color-palette}.
    */
    property color accentColor: "#2196F3"

    /*!
       The default background color for the application.
     */
    property color backgroundColor: "#f3f3f3"

    /*!
       The color of the higlight indicator for selected tabs. By default this is the accent color,
       but it can also be white (for a dark primary color/toolbar background).
     */
    property color tabHighlightColor: accentColor

    /*!
       Standard colors specifically meant for light surfaces. This includes text colors along with
       a light version of the accent color.
     */
    property ThemePalette light: ThemePalette {
        light: true
    }

    /*!
       Standard colors specifically meant for dark surfaces. This includes text colors along with
       a dark version of the accent color.
    */
    property ThemePalette dark: ThemePalette {
        light: false
    }

    /*!
       A utility method for changing the alpha on colors. Returns a new object, and does not modify
       the original color at all.
     */
    function alpha(color, alpha) {
        var realColor = Qt.darker(color, 1)
        realColor.a = alpha
        return realColor
    }

    /*!
       Select a color depending on whether the background is light or dark.

       \c lightColor is the color used on a light background.

       \c darkColor is the color used on a dark background.
     */
    function lightDark(background, lightColor, darkColor) {
        return isDarkColor(background) ? darkColor : lightColor
    }

    /*!
       Returns true if the color is dark and should have light content on top
     */
    function isDarkColor(background) {
        var temp = Qt.darker(background, 1)

        var a = 1 - ( 0.299 * temp.r + 0.587 * temp.g + 0.114 * temp.b);

        return temp.a > 0 && a >= 0.3
    }

    // Other
    property alias loadingVisible: progressCircle.visible

    property var onDarkBackgroundClicked: null
    property var onStealthBackgroundClicked: null
    property var stealthBackgroundFilterItem: null

    property var swipeToRefreshOnRefreshCallback: null
    property var swipeToRefreshOnCancelCallback: null
    property var swipeToRefreshOnCompleted: null

    property string materialFontName: "Material-Design-Iconic-Font"

    property string dialogOKText: ("OK")
    property string dialogCancelText: ("Cancel")

    function isSmartPhone() {
        return (Qt.platform.os === "ios") || (Qt.platform.os === "android");
    }

    function addSwipeToRefresh(listModel, onRefreshCallback, onCancelCallback, onCompleted) {
        listModel.insert(0,
                         {
                             type: "component",
                             source: "qrc:/MaterialUI/Interface/MaterialSwipeToRefresh.qml"
                         });

        swipeToRefreshOnRefreshCallback = onRefreshCallback;
        swipeToRefreshOnCancelCallback = onCancelCallback;
        swipeToRefreshOnCompleted = onCompleted;
    }

    function showDialogAlert(title, message, callbackOnOK) {
        if (!loaderForDialogAlert.active)
        {
            loaderForDialogAlert.active = true;
            loaderForDialogAlert.item.positiveButtonText = materialUI.dialogOKText;
        }

        loaderForDialogAlert.item.show(title, message, callbackOnOK);
    }

    function showDialogConfirm(title, message, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogConfirm.active)
        {
            loaderForDialogConfirm.active = true;
            loaderForDialogConfirm.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogConfirm.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogConfirm.item.show(title, message, callbackOnCancel, callbackOnOK);
    }

    function showDialogPrompt(title, message, placeholderText, currentText, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogPrompt.active)
        {
            loaderForDialogPrompt.active = true;
            loaderForDialogPrompt.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogPrompt.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogPrompt.item.show(title, message, placeholderText, currentText, callbackOnCancel, callbackOnOK);
    }

    function showDialogTextArea(title, message, currentText, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogTextArea.active)
        {
            loaderForDialogTextArea.active = true;
            loaderForDialogTextArea.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogTextArea.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogTextArea.item.show(title, message, currentText, callbackOnCancel, callbackOnOK);
    }

    function showDialogScrolling(title, message, listData, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogScrolling.active)
        {
            loaderForDialogScrolling.active = true;
            loaderForDialogScrolling.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogScrolling.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogScrolling.item.show(title, message, listData, callbackOnCancel, callbackOnOK);
    }

    function showDialogDatePicker(title, message, currentDate, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogDatePicker.active)
        {
            loaderForDialogDatePicker.active = true;
            loaderForDialogDatePicker.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogDatePicker.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogDatePicker.item.show(title, message, currentDate, callbackOnCancel, callbackOnOK);
    }

    function showDialogTimePicker(title, message, currentTime, callbackOnCancel, callbackOnOK) {
        if (!loaderForDialogTimePicker.active)
        {
            loaderForDialogTimePicker.active = true;
            loaderForDialogTimePicker.item.positiveButtonText = materialUI.dialogOKText;
            loaderForDialogTimePicker.item.negativeButtonText = materialUI.dialogCancelText;
        }

        loaderForDialogTimePicker.item.show(title, message, currentTime, callbackOnCancel, callbackOnOK);
    }

    function showBottomActionSheet(title, sheetData, callbackOnCancel, callbackOnOK) {
        actionSheet.show(title, sheetData, callbackOnCancel, callbackOnOK);
    }

    function showDarkBackground(onDarkBackgroundClicked) {
        darkBackground.opacity = 1;

        switch (arguments.length)
        {
            case 1:
                materialUI.onDarkBackgroundClicked = onDarkBackgroundClicked;
                break;
            default:
                materialUI.onDarkBackgroundClicked = null;
                break;
        }
    }

    function showStealthBackground(onStealthBackgroundClicked, stealthBackgroundFilterItem) {
        stealthBackground.opacity = 1;

        switch (arguments.length)
        {
            case 2:
                materialUI.stealthBackgroundFilterItem = stealthBackgroundFilterItem;
            case 1:
                materialUI.onStealthBackgroundClicked = onStealthBackgroundClicked;
                break;
            default:
                materialUI.onStealthBackgroundClicked = null;
                break;
        }
    }

    function hideDarkBackground() {
        darkBackground.opacity = 0;
    }

    function hideStealthBackground() {
        stealthBackground.opacity = 0;
    }

    function showSnackbarMessage(message) {
        snackbar.open(message);
    }

    function showLoading(text, callbackOnClicked) {
        progressCircle.visible = true;

        switch (arguments.length)
        {
            case 1:
            case 2:
                labelProgressCircle.text = text;
                break;
            default:
                labelProgressCircle.text = "";
                break;
        }

        showDarkBackground((arguments.length == 2) ? (callbackOnClicked) : (null));
    }

    function hideLoading() {
        progressCircle.visible = false;

        hideDarkBackground();
    }

    Rectangle {
        id: darkBackground
        anchors.fill: parent
        color: "#55000000"
        visible: opacity !== 0
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 500; easing.type: Easing.OutCubic }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons

            onClicked: {
                if (materialUI.onDarkBackgroundClicked)
                {
                    materialUI.onDarkBackgroundClicked();
                }
            }
        }
    }

    Rectangle {
        id: stealthBackground
        anchors.fill: parent
        color: "#00000000"
        visible: opacity !== 0
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 500; easing.type: Easing.OutCubic }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton

            onPressed: {
                if (materialUI.stealthBackgroundFilterItem)
                {
                    var item = materialUI.stealthBackgroundFilterItem;
                    var currentX = item.x;
                    var currentY = item.y;
                    var parent = item.parent;

                    while (parent && ("x" in parent))
                    {
                        currentX += parent.x;
                        currentY += parent.y;
                        parent = parent.parent;
                    }

                    if (((mouseX > currentX) && (mouseX < (currentX + item.width))) &&
                       ((mouseY > currentY) && (mouseY < (currentY + item.height))))
                    {
                        mouse.accepted = false;
                    }
                }
            }

            onClicked: {
                if (materialUI.onStealthBackgroundClicked)
                {
                    materialUI.onStealthBackgroundClicked();
                }
            }
        }
    }

    MaterialProgressCircle {
        id: progressCircle
        width: 40
        height: 40
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -20
        indeterminate: parent.visible
        autoChangeColor: parent.visible
        visible: false

        MaterialLabel {
            id: labelProgressCircle
            anchors.top: parent.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
        }
    }

    MaterialBottomActionSheet {
        id: actionSheet
    }

    MaterialSnackbar {
        id: snackbar
    }

    FontLoader {
        id: materialFont
        source: "qrc:/MaterialUI/Material-Design-Iconic-Font.ttf"
    }

    Loader {
        id: loaderForDialogAlert
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogAlert.qml"
        active: false
    }

    Loader {
        id: loaderForDialogConfirm
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogConfirm.qml"
        active: false
    }

    Loader {
        id: loaderForDialogPrompt
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogPrompt.qml"
        active: false
    }

    Loader {
        id: loaderForDialogTextArea
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogTextArea.qml"
        active: false
    }

    Loader {
        id: loaderForDialogScrolling
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogScrolling.qml"
        active: false
    }

    Loader {
        id: loaderForDialogDatePicker
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogDatePicker.qml"
        active: false
    }

    Loader {
        id: loaderForDialogTimePicker
        anchors.centerIn: parent
        source: "qrc:/MaterialUI/Interface/MaterialDialogTimePicker.qml"
        active: false
    }
}
