import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/Interface/"
import PngWarningRemover 1.0

Item {
    id: pngWarningRemover
    width: 620
    height: 540

    PngWarningRemoverManage {
        id: pngWarningRemoverManage
    }

    MaterialLabel {
        x: 162
        y: 170
        text:
"在Qt中，如果使用某些格式png图片，可能会报错
libpng warning: iCCP: known incorrect sRGB profile
这是PNG中嵌入了icc颜色管理模块导致的，虽然没什么影响，但是看到这个警告非常的烦
使用本工具，将PNG图片进行转换后，可以消除此警告"
        anchors.verticalCenterOffset: -68
        anchors.horizontalCenterOffset: 1
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MaterialButton {
        x: 254
        y: 278
        width: 120
        height: 40
        text: "选择图片"
        anchors.verticalCenterOffset: 53
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        onClicked: {
            materialUI.showLoading();

            var reply = pngWarningRemoverManage.conversationPng();

            switch( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                case "openSourceError": materialUI.showSnackbarMessage( "打开源文件失败" ); break;
                case "saveTargetError": materialUI.showSnackbarMessage( "保存目标文件失败" ); break;
                case "OK": materialUI.showSnackbarMessage( "所有图片转换已经完成" ); break;
            }

            materialUI.hideLoading();
        }
    }
}
