import QtQuick 2.5
import QtQuick.Layouts 1.1
import "qrc:/MaterialUI/Element/"

Item {
    id: materialTabbed
    width: 40
    height: 40

    property int itemWidth: 100

    property alias model: listView.model
    property var iconDatas

    property alias textColor: button.textColor
    property alias backgroundColor: button.backgroundColor

    readonly property string selectedText: (listView.currentItem) ? (listView.currentItem.text) : ("")
    property alias selectedIndex: listView.currentIndex
    property int maxVisibleItems: 4

    signal itemSelected(int index, string text);

    MaterialActionButton {
        id: button
        anchors.fill: parent
        elevation: 0
        textFontFamily: "Material-Design-Iconic-Font"
        text: "\uF2A3"
        textSize: 22

        onClicked: {
            dropdown.open(this, -8, 8);
        }

        Dropdown {
            id: dropdown
            width: itemWidth
            height: Math.min(maxVisibleItems * (48) + (24), listView.height)

            ListView {
                id: listView

                width: dropdown.width
                height: Math.min(count > 0 ? contentHeight : 0, 4.5 * (48));

                interactive: true

                delegate: Standard {
                    id: delegateItem
                    text: modelData

                    onClicked: {
                        listView.currentIndex = index;
                        dropdown.close();
                        itemSelected(index, listView.currentItem.text);
                    }

                    Text {
                        id: labelForIcon
                        anchors.verticalCenter: parent.verticalCenter
                        color: "#000000"
                        visible: text !== ""
                        font.pixelSize: 20

                        Component.onCompleted: {
                            if (materialTabbed.iconDatas && (materialTabbed.iconDatas.length >= index) && materialTabbed.iconDatas[index])
                            {
                                labelForIcon.text = materialTabbed.iconDatas[index]["text"];
                                labelForIcon.font.family = materialTabbed.iconDatas[index]["fontFamily"];
                            }
                        }
                    }
                }
            }

            Scrollbar {
                flickableItem: listView
            }
        }
    }
}
