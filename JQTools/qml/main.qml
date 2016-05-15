import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"
import "qrc:/WelcomePage/"

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
                source: componentForWelcomePage
            }
        ]

        iconDatas: [
            {
                fontFamily: materialUI.materialFontName,
                text: "\uF036"
            }
        ]

        Component {
            id: componentForWelcomePage

            WelcomePage {
                id: welcomePage
            }
        }
    }

    MaterialUI {
        id: materialUI
        anchors.fill: parent
    }
}
