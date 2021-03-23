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

        MaterialCheckBox {
            id: checkBoxForCpp
            x: 64
            y: 92
            text: "h/c/cc/cp/cpp/hpp/inc/i/ii/m"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForQmake
            x: 64
            y: 142
            text: "pro/pri/prf/prl/qrc"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForQml
            x: 64
            y: 192
            text: "qml"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForUi
            x: 64
            y: 242
            text: "ui"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForJsonAndXml
            x: 64
            y: 292
            text: "json/xml"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForNoSuffixFile
            x: 64
            y: 342
            text: "无后缀文件"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForFileAndDir
            x: 64
            y: 392
            text: "文件名/文件夹名"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForMultiCase
            x: 64
            y: 442
            text: "匹配英文大小写"
            checked: true
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

                if ( checkBoxForFileAndDir.checked && ( textFieldForSourceKey.text == "" ) )
                {
                    materialUI.showSnackbarMessage( "请输入目标值" );
                    return;
                }

                materialUI.showLoading();

                var suffixs = new Array;

                if ( checkBoxForCpp.checked )
                {
                    suffixs.push( "h" );
                    suffixs.push( "c" );
                    suffixs.push( "cc" );
                    suffixs.push( "cp" );
                    suffixs.push( "cpp" );
                    suffixs.push( "hpp" );
                    suffixs.push( "inc" );
                    suffixs.push( "i" );
                    suffixs.push( "ii" );
                    suffixs.push( "m" );
                }

                if ( checkBoxForQml.checked )
                {
                    suffixs.push( "qml" );
                }

                if ( checkBoxForUi.checked )
                {
                    suffixs.push( "ui" );
                }

                if ( checkBoxForJsonAndXml.checked )
                {
                    suffixs.push( "json" );
                    suffixs.push( "xml" );
                }

                if ( checkBoxForQmake.checked )
                {
                    suffixs.push( "pro" );
                    suffixs.push( "pri" );
                    suffixs.push( "prf" );
                    suffixs.push( "prl" );
                    suffixs.push( "qrc" );
                }

                if ( checkBoxForNoSuffixFile.checked )
                {
                    suffixs.push( "NoSuffixFile" );
                }

                if ( checkBoxForFileAndDir.checked )
                {
                    suffixs.push( "FileNameAndDirName" );
                }

                var reply = batchReplacementManage.startBatchReplacement(
                            suffixs,
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

                labelForLinesCount.fileCount = reply[ "fileCount" ];
                labelForLinesCount.replacementCount = reply[ "replacementCount" ];

                materialUI.hideLoading();
            }
        }

        MaterialLabel {
            id: labelForLinesCount
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
