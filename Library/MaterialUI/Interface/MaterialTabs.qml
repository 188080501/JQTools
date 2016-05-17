import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles
import QtGraphicalEffects 1.0

Item {
    id: tabs

    signal indexRefreshed();

    property var tabSource
    property var iconDatas

    property int currentItemX
    property int currentItemWidth

    property int tabHeight: 48

    property alias currentIndex: tabView.currentIndex
    property alias tabPosition: tabView.tabPosition

    property bool hideTopShadow: false
    property bool hideTopBackground: false

    property alias tabView: tabView

    Component.onCompleted: {
        for (var index = 0; index < tabSource.length; index++)
        {
            var tab = tabView.addTab(tabSource[index]["title"], tabSource[index]["source"]);

            if ("objectName" in tabSource[index])
            {
                tab.children[0].item.objectName = tabSource[index]["objectName"];
            }
        }
        indexRefreshed();
    }

    Controls.TabView {
        id: tabView
        anchors.fill: parent
        clip: false

        style: ControlStyles.TabViewStyle {
            frameOverlap: 0
            tabOverlap: 0
            tabsAlignment: Qt.AlignHCenter

            tab: MaterialButton {
                height: tabs.tabHeight
                text: styleData.title
                textColor: (styleData.selected) ? ("#ffffff") : ("#a2ffffff")
                implicitWidth: Math.min(Math.max(labelWidth + 40, 80), tabView.width / tabView.count)
                elevation: 0

                Component.onCompleted: {
                    if (tabs.iconDatas && (tabs.iconDatas.length >= styleData.index) && tabs.iconDatas[styleData.index])
                    {
                        iconVisible = true;
                        iconFontFamily = tabs.iconDatas[styleData.index]["fontFamily"];
                        iconText = tabs.iconDatas[styleData.index]["text"];
                        iconSize = textSize * 1.5;
                    }

                    if ( "implicitWidth" in tabs.tabSource[ styleData.index ] )
                    {
                        implicitWidth = tabs.tabSource[ styleData.index ][ "implicitWidth" ];
                    }
                }

                function refreshPosition() {
                    if (tabView.currentIndex === styleData.index)
                    {
                        needle.x = parent.parent.x + parent.parent.parent.parent.x
                        needle.width = width
                    }
                }

                onClicked: {
                    tabView.currentIndex = styleData.index;
                }

                Connections {
                    target: parent.parent.parent.parent

                    onXChanged: {
                        refreshPosition();
                    }
                }

                Connections {
                    target: tabs

                    onWidthChanged: {
                        refreshPosition();
                    }

                    onCurrentIndexChanged: {
                        refreshPosition();
                    }

                    onIndexRefreshed: {
                        refreshPosition();
                    }
                }

                Behavior on textColor {
                    ColorAnimation { duration: 200; }
                }
            }

            frame: Rectangle {
                color: "#00000000"
            }
        }

        RectangularGlow {
            z: 1
            anchors.fill: tabBackground
            glowRadius: 6
            spread: 0.22
            color: "#40000000"
            visible: !hideTopShadow
        }

        Rectangle {
            id: tabBackground
            x: 0
            y: -1 * (tabs.tabHeight)
            z: 1
            width: tabView.width
            height: (tabs.tabHeight)
            color: "#07bdd3"
            visible: !hideTopBackground
        }
    }

    Rectangle {
        id: needle
        x: 0
        y: (tabs.tabPosition === Qt.TopEdge) ? (tabs.tabHeight - 2) : (parent.height - tabs.tabHeight)
        width: 20
        height: (2)
        color: "#ffff95"

        Behavior on x {
            NumberAnimation { duration: 200; easing.type: Easing.OutCubic }
        }

        Behavior on width {
            NumberAnimation { duration: 200; }
        }
    }
}
