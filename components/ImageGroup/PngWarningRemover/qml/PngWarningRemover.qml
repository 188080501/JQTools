/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import PngWarningRemover 1.0

Item {
    id: pngWarningRemover
    width: 620
    height: 540
    property bool loadingVisible: false

    PngWarningRemoverManage {
        id: pngWarningRemoverManage
    }

    JQText {
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

    Row {
        anchors.verticalCenterOffset: 53
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        spacing: 16

        JQButton {
            width: 120
            text: qsTr( "选择图片" )

            onClicked: {
                pngWarningRemover.loadingVisible = true;

                var reply = pngWarningRemoverManage.convertPng();

                switch( reply )
                {
                    case "cancel": JQGlobal.showMessage(  qsTr( "用户取消操作" ) ); break;
                    case "openSourceError": JQGlobal.showMessage(  qsTr( "打开源文件失败：" ) + pngWarningRemoverManage.lastErrorFileName() ); break;
                    case "saveTargetError": JQGlobal.showMessage(  qsTr( "保存目标文件失败：" ) + pngWarningRemoverManage.lastErrorFileName() ); break;
                    case "OK": JQGlobal.showMessage(  qsTr( "所有图片转换已经完成" ) ); break;
                }

                pngWarningRemover.loadingVisible = false;
            }
        }

        JQButton {
            width: 120
            text: qsTr( "选择文件夹" )

            onClicked: {
                pngWarningRemover.loadingVisible = true;

                var reply = pngWarningRemoverManage.convertPngByOpenDirectory();

                switch( reply )
                {
                    case "cancel": JQGlobal.showMessage(  qsTr( "用户取消操作" ) ); break;
                    case "empty": JQGlobal.showMessage(  qsTr( "所选文件夹不包含png图片" ) ); break;
                    case "openSourceError": JQGlobal.showMessage(  qsTr( "打开源文件失败：" ) + pngWarningRemoverManage.lastErrorFileName() ); break;
                    case "saveTargetError": JQGlobal.showMessage(  qsTr( "保存目标文件失败：" ) + pngWarningRemoverManage.lastErrorFileName() ); break;
                    case "OK": JQGlobal.showMessage(  qsTr( "所有图片转换已经完成" ) ); break;
                }

                pngWarningRemover.loadingVisible = false;
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        z: 999
        visible: pngWarningRemover.loadingVisible
        color: "#55000000"

        JQLoadingIndicator {
            anchors.centerIn: parent
            text: "处理中..."
        }

        MouseArea {
            anchors.fill: parent
        }
    }
}
