import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

MaterialDialog {
    id: dialog

    negativeButtonText: qsTr("Cancel")
    positiveButtonText: qsTr("OK")

    positiveButtonEnabled: currentItemIndex !== -1

    property var callbackOnCancel: null
    property var callbackOnOK: null

    property int currentItemIndex
    property string currentItemText
    property var currentItemFlag

    function show(title, message, listData, callbackOnCancel, callbackOnOK) {
        dialog.title = title;
        dialog.text = message;
        dialog.callbackOnCancel = callbackOnCancel;
        dialog.callbackOnOK = callbackOnOK;
        dialog.open();

        currentItemIndex = -1;
        currentItemText = "";
        currentItemFlag = null;

        materialUI.showDarkBackground();

        listModel.clear();
        for (var index = 0; index < listData.length; index++)
        {
            listModel.append({
                                 itemIndex: index,
                                 itemText: listData[index]["text"],
                                 itemFlag: ("flag" in listData[index]) ? (listData[index]["flag"]) : (""),
                                 itemTooltip: ("tooltip" in listData[index]) ? (listData[index]["tooltip"]) : (""),
                                 defaultChecked: ("checked" in listData[index]) ? (listData[index]["checked"]) : (false)
                             });
        }
    }

    onAccepted: {
        materialUI.hideDarkBackground();

        if (callbackOnOK)
        {
            callbackOnOK(currentItemIndex, currentItemText, currentItemFlag);
        }
    }

    onRejected: {
        materialUI.hideDarkBackground();

        if (callbackOnCancel)
        {
            callbackOnCancel();
        }
    }

    ExclusiveGroup{
        id: checkGroup
    }

    ListView {
        id: listView
        x: 0
        y: 55
        width: 270
        height: 150
        clip: true
        boundsBehavior: Flickable.StopAtBounds

        onContentYChanged: {
            slider.value = -1 * contentY;
        }

        delegate: Item {
            width: 270
            height: 50

            Component.onCompleted: {
                if (defaultChecked || (itemIndex === 0))
                {
                    radioButton.checked = true;
                    currentItemIndex = itemIndex;
                    currentItemText = itemText;
                    currentItemFlag = itemFlag;
                }
            }

            MaterialButton {
                anchors.fill: parent
                tooltip: itemTooltip

                elevation: 0

                onClicked: {
                    radioButton.checked = true;
                    currentItemIndex = itemIndex;
                    currentItemText = itemText;
                    currentItemFlag = itemFlag;
                }
            }

            Rectangle {
                x: 10
                y: 49
                width: 270
                height: 1
                color: "#50afafbc"
            }

            MaterialLabel {
                x: 50
                y: 15
                text: itemText
                font.pixelSize: 17
            }

            MaterialRadioButton {
                id: radioButton
                y: 15
                width: 25
                height: 20
                exclusiveGroup: checkGroup
                checked: defaultChecked

                onCheckedChanged: {
                    if ( !checked ) { return; }

                    radioButton.checked = true;
                    currentItemIndex = itemIndex;
                    currentItemText = itemText;
                    currentItemFlag = itemFlag;
                }
            }
        }

        model: ListModel {
            id: listModel
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "#e7e7e7"
            anchors.left: listView.left
            anchors.bottom: listView.bottom
        }

        Rectangle {
            width: parent.width
            height: 1
            color: "#e7e7e7"
            anchors.left: listView.left
            anchors.top: listView.top
        }

        Slider {
            id: slider
            anchors.right: listView.right
            anchors.rightMargin: line.width - 16
            anchors.top: listView.top
            width: 16
            height: listView.height
            minimumValue: -1 * (((listView.contentHeight - listView.height) > 0) ? (listView.contentHeight - listView.height) : (0))
            maximumValue: listModel.count * 0
            orientation: Qt.Vertical
            visible: ((listView.contentHeight - listView.height) > 0) && !materialUI.isSmartPhone()

            onValueChanged: {
                listView.contentY = -1 * value;
            }

            style: SliderStyle {

                groove: Rectangle {
                    color: "#00000000"
                }

                handle: Rectangle {
                    width: 32
                    height: 16
                    color: "#00000000"

                    Rectangle {
                        x: 1
                        y: (height - 2) / 5
                        width: 30
                        height: (control.hovered || control.pressed) ? (12) : (7)
                        color: "#dd666666"
                        implicitWidth: 34
                        implicitHeight: 34
                        radius: height / 2
                        opacity: 0.8

                        onHeightChanged: {
                            line.width = height + 4;
                        }

                        Behavior on height { PropertyAnimation { } }
                    }
                }
            }

            Rectangle {
                id: line
                y: -1
                width: 10
                height: parent.height + 2
                border.color: "#88999999"
                color: "#11999999"
                opacity: (width - 11) / 5
            }
        }
    }
}
