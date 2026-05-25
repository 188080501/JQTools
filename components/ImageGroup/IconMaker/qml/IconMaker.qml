/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import IconMaker 1.0

Item {
    id: iconMaker
    width: 620
    height: 540
    property bool loadingVisible: false
    property int operationButtonWidth: 160
    property int rightOperationButtonX: 456

    function makeReplyProcessor( reply )
    {
        switch( reply )
        {
            case "saveToFileError": JQGlobal.showMessage( "保存失败" ); break;
            case "OK": JQGlobal.showMessage( "图标制作成功" ); break;
        }
    }

    IconMakerManage {
        id: iconMakerManage

        onTargetSavePathChanged: {
            labelForTargetSavePath.targetSavePath = iconMakerManage.targetSavePath();
        }

        onSourceIconFilePathChanged: {
            labelForSourceFilePath.sourceIconFilePath = iconMakerManage.sourceIconFilePath();
            labelForSourceIconImageWidth.sourceIconImageWidth = iconMakerManage.sourceIconImageWidth();
            labelForSourceIconImageHeight.sourceIconImageHeight = iconMakerManage.sourceIconImageHeight();
            imageForIcon.source = "file:/" + iconMakerManage.sourceIconFilePath();
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        width: 640
        height: 430

        JQText {
            id: labelForTargetSavePath
            x: 49
            y: 60
            width: 400
            text: "保存路径：" + targetSavePath
            elide: Text.ElideLeft

            property string targetSavePath: iconMakerManage.targetSavePath()
        }

        JQText {
            id: labelForSourceFilePath
            x: 49
            y: 86
            width: 400
            text: "原图路径：" + sourceIconFilePath
            elide: Text.ElideLeft

            property string sourceIconFilePath: "未选择"
        }

        JQText {
            id: labelForSourceIconImageWidth
            x: 49
            y: 112
            text: "原图宽：" + sourceIconImageWidth

            property string sourceIconImageWidth: "未选择"
        }

        JQText {
            id: labelForSourceIconImageHeight
            x: 49
            y: 138
            text: "原图高：" + sourceIconImageHeight

            property string sourceIconImageHeight: "未选择"
        }

        JQButton {
            x: 279
            y: 208
            width: iconMaker.operationButtonWidth
            text: "选择原图"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.chooseSourceIconFilePath();

                switch( reply )
                {
                    case "cancel": JQGlobal.showMessage( "用户取消操作" ); break;
                    case "OK": JQGlobal.showMessage( "原图已更新" ); break;
                }

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: 279
            y: 291
            width: iconMaker.operationButtonWidth
            text: "更改保存路径"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.chooseTargetSavePath();

                switch( reply )
                {
                    case "cancel": JQGlobal.showMessage( "用户取消操作" ); break;
                    case "openFail": JQGlobal.showMessage( "文件打开失败" ); break;
                    case "OK": JQGlobal.showMessage( "保存路径已更改" ); break;
                }

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 65
            width: iconMaker.operationButtonWidth
            text: "全部生成"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makeAll();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 121
            width: iconMaker.operationButtonWidth
            text: "OS X(icns)"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makeOSX();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 167
            width: iconMaker.operationButtonWidth
            text: "iOS(png)"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makeIOS();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 223
            width: iconMaker.operationButtonWidth
            text: "Windows(ico)"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makeWindows();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 269
            width: iconMaker.operationButtonWidth
            text: "Android(png)"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makeAndroid();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQButton {
            x: iconMaker.rightOperationButtonX
            y: 325
            width: iconMaker.operationButtonWidth
            text: "PWA(png)"

            onClicked: {
                iconMaker.loadingVisible = true;

                var reply = iconMakerManage.makePWA();

                iconMaker.makeReplyProcessor( reply );

                iconMaker.loadingVisible = false;
            }
        }

        JQText {
            x: 98
            y: 182
            text: "图标预览"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Rectangle {
            x: 49
            y: 208
            width: 162
            height: 162
            color: "#00000000"
            border.color: "#000000"
            border.width: 1

            Image {
                x: 1
                y: 1
                z: -1
                width: 160
                height: 160
                source: "qrc:/IconMaker/Background.jpg"
            }

            Image {
                id: imageForIcon
                x: 1
                y: 1
                z: -1
                width: 160
                height: 160
                source: "qrc:/IconMaker/DefaultIcon.png"
            }
        }

        Rectangle {
            anchors.fill: parent
            z: 999
            visible: iconMaker.loadingVisible
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
}
