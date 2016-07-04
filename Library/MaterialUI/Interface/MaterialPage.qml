import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0

Rectangle {
    id: materialPage
    width: parent.width
    height: parent.height
    color: "#efefef"

    property alias titleText: labelForTitle.text

    property alias tabbedModel: tabbed.model
    property alias tabbedIconDatas: tabbed.iconDatas
    property alias tabbedItemWidth: tabbed.itemWidth
    property alias tabbedZ: tabbed.z

    property bool hideBackButton: false
    property bool hideTopShadow: false

    property bool destroyOnHide: false

    signal tabbedItemSelected(int index, string text)

    function show() {
        visible = true;
        animationForShowAndClose.from = width;
        animationForShowAndClose.to = 0;
        animationForShowAndClose.easing.type = Easing.OutQuad;
        animationForShowAndClose.duration = Math.min(width * 1.5, 800);
        animationForShowAndClose.start();
    }

    function hide() {
        animationForShowAndClose.from = 0;
        animationForShowAndClose.to = width;
        animationForShowAndClose.easing.type = Easing.InQuad;
        animationForShowAndClose.duration = Math.min(width * 1.2, 800);
        animationForShowAndClose.start();
    }

    MouseArea {
        anchors.fill: parent
    }

    RectangularGlow {
        z: 1
        anchors.fill: topRectangle
        glowRadius: 6
        spread: 0.22
        color: "#40000000"
        visible: !hideTopShadow
    }

    RectangularGlow {
        z: -1
        anchors.fill: materialPage
        glowRadius: 6
        spread: 0.22
        color: "#40000000"
        visible: !hideTopShadow
    }

    Rectangle {
        id: topRectangle
        z: 2
        width: parent.width
        height: (48)
        color: "#07bdd3"

        MaterialActionButton {
            width: height
            height: parent.height
            elevation: 0
            textFontFamily: "Material-Design-Iconic-Font"
            text: "\uF297"
            textSize: 22
            textColor: "#ffffff"
            backgroundColor: topRectangle.color
            visible: !hideBackButton

            onClicked: {
                materialPage.hide();
            }
        }

        Label {
            id: labelForTitle
            anchors.centerIn: parent
            color: "#ffffff"
            font.pixelSize: 18
        }
    }

    MaterialTabbed {
        id: tabbed
        z: 2
        width: height
        height: topRectangle.height
        anchors.top: topRectangle.top
        anchors.right: topRectangle.right
        visible: (model) ? (model.length > 0) : (false)
        textColor: "#ffffff"
        backgroundColor: topRectangle.color

        onItemSelected: {
            tabbedItemSelected(index, text);
        }
    }

    NumberAnimation {
        id: animationForShowAndClose
        target: materialPage
        property: "x"

        onStopped: {
            if (to === width)
            {
                visible = false;
                if (destroyOnHide)
                {
                    materialPage.destroy();
                }
            }
            else
            {
                focus = true;
            }
        }
    }
}
