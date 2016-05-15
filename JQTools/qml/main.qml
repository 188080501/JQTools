import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"
import "qrc:/Welcome/"
import "qrc:/PngWarningRemover/"
import "qrc:/Utf16Transform/"

ApplicationWindow {
    title: qsTr("JQTools")
    width: 640
    height: 480
    visible: true

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
                implicitWidth: 110
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
    }

    MaterialUI {
        id: materialUI
        anchors.fill: parent
    }
}
