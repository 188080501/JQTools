import QtQuick 2.5
import QtQuick.Controls 1.4
import "qrc:/MaterialUI/Interface/"
import IconMaker 1.0

Item {
    id: iconMaker
    width: 620
    height: 540

    function makeReplyProcessor( reply )
    {
        switch( reply )
        {
            case "saveToFileError": materialUI.showSnackbarMessage( "保存失败" ); break;
            case "OK": materialUI.showSnackbarMessage( "图标制作成功" ); break;
        }
    }

    IconMakerManage {
        id: iconMakerManage

        onTargetSavePathChanged: {
            labelForTargetSavePath.targetSavePath = iconMakerManage.targetSavePath();
        }

        onSourceIconFilePathChanged: {
            labelForSourceFilePath.sourceIconFilePath = iconMakerManage.sourceIconFilePath();
            labelForSourceIconImageWidht.sourceIconImageWidht = iconMakerManage.sourceIconImageWidht();
            labelForTargetIconImageWidht.sourceIconImageHeight = iconMakerManage.sourceIconImageHeight();
            imageForIcon.source = "file:/" + iconMakerManage.sourceIconFilePath();
        }
    }

    Item {
        id: centerItem
        anchors.centerIn: parent
        width: 640
        height: 430

        MaterialLabel {
            id: labelForTargetSavePath
            x: 49
            y: 60
            width: 400
            text: "保存路径：" + targetSavePath
            elide: Text.ElideLeft

            property string targetSavePath: iconMakerManage.targetSavePath()
        }

        MaterialLabel {
            id: labelForSourceFilePath
            x: 49
            y: 86
            width: 400
            text: "原图路径：" + sourceIconFilePath
            elide: Text.ElideLeft

            property string sourceIconFilePath: "未选择"
        }

        MaterialLabel {
            id: labelForSourceIconImageWidht
            x: 49
            y: 112
            text: "原图宽：" + sourceIconImageWidht

            property string sourceIconImageWidht: "未选择"
        }

        MaterialLabel {
            id: labelForTargetIconImageWidht
            x: 49
            y: 138
            text: "原图高：" + sourceIconImageHeight

            property string sourceIconImageHeight: "未选择"
        }

        MaterialButton {
            x: 279
            y: 208
            width: 120
            height: 40
            text: "选择原图"
            backgroundColor: "#2196f3"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.choostSourceIconFilePath();

                switch( reply )
                {
                    case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                    case "OK": materialUI.showSnackbarMessage( "保存路径已更改" ); break;
                }

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 279
            y: 291
            width: 120
            height: 40
            text: "更改保存路径"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.chooseTargetSavePath();

                switch( reply )
                {
                    case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                    case "openFail": materialUI.showSnackbarMessage( "文件打开失败" ); break;
                    case "OK": materialUI.showSnackbarMessage( "保存路径已更改" ); break;
                }

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 65
            width: 120
            height: 40
            text: "所有"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeAll();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 121
            width: 120
            height: 40
            text: "OS X(icns)"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeOSX();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 167
            width: 120
            height: 40
            text: "iOS(png)"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeIOS();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 223
            width: 120
            height: 40
            text: "Windows(ico)"
            enabled: false

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeWindows();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 269
            width: 120
            height: 40
            text: "WP(png)"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeWP();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialButton {
            x: 476
            y: 325
            width: 120
            height: 40
            text: "Android(png)"

            onClicked: {
                materialUI.showLoading();

                var reply = iconMakerManage.makeAndroid();

                iconMaker.makeReplyProcessor( reply );

                materialUI.hideLoading();
            }
        }

        MaterialLabel {
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
    }
}
