/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import BatchReplacement 1.0

Item {
    id: batchReplacement
    width: 620
    height: 540

    property bool changingFlag: true
    property bool loadingVisible: false

    Component.onCompleted: {
        changingFlag = false;
    }

    BatchReplacementManage {
        id: batchReplacementManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQText {
            x: 64
            y: 66
            text: "搜索的文件后缀"
        }

        Column {
            x: 64
            y: 92
            spacing: 4

            JQCheckBox {
                id: checkBoxForCpp
                width: 300
                text: "h/c/cc/cp/cpp/hpp/inc/i/ii/m"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForQmake
                width: 220
                text: "pro/pri/prf/prl/qrc"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForQml
                width: 220
                text: "qml"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForUi
                width: 220
                text: "ui"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForJsonAndXml
                width: 220
                text: "json/xml"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForBatAndSh
                width: 220
                text: "bat/sh"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForNoSuffixFile
                width: 220
                text: "无后缀文件"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForFileAndDir
                width: 220
                text: "文件名/文件夹名"
                checked: true
            }

            JQCheckBox {
                id: checkBoxForMultiCase
                width: 220
                text: "匹配英文大小写"
                checked: true
            }
        }

        JQTextField {
            id: textFieldForSourceKey
            x: 370
            y: 180
            width: 200
            placeholderText: "替换关键字"
            text: ""
        }

        JQTextField {
            id: textFieldForTargetKey
            x: 370
            y: 270
            width: 200
            placeholderText: "目标值"
            text: ""
        }

        JQButton {
            x: 405
            y: 380
            width: 120
            text: "开始替换"

            onClicked: {
                if ( textFieldForSourceKey.text == "" )
                {
                    JQGlobal.showMessage( "请输入替换关键字" );
                    return;
                }

                if ( checkBoxForFileAndDir.checked && ( textFieldForTargetKey.text == "" ) )
                {
                    JQGlobal.showMessage( "请输入目标值" );
                    return;
                }

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

                if ( checkBoxForUi.checked )
                {
                    suffixes.push( "ui" );
                }

                if ( checkBoxForJsonAndXml.checked )
                {
                    suffixes.push( "json" );
                    suffixes.push( "xml" );
                }

                if ( checkBoxForBatAndSh.checked )
                {
                    suffixes.push( "bat" );
                    suffixes.push( "sh" );
                }

                if ( checkBoxForQmake.checked )
                {
                    suffixes.push( "pro" );
                    suffixes.push( "pri" );
                    suffixes.push( "prf" );
                    suffixes.push( "prl" );
                    suffixes.push( "qrc" );
                }

                if ( checkBoxForNoSuffixFile.checked )
                {
                    suffixes.push( "NoSuffixFile" );
                }

                if ( checkBoxForFileAndDir.checked )
                {
                    suffixes.push( "FileNameAndDirName" );
                }

                batchReplacement.loadingVisible = true;

                var reply = batchReplacementManage.previewBatchReplacement(
                            suffixes,
                            textFieldForSourceKey.text,
                            checkBoxForMultiCase.checked
                        );
                batchReplacement.loadingVisible = false;

                if ( "cancel" in reply )
                {
                    JQGlobal.showMessage( "用户取消操作" );
                    return;
                }

                if ( "error" in reply )
                {
                    JQGlobal.showMessage( qsTr( "预搜索失败" ) );
                    return;
                }

                if ( reply[ "replacementCount" ] <= 0 )
                {
                    JQGlobal.showMessage( qsTr( "未搜索到可替换内容" ) );
                    return;
                }

                dialogForConfirm.directoryPath = reply[ "directoryPath" ];
                dialogForConfirm.suffixes = suffixes;
                dialogForConfirm.sourceKey = textFieldForSourceKey.text;
                dialogForConfirm.targetKey = textFieldForTargetKey.text;
                dialogForConfirm.multiCase = checkBoxForMultiCase.checked;
                dialogForConfirm.fileCount = reply[ "fileCount" ];
                dialogForConfirm.replacementCount = reply[ "replacementCount" ];
                dialogForConfirm.open();
            }
        }

        JQText {
            id: labelForReplacementSummary
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 150
            anchors.verticalCenterOffset: -120
            anchors.verticalCenter: parent.verticalCenter
            text: "文件数：" + fileCount + "\n匹配数：" + replacementCount
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft

            property int fileCount: 0
            property int replacementCount: 0
        }

        JQDialog {
            id: dialogForConfirm
            title: qsTr( "确认替换" )
            destroyOnClosed: false
            centerItem: dialogContentForConfirm

            property string directoryPath: ""
            property var suffixes: [ ]
            property string sourceKey: ""
            property string targetKey: ""
            property bool multiCase: false
            property int fileCount: 0
            property int replacementCount: 0

            function startReplacement() {
                batchReplacement.loadingVisible = true;

                var reply = batchReplacementManage.startBatchReplacement(
                            directoryPath,
                            suffixes,
                            sourceKey,
                            targetKey,
                            multiCase
                        );

                batchReplacement.loadingVisible = false;

                if ( "error" in reply )
                {
                    JQGlobal.showMessage( qsTr( "替换失败，请检查参数" ) );
                    return;
                }

                labelForReplacementSummary.fileCount = reply[ "fileCount" ];
                labelForReplacementSummary.replacementCount = reply[ "replacementCount" ];
                var failedOperationCount = ("failedOperationCount" in reply) ? reply[ "failedOperationCount" ] : 0;

                if ( failedOperationCount > 0 )
                {
                    var failedMessage = qsTr( "替换完成，但有 " ) + failedOperationCount + qsTr( " 个操作失败" );

                    if ( ("failedPaths" in reply) && reply[ "failedPaths" ].length > 0 )
                    {
                        failedMessage += "\n" + qsTr( "示例：" ) + reply[ "failedPaths" ][ 0 ];
                    }

                    JQGlobal.showMessage( failedMessage );
                }
                else
                {
                    JQGlobal.showMessage( qsTr( "替换完成" ) );
                }
            }

            Column {
                id: dialogContentForConfirm
                width: 460
                spacing: 12

                JQText {
                    width: parent.width
                    text: qsTr( "已完成粗略搜索，是否开始执行替换？" )
                    wrapMode: Text.WordWrap
                }

                JQText {
                    width: parent.width
                    text: qsTr( "目录：" ) + dialogForConfirm.directoryPath
                    wrapMode: Text.WrapAnywhere
                }

                JQText {
                    width: parent.width
                    text: qsTr( "预计影响文件数：" ) + dialogForConfirm.fileCount
                }

                JQText {
                    width: parent.width
                    text: qsTr( "预计替换处数：" ) + dialogForConfirm.replacementCount
                }

                Row {
                    width: parent.width
                    spacing: 10
                    layoutDirection: Qt.RightToLeft

                    JQButton {
                        width: 100
                        text: qsTr( "确定" )

                        onClicked: {
                            dialogForConfirm.close();
                            dialogForConfirm.startReplacement();
                        }
                    }

                    JQButton {
                        width: 100
                        text: qsTr( "取消" )

                        onClicked: {
                            dialogForConfirm.close();
                        }
                    }
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            z: 999
            visible: batchReplacement.loadingVisible
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
