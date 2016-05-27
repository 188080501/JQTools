import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import LinesStatistics 1.0

Item {
    id: linesStatistics
    width: 620
    height: 540

    property bool changingFlag: true

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

        MaterialLabel {
            x: 61
            y: 157
            text: "搜索的文件后缀"
        }

        MaterialCheckBox {
            id: checkBoxForCpp
            x: 61
            y: 183
            text: "h/c/cc/cp/cpp/hpp/inc/i/ii/m"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForQml
            x: 61
            y: 303
            text: "qml"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForQmake
            x: 61
            y: 243
            text: "pro/pri/prf/prl"
            checked: true
        }

        MaterialButton {
            x: 254
            y: 278
            width: 120
            height: 40
            text: "开始统计"
            anchors.horizontalCenterOffset: 134
            anchors.verticalCenterOffset: 32
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            onClicked: {
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

                if ( checkBoxForQmake.checked )
                {
                    suffixs.push( "pro" );
                    suffixs.push( "pri" );
                    suffixs.push( "prf" );
                    suffixs.push( "prl" );
                }

                var reply = linesStatisticsManage.statisticsLines( suffixs );

                if ( "cancel" in reply )
                {
                    materialUI.showSnackbarMessage( "用户取消操作" );
                    materialUI.hideLoading();
                    return;
                }

                labelForLinesCount.fileCount = reply[ "fileCount" ];
                labelForLinesCount.lineCount = reply[ "lineCount" ];

                materialUI.hideLoading();
            }
        }

        MaterialLabel {
            id: labelForLinesCount
            text: "文件数：" + fileCount + "\n行数：" + lineCount
            anchors.horizontalCenterOffset: 134
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenterOffset: -53
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            property int fileCount: 0
            property int lineCount: 0
        }
    }
}
