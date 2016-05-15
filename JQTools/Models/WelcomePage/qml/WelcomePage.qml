import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/Interface/"
import WelcomePage 1.0

Item {
    id: item1
    width: 640
    height: 480

    WelcomePageManage {
        id: welcomePageManage
    }

    MaterialLabel {
        x: 162
        y: 170
        text: "欢迎使用JQTools\n这是基于Qt开发的一款小工具包"
        anchors.verticalCenterOffset: -59
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MaterialButton {
        x: 254
        y: 278
        text: "访问GitHub"
        anchors.verticalCenterOffset: 21
        anchors.horizontalCenterOffset: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

    MaterialLabel {
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 3
        text: "当前版本：V" + welcomePageManage.jqToolsVersion();
        verticalAlignment: Text.AlignBottom
        horizontalAlignment: Text.AlignRight
        color: "#a1a1a1"
    }
}
