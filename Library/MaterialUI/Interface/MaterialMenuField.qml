import QtQuick 2.5
import QtQuick.Layouts 1.1
import "../Element"

Item {
    id: field
    width: 100
    height: 56
    z: (dropdown.visible) ? (2) : (0)

    implicitHeight: hasHelperText ? helperTextLabel.y + helperTextLabel.height + (4)
                                  : underline.y + (8)
    implicitWidth: spinBoxContents.implicitWidth

    activeFocusOnTab: true

    property int itemWidth: field.width
    property int itemHeight: 48

    property bool autoOffsetY: false
    property bool fixedOffsetY: false
    property int fixedOffsetYValue: -24

    property color accentColor: "#2196f3"
    property color errorColor: "#F44336"

    property alias model: listView.model
    readonly property string selectedText: listView.currentItem.text
    property alias selectedIndex: listView.currentIndex
    property int maxVisibleItems: 4

    property string textPrefix: " "
    property alias textVerticalAlignment: label.verticalAlignment
    property alias textHorizontalAlignment: label.horizontalAlignment

    property alias placeholderText: fieldPlaceholder.text
    property alias helperText: helperTextLabel.text

    property bool floatingLabel: false
    property bool hasError: false
    property bool hasHelperText: helperText.length > 0

    property alias dropdownVisible: dropdown.visible
    property alias dropdownWidth: dropdown.width
    property alias dropdownHeight: dropdown.height

    readonly property rect inputRect: Qt.rect(spinBox.x, spinBox.y, spinBox.width, spinBox.height)

    signal itemSelected(int index, string text);

    Ink {
        anchors.fill: parent

        onClicked: {
            listView.positionViewAtIndex(listView.currentIndex, ListView.Center)
            var offset = listView.currentItem.itemLabel.mapToItem(dropdown, 0, 0)

            if (autoOffsetY)
            {
                dropdown.open(label, 0, -offset.y - (4));
            }
            else if (fixedOffsetY)
            {
                dropdown.open(label, 0, fixedOffsetYValue);
            }
            else
            {
                dropdown.open(label, 0, -24);
            }

            materialUI.showStealthBackground(function() {
                dropdown.close();
                materialUI.hideStealthBackground();
            }, dropdown);
        }
    }

    Item {
        z: 2
        id: spinBox

        height: (24)
        width: parent.width

        y: {
            if (!floatingLabel)
                return (16)
            if (floatingLabel && !hasHelperText)
                return (40)
            return (28)
        }

        RowLayout {
            id: spinBoxContents

            height: parent.height
            width: parent.width

            MaterialLabel {
                id: label

                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter

                text: field.textPrefix + listView.currentItem.text

                style: "subheading"
                elide: Text.ElideRight
            }
        }

        Dropdown {
            id: dropdown
            anchor: Item.TopLeft
            width: itemWidth
            height: Math.min(maxVisibleItems * (48), listView.height)

            ListView {
                id: listView

                width: dropdown.width
                height: Math.min(count > 0 ? contentHeight : 0, maxVisibleItems * (48));

                interactive: true

                delegate: Standard {
                    id: delegateItem
                    width: dropdown.width
                    height: field.itemHeight

                    text: modelData

                    onClicked: {
                        listView.currentIndex = index

                        dropdown.close()

                        materialUI.hideStealthBackground();

                        itemSelected(index, listView.currentItem.text);
                    }
                }
            }

            Scrollbar {
                flickableItem: listView
            }
        }
    }

    MaterialLabel {
        id: fieldPlaceholder
        anchors.bottom: spinBox.top
        text: field.placeholderText
        visible: floatingLabel
        font.pixelSize: 13
        color: "#42000000"
    }

    Rectangle {
        id: underline

        color: field.hasError ? field.errorColor : field.activeFocus ? field.accentColor : "#42000000"

        height: field.activeFocus ? (2) : (1)

        anchors {
            left: parent.left
            right: parent.right
            top: spinBox.bottom
            topMargin: (6)
        }

        Behavior on height { NumberAnimation { duration: 200 } }

        Behavior on color { ColorAnimation { duration: 200 } }
    }

    MaterialLabel {
        id: helperTextLabel

        anchors {
            left: parent.left
            right: parent.right
            top: underline.top
            topMargin: (4)
        }

        visible: hasHelperText
        font.pixelSize: (12)
        color: field.hasError ? field.errorColor : Qt.darker("#42000000")

        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }
}
