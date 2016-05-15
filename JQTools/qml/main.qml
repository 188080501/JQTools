import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"
import "qrc:/Welcome/"
import "qrc:/PngWarningRemover/"

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
                title: "PNG警告移除",
                source: componentForPngWarningRemover
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
    }

    MaterialUI {
        id: materialUI
        anchors.fill: parent
    }
}
