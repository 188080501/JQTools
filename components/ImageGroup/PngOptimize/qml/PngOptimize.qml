/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import PngOptimize 1.0

Item {
    id: pngOptimize
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    PngOptimizeManage {
        id: pngOptimizeManage

        onOptimizeStart: {
            buttonForChooseImage.enabled = false;
            buttonForChooseDirectory.enabled = false;
            materialUI.showSnackbarMessage( "开始压缩图片" );

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
            materialUI.showSnackbarMessage( "压缩图片完成" );
        }
    }

    MaterialLabel {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 22
        text: "基于Zopfli开发，仅支持PNG图片\n大图片压缩非常慢，请耐心等待\n（可以将文件拖拽拖拽到此处）"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MaterialButton {
        id: buttonForChooseImage
        x: 254
        width: 120
        height: 40
        text: "选择图片"
        anchors.horizontalCenterOffset: 34
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 105

        onClicked: {
            materialUI.showLoading();

            var reply = pngOptimizeManage.optimizePngByOpenFiles( radioButtonForCoverOldFile.checked );

            switch( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                case "mkdir error": materialUI.showSnackbarMessage( "创建目标文件夹失败" ); break;
            }

            materialUI.hideLoading();
        }
    }

    MaterialButton {
        id: buttonForChooseDirectory
        x: 254
        width: 120
        height: 40
        text: "选择文件夹"
        anchors.horizontalCenterOffset: 190
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 105

        onClicked: {
            materialUI.showLoading();

            var reply = pngOptimizeManage.optimizePngByOpenDirectory( radioButtonForCoverOldFile.checked );

            switch( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                case "empty": materialUI.showSnackbarMessage( "所选文件夹不包含png图片" ); break;
                case "mkdir error": materialUI.showSnackbarMessage( "创建目标文件夹失败" ); break;
            }

            materialUI.hideLoading();
        }
    }

    ExclusiveGroup {
        id: exclusiveGroupForMode
    }

    MaterialRadioButton {
        id: radioButtonForCoverOldFile
        x: 115
        text: "压缩后的图片覆盖源文件"
        anchors.horizontalCenterOffset: -168
        anchors.top: parent.top
        anchors.topMargin: 83
        anchors.horizontalCenter: parent.horizontalCenter
        exclusiveGroup: exclusiveGroupForMode
    }

    MaterialRadioButton {
        id: radioButtonForNewFile
        x: 115
        text: "压缩后的图片另存为到桌面"
        anchors.horizontalCenterOffset: -161
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 126
        exclusiveGroup: exclusiveGroupForMode
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
                pngOptimizeManage.startOptimize( filePath );
            }

            Connections {
                target: pngOptimizeManage

                onOptimizePngStart: {
                    if ( currentFilePath !== filePath ) { return; }

                    progressCircleForOptimizing.indeterminate = true;
                }

                onOptimizePngFinish: {
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

            RectangularGlow {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                glowRadius: 4
                spread: 0.2
                color: "#44000000"
                cornerRadius: 8
            }

            Rectangle {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                color: "#ffffff"
            }

            MaterialLabel {
                id: labelForFileName
                x: 16
                anchors.verticalCenter: parent.verticalCenter
                width: 260
                text: fileName
                elide: Text.ElideRight
            }

            MaterialLabel {
                id: labelForOriginalSize
                anchors.right: progressCircleForOptimizing.left
                anchors.rightMargin: 25
                anchors.verticalCenter: parent.verticalCenter
                text: originalSize
            }

            MaterialProgressCircle {
                id: progressCircleForOptimizing
                x: 360
                anchors.verticalCenter: parent.verticalCenter
                width: 32
                height: 32
                indeterminate: false
                autoChangeColor: true
                visible: opacity !== 0

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }

            MaterialLabel {
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

            MaterialLabel {
                id: labelForResultSize
                anchors.left: progressCircleForOptimizing.right
                anchors.leftMargin: 25
                anchors.verticalCenter: parent.verticalCenter
                visible: opacity !== 0
                opacity: 0
                color: "#000000"

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }

            MaterialLabel {
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
                var pngFilePath = pngOptimizeManage.urlToLocalPngFilePath( drop.urls[ index ] );

                if ( pngFilePath.length === 0 ) { continue; }

                filePaths.push( pngFilePath);
            }

            if ( filePaths.length === 0 ) { return; }

            materialUI.showLoading();

            var reply = pngOptimizeManage.optimizePngByFilePaths( radioButtonForCoverOldFile.checked, filePaths );

            switch( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                case "mkdir error": materialUI.showSnackbarMessage( "创建目标文件夹失败" ); break;
            }

            materialUI.hideLoading();
        }
    }
}
