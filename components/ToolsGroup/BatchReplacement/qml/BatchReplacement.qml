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
import BatchReplacement 1.0

Item {
    id: batchReplacement
    width: 620
    height: 540

    property bool changingFlag: true

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

        MaterialLabel {
            x: 64
            y: 66
            text: "搜索的文件后缀"
        }

        Column {
            x: 64
            y: 92
            spacing: -10

            MaterialCheckBox {
                id: checkBoxForCpp
                text: "h/c/cc/cp/cpp/hpp/inc/i/ii/m"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForQmake
                text: "pro/pri/prf/prl/qrc"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForQml
                text: "qml"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForUi
                text: "ui"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForJsonAndXml
                text: "json/xml"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForBatAndSh
                text: "bat/sh"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForNoSuffixFile
                text: "无后缀文件"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForFileAndDir
                text: "文件名/文件夹名"
                checked: true
            }

            MaterialCheckBox {
                id: checkBoxForMultiCase
                text: "匹配英文大小写"
                checked: true
            }
        }

        MaterialTextField {
            id: textFieldForSourceKey
            x: 370
            y: 180
            width: 200
            placeholderText: "替换关键字"
            text: ""
        }

        MaterialTextField {
            id: textFieldForTargetKey
            x: 370
            y: 270
            width: 200
            placeholderText: "目标值"
            text: ""
        }

        MaterialButton {
            x: 405
            y: 380
            width: 120
            height: 40
            text: "开始替换"

            onClicked: {
                if ( textFieldForSourceKey.text == "" )
                {
                    materialUI.showSnackbarMessage( "请输入替换关键字" );
                    return;
                }

                if ( checkBoxForFileAndDir.checked && ( textFieldForTargetKey.text == "" ) )
                {
                    materialUI.showSnackbarMessage( "请输入目标值" );
                    return;
                }

                materialUI.showLoading();

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

                var reply = batchReplacementManage.startBatchReplacement(
                            suffixes,
                            textFieldForSourceKey.text,
                            textFieldForTargetKey.text,
                            checkBoxForMultiCase.checked
                        );

                if ( "cancel" in reply )
                {
                    materialUI.showSnackbarMessage( "用户取消操作" );
                    materialUI.hideLoading();
                    return;
                }

                labelForReplacementSummary.fileCount = reply[ "fileCount" ];
                labelForReplacementSummary.replacementCount = reply[ "replacementCount" ];

                materialUI.hideLoading();
            }
        }

        MaterialLabel {
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
    }
}
