/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 2.15
import JQControls 1.0
import JpgOptimize 1.0

Item {
    id: jpgOptimize
    width: 620
    height: 540

    property bool changingFlag: true
    property bool loadingVisible: false

    Component.onCompleted: {
        changingFlag = false;
    }

    JpgOptimizeManage {
        id: jpgOptimizeManage

        onOptimizeStart: {
            buttonForChooseImage.enabled = false;
            buttonForChooseDirectory.enabled = false;
            JQGlobal.showMessage( "开始压缩图片" );

            listModelForNodes.clear();
            for ( var index = 0; index < fileList.length; ++index )
            {
                listModelForNodes.append( {
                                             fileName: fileList[ index ][ "fileName" ],
                                             filePath: fileList[ index ][ "filePath" ],
                                             originalSize: fileList[ index ][ "originalSize" ]
                                         } );
            }
        }

        onOptimizeEnd: {
            buttonForChooseImage.enabled = true;
            buttonForChooseDirectory.enabled = true;
            JQGlobal.showMessage( "压缩图片完成" );
        }
    }

    JQText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 22
        text: "基于Guetzli开发，支持JPG有损压缩\n大图片压缩非常慢，请耐心等待\n（可以将文件拖拽到此处）"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    JQButton {
        id: buttonForChooseImage
        x: 254
        width: 120
        text: "选择图片"
        anchors.horizontalCenterOffset: 34
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 105

        onClicked: {
            jpgOptimize.loadingVisible = true;

            var reply = jpgOptimizeManage.optimizeJpgByOpenFiles( radioButtonForCoverOldFile.checked );

            switch( reply )
            {
                case "cancel": JQGlobal.showMessage( "用户取消操作" ); break;
                case "mkdir error": JQGlobal.showMessage( "创建目标文件夹失败" ); break;
            }

            jpgOptimize.loadingVisible = false;
        }
    }

    JQButton {
        id: buttonForChooseDirectory
        x: 254
        width: 120
        text: "选择文件夹"
        anchors.horizontalCenterOffset: 190
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 105

        onClicked: {
            jpgOptimize.loadingVisible = true;

            var reply = jpgOptimizeManage.optimizeJpgByOpenDirectory( radioButtonForCoverOldFile.checked );

            switch( reply )
            {
                case "cancel": JQGlobal.showMessage( "用户取消操作" ); break;
                case "empty": JQGlobal.showMessage( "所选文件夹不包含jpg图片" ); break;
                case "mkdir error": JQGlobal.showMessage( "创建目标文件夹失败" ); break;
            }

            jpgOptimize.loadingVisible = false;
        }
    }

    ButtonGroup {
        id: buttonGroupForMode
    }

    JQRadioButton {
        id: radioButtonForCoverOldFile
        x: 115
        text: "压缩后的图片覆盖源文件"
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: -270
        anchors.top: parent.top
        anchors.topMargin: 83
        width: 220
        ButtonGroup.group: buttonGroupForMode
    }

    JQRadioButton {
        id: radioButtonForNewFile
        x: 115
        text: "压缩后的图片另存到桌面"
        anchors.left: parent.horizontalCenter
        anchors.leftMargin: -270
        anchors.top: parent.top
        anchors.topMargin: 126
        width: 220
        ButtonGroup.group: buttonGroupForMode
        checked: true
    }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 180
        width: 575
        height: parent.height - 180
        clip: true
        cacheBuffer: 999999

        model: ListModel {
            id: listModelForNodes
        }

        delegate: Item {
            id: itemForNodes
            width: 575
            height: 54

            Component.onCompleted: {
                jpgOptimizeManage.startOptimize( filePath );
            }

            Connections {
                target: jpgOptimizeManage

                function onOptimizeJpgStart(currentFilePath)
                {
                    if ( currentFilePath !== filePath ) { return; }

                    progressCircleForOptimizing.opacity = 1;
                }

                function onOptimizeJpgFinish(currentFilePath, optimizeResult)
                {
                    if ( currentFilePath !== filePath ) { return; }

                    progressCircleForOptimizing.opacity = 0;
                    labelForCompressionRatio.opacity = 1;

                    if ( !optimizeResult[ "resultSize" ] )
                    {
                        labelForCompressionRatio.text = "失败";
                        labelForCompressionRatio.color = "#ff0000";
                        return;
                    }

                    labelForCompressionRatio.text = optimizeResult[ "compressionRatio" ];

                    labelForResultSize.opacity = 1;
                    labelForResultSize.text = optimizeResult[ "resultSize" ];
                    labelForResultSize.color = optimizeResult[ "compressionRatioColor" ];

                    labelForTimeConsuming.opacity = 1;
                    labelForTimeConsuming.text = optimizeResult[ "timeConsuming" ];
                }
            }

            JQPane {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
            }

            Rectangle {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                color: "#ffffff"
            }

            JQText {
                id: labelForFileName
                x: 16
                anchors.verticalCenter: parent.verticalCenter
                width: 260
                text: fileName
                elide: Text.ElideRight
            }

            JQText {
                id: labelForOriginalSize
                anchors.right: progressCircleForOptimizing.left
                anchors.rightMargin: 25
                anchors.verticalCenter: parent.verticalCenter
                text: originalSize
            }

            JQLoadingIndicator {
                id: progressCircleForOptimizing
                x: 360
                anchors.verticalCenter: parent.verticalCenter
                width: 32
                height: 32
                indicatorSize: 32
                running: true
                showText: false
                visible: opacity !== 0

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }

            JQText {
                id: labelForCompressionRatio
                anchors.centerIn: progressCircleForOptimizing
                width: 32
                height: 32
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.verticalCenter: parent.verticalCenter
                visible: opacity !== 0
                opacity: 0

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }

            JQText {
                id: labelForResultSize
                anchors.left: progressCircleForOptimizing.right
                anchors.leftMargin: 25
                anchors.verticalCenter: parent.verticalCenter
                visible: opacity !== 0
                opacity: 0
                color: "#000000"

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }

            JQText {
                id: labelForTimeConsuming
                anchors.left: progressCircleForOptimizing.right
                anchors.leftMargin: 95
                anchors.verticalCenter: parent.verticalCenter
                visible: opacity !== 0
                opacity: 0

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }
        }
    }

    DropArea {
        anchors.fill: parent

        onDropped: {
            if( !drop.hasUrls ) { return; }

            var filePaths = [ ];

            for( var index = 0; index < drop.urls.length; ++index )
            {
                var jpgFilePath = jpgOptimizeManage.urlToLocalJpgFilePath( drop.urls[ index ] );

                if ( jpgFilePath.length === 0 ) { continue; }

                filePaths.push( jpgFilePath);
            }

            if ( filePaths.length === 0 ) { return; }

            jpgOptimize.loadingVisible = true;

            var reply = jpgOptimizeManage.optimizeJpgByFilePaths( radioButtonForCoverOldFile.checked, filePaths );

            switch( reply )
            {
                case "cancel": JQGlobal.showMessage( "用户取消操作" ); break;
                case "mkdir error": JQGlobal.showMessage( "创建目标文件夹失败" ); break;
            }

            jpgOptimize.loadingVisible = false;
        }
    }

    Rectangle {
        anchors.fill: parent
        z: 999
        visible: jpgOptimize.loadingVisible
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
