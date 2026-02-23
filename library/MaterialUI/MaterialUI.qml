import QtQuick 2.5
import "./Interface"

Item {
    id: materialUI

    // Other
    property var onDarkBackgroundClicked: null
    property var onStealthBackgroundClicked: null
    property var stealthBackgroundFilterItem: null

    property string dialogOKText: "OK"
    property string dialogCancelText: "Cancel"

    function isSmartPhone() {
        return (Qt.platform.os === "ios") || (Qt.platform.os === "android");
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
                labelForProgressCircle.text = text;
                break;
            default:
                labelForProgressCircle.text = "";
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
            id: labelForProgressCircle
            anchors.top: parent.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 15
            horizontalAlignment: Text.AlignHCenter
        }
    }

    MaterialSnackbar {
        id: snackbar
    }

}
