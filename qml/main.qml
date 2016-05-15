import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"
import "qrc:/Welcome/"
import "qrc:/PngWarningRemover/"
import "qrc:/Utf16Transform/"
import "qrc:/HashCalculate/"
import "qrc:/IconMaker/"

ApplicationWindow {
    id: applicationWindow
    title: qsTr("JQTools")
    width: 640
    height: 480
    visible: true
    opacity: 0
    color: "#00000000"

    minimumWidth: 640
    minimumHeight: 480

    NumberAnimation {
        id: animationForOpacity
        target: applicationWindow
        property: "opacity"
        easing.type: Easing.OutCubic
        duration: 300
        to: 1
    }

    Component.onCompleted: {
        animationForOpacity.start();
    }

    MaterialTabs {
        id: tabs
        anchors.fill: parent

        tabSource: [
            {
                title: "欢迎页",
                source: componentForWelcome
            },
            {
                title: "PNG警告",
                source: componentForPngWarningRemover,
                implicitWidth: 80
            },
            {
                title: "UTF-16转换",
                source: componentForUtf16Transform,
                implicitWidth: 105
            },
            {
                title: "HASH计算",
                source: componentForHashCalculate,
                implicitWidth: 90
            },
            {
                title: "图标生成",
                source: componentForIconMaker,
                implicitWidth: 90
            }
        ]

        iconDatas: [
            {
                fontFamily: materialUI.materialFontName,
                text: "\uF036"
            }
        ]

        Component {
            id: componentForWelcome

            Welcome {
                id: welcome
            }
        }

        Component {
            id: componentForPngWarningRemover

            PngWarningRemover {
                id: pngWarningRemover
            }
        }

        Component {
            id: componentForUtf16Transform

            Utf16Transform {
                id: utf16Transform
            }
        }

        Component {
            id: componentForHashCalculate

            HashCalculate {
                id: hashCalculate
            }
        }

        Component {
            id: componentForIconMaker

            IconMaker {
                id: iconMaker
            }
        }

        Rectangle {
            z: -1
            anchors.fill: parent
            color: "#ededed"
        }
    }

    MaterialUI {
        id: materialUI
        anchors.fill: parent
    }
}
