/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import LinesStatistics 1.0

Item {
    id: linesStatistics
    width: 620
    height: 540

    property bool changingFlag: true
    property bool loadingVisible: false

    Component.onCompleted: {
        changingFlag = false;
    }

    LinesStatisticsManage {
        id: linesStatisticsManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQText {
            x: 64
            y: 136
            text: "搜索的文件后缀"
        }

        JQCheckBox {
            id: checkBoxForCpp
            x: 64
            y: 162
            width: 300
            text: "h/c/cc/cp/cpp/hpp/inc/i/ii/m"
            checked: true
        }

        JQCheckBox {
            id: checkBoxForQmake
            x: 64
            y: 222
            width: 220
            text: "pro/pri/prf/prl"
            checked: true
        }

        JQCheckBox {
            id: checkBoxForQml
            x: 64
            y: 282
            width: 120
            text: "qml"
            checked: true
        }

        JQCheckBox {
            id: checkBoxForImage
            x: 64
            y: 342
            width: 340
            text: "png/jpg/jpeg/bmp/gif/svg/psd/ai"
            checked: false
        }

        JQText {
            x: 64
            y: 396
            text: "过滤特殊目录"
        }

        JQCheckBox {
            id: checkBoxForIgnoreBuild
            x: 64
            y: 422
            width: 120
            text: "build"
            checked: true
        }

        JQCheckBox {
            id: checkBoxForIgnoreGit
            x: 64
            y: 462
            width: 120
            text: ".git"
            checked: true
        }

        JQButton {
            x: 254
            y: 278
            width: 120
            text: "开始统计"
            anchors.horizontalCenterOffset: 134
            anchors.verticalCenterOffset: 32
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
                linesStatistics.loadingVisible = true;

                var suffixes = new Array;

                if ( checkBoxForCpp.checked )
                {
                    suffixes.push( "h" );
                    suffixes.push( "c" );
                    suffixes.push( "cc" );
                    suffixes.push( "cp" );
                    suffixes.push( "cpp" );
                    suffixes.push( "hpp" );
                    suffixes.push( "inc" );
                    suffixes.push( "i" );
                    suffixes.push( "ii" );
                    suffixes.push( "m" );
                }

                if ( checkBoxForQml.checked )
                {
                    suffixes.push( "qml" );
                }

                if ( checkBoxForQmake.checked )
                {
                    suffixes.push( "pro" );
                    suffixes.push( "pri" );
                    suffixes.push( "prf" );
                    suffixes.push( "prl" );
                }

                if ( checkBoxForImage.checked )
                {
                    suffixes.push( "png" );
                    suffixes.push( "jpg" );
                    suffixes.push( "jpeg" );
                    suffixes.push( "bmp" );
                    suffixes.push( "gif" );
                    suffixes.push( "svg" );
                    suffixes.push( "psd" );
                    suffixes.push( "ai" );
                }

                var ignoredDirectoryNames = new Array;

                if ( checkBoxForIgnoreBuild.checked )
                {
                    ignoredDirectoryNames.push( "build" );
                }

                if ( checkBoxForIgnoreGit.checked )
                {
                    ignoredDirectoryNames.push( ".git" );
                }

                var reply = linesStatisticsManage.collectLineStatistics( suffixes, ignoredDirectoryNames );
                linesStatistics.loadingVisible = false;

                if ( "cancel" in reply )
                {
                    JQGlobal.showMessage( "用户取消操作" );
                    return;
                }

                labelForLinesCount.fileCount = reply[ "fileCount" ];
                labelForLinesCount.lineCount = reply[ "lineCount" ];
            }
        }

        JQText {
            id: labelForLinesCount
            text: "文件数：" + fileCount + "\n代码行数：" + lineCount
            anchors.horizontalCenterOffset: 134
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            anchors.verticalCenterOffset: -53
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            property int fileCount: 0
            property int lineCount: 0
        }

        Rectangle {
            anchors.fill: parent
            z: 999
            visible: linesStatistics.loadingVisible
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
