import QtQuick 2.5
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
            materialUI.showSnackbarMessage( "开始压缩图片" );

            listModelForNodes.clear();
            for ( var index = 0; index < fileList.length; ++index )
            {
                listModelForNodes.append( {
                                             fileName: fileList[ index ][ "fileName" ],
                                             originalSize: fileList[ index ][ "originalSize" ]
                                         } );
            }
        }

        onOptimizeEnd: {
            buttonForChooseImage.enabled = true;
            materialUI.showSnackbarMessage( "压缩图片完成" );
        }
    }

    MaterialLabel {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        text: "基于Zopfli开发，仅支持PNG图片，大图片压缩非常慢，请耐心等待"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MaterialButton {
        id: buttonForChooseImage
        x: 254
        width: 120
        height: 40
        text: "选择图片"
        anchors.horizontalCenterOffset: 101
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 97

        onClicked: {
            materialUI.showLoading();

            var reply = pngOptimizeManage.optimizePng( radioButtonForCoverOldFile.checked );

            switch( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
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
        text: "优化后覆盖旧图片"
        anchors.horizontalCenterOffset: -115
        anchors.top: parent.top
        anchors.topMargin: 74
        anchors.horizontalCenter: parent.horizontalCenter
        exclusiveGroup: exclusiveGroupForMode
    }

    MaterialRadioButton {
        id: radioButtonForNewFile
        x: 115
        text: "另存为优化后图片到桌面"
        anchors.horizontalCenterOffset: -94
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 118
        exclusiveGroup: exclusiveGroupForMode
        checked: true
    }

    ListView {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 180
        width: 500
        height: parent.height - 180
        clip: true
        cacheBuffer: 9999

        model: ListModel {
            id: listModelForNodes
        }

        delegate: Item {
            id: itemForNodes
            width: 500
            height: 54

            Connections {
                target: pngOptimizeManage

                onOptimizePngFinish: {
                    if ( currentFileName !== fileName ) { return; }

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
                width: 300
                text: fileName
                elide: Text.ElideRight
            }

            MaterialLabel {
                id: labelForOriginalSize
                anchors.right: progressCircleForOptimizing.left
                anchors.rightMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                text: originalSize
            }

            MaterialProgressCircle {
                id: progressCircleForOptimizing
                x: 390
                anchors.verticalCenter: parent.verticalCenter
                width: 32
                height: 32
                indeterminate: visible
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
                anchors.leftMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                visible: opacity !== 0
                opacity: 0
                color: "#64dd17"

                Behavior on opacity { NumberAnimation { duration: 300 } }
            }
        }
    }
}
