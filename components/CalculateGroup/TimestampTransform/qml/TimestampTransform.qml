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
import TimestampTransform 1.0

Item {
    id: timestampTransform
    width: 620
    height: 540

    property bool changingFlag: false
    property string convertedDateTimeStringValue: ""
    property string secondsTimestampStringValue: ""
    property string millisecondsTimestampStringValue: ""

    TimestampTransformManage {
        id: timestampTransformManage
    }

    function refreshDateTimeFromTimestamp() {
        if ( timestampTransform.changingFlag ) { return; }

        timestampTransform.changingFlag = true;

        var convertedDateTimeString = timestampTransformManage.dateTimeStringFromTimestampString(
                    textFieldForTimestampString.text
                );
        convertedDateTimeStringValue = convertedDateTimeString;

        labelForConvertedDateTimeString.text = ( convertedDateTimeString === "" ) ?
                    ( qsTr( "日期时间：无效时间戳" ) ) :
                    ( qsTr( "日期时间：" ) + convertedDateTimeString );

        timestampTransform.changingFlag = false;
    }

    function refreshTimestampFromDateTime() {
        if ( timestampTransform.changingFlag ) { return; }

        timestampTransform.changingFlag = true;

        var secondsTimestamp = timestampTransformManage.timestampStringFromDateTimeString(
                    textFieldForDateTimeString.text,
                    false
                );
        var millisecondsTimestamp = timestampTransformManage.timestampStringFromDateTimeString(
                    textFieldForDateTimeString.text,
                    true
                );
        secondsTimestampStringValue = secondsTimestamp;
        millisecondsTimestampStringValue = millisecondsTimestamp;

        labelForSecondsTimestamp.text = ( secondsTimestamp === "" ) ?
                    ( qsTr( "秒级时间戳：无效日期时间" ) ) :
                    ( qsTr( "秒级时间戳：" ) + secondsTimestamp );
        labelForMillisecondsTimestamp.text = ( millisecondsTimestamp === "" ) ?
                    ( qsTr( "毫秒时间戳：无效日期时间" ) ) :
                    ( qsTr( "毫秒时间戳：" ) + millisecondsTimestamp );

        timestampTransform.changingFlag = false;
    }

    Component.onCompleted: {
        textFieldForTimestampString.text = timestampTransformManage.currentSecondsTimestampString();
        textFieldForDateTimeString.text = timestampTransformManage.currentDateTimeString();

        refreshDateTimeFromTimestamp();
        refreshTimestampFromDateTime();
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        Item {
            id: itemForTimestampToDateTime
            width: 620
            height: 280

            MaterialLabel {
                x: 40
                y: 15
                width: 540
                text: qsTr( "支持秒/毫秒时间戳与常见日期时间格式互转。" )
                horizontalAlignment: Text.AlignLeft
                wrapMode: Text.WordWrap
            }

            MaterialLabel {
                x: 40
                y: 58
                text: qsTr( "时间戳 -> 日期时间" )
            }

            MaterialTextField {
                id: textFieldForTimestampString
                x: 40
                y: 84
                width: 330
                placeholderText: qsTr( "输入时间戳（秒或毫秒）" )

                onTextChanged: {
                    refreshDateTimeFromTimestamp();
                }
            }

            MaterialButton {
                x: 390
                y: 60
                width: 190
                height: 40
                text: qsTr( "当前秒级时间戳" )

                onClicked: {
                    textFieldForTimestampString.text = timestampTransformManage.currentSecondsTimestampString();
                }
            }

            MaterialButton {
                x: 390
                y: 105
                width: 190
                height: 40
                text: qsTr( "当前毫秒时间戳" )

                onClicked: {
                    textFieldForTimestampString.text = timestampTransformManage.currentMillisecondsTimestampString();
                }
            }

            MaterialLabel {
                id: labelForConvertedDateTimeString
                x: 40
                y: 170
                width: 330
                text: qsTr( "日期时间：" )
                wrapMode: Text.WordWrap
            }

            MaterialButton {
                x: 390
                y: 160
                width: 190
                height: 40
                text: qsTr( "复制日期时间" )

                onClicked: {
                    if ( convertedDateTimeStringValue === "" )
                    {
                        materialUI.showSnackbarMessage( qsTr( "当前没有可复制的日期时间" ) );
                        return;
                    }

                    timestampTransformManage.setClipboardText( convertedDateTimeStringValue );
                    materialUI.showSnackbarMessage( qsTr( "日期时间已复制到剪贴板" ) );
                }
            }

            Rectangle {
                x: 40
                y: 279
                width: 540
                height: 1
                color: "#e1e1e1"
            }
        }

        Item {
            id: itemForDateTimeToTimestamp
            width: 620
            height: 220

            MaterialLabel {
                x: 40
                y: 0
                text: qsTr( "日期时间 -> 时间戳" )
            }

            MaterialTextField {
                id: textFieldForDateTimeString
                x: 40
                y: 30
                width: 330
                placeholderText: qsTr( "输入日期时间（如 2026-02-24 12:00:00）" )

                onTextChanged: {
                    refreshTimestampFromDateTime();
                }
            }

            MaterialButton {
                x: 390
                y: 30
                width: 190
                height: 40
                text: qsTr( "填入当前时间" )

                onClicked: {
                    textFieldForDateTimeString.text = timestampTransformManage.currentDateTimeString();
                }
            }

            MaterialLabel {
                id: labelForSecondsTimestamp
                x: 40
                y: 120
                width: 330
                text: qsTr( "秒级时间戳：" )
                wrapMode: Text.WordWrap
            }

            MaterialButton {
                x: 390
                y: 85
                width: 190
                height: 40
                text: qsTr( "复制秒级时间戳" )

                onClicked: {
                    if ( secondsTimestampStringValue === "" )
                    {
                        materialUI.showSnackbarMessage( qsTr( "当前没有可复制的秒级时间戳" ) );
                        return;
                    }

                    timestampTransformManage.setClipboardText( secondsTimestampStringValue );
                    materialUI.showSnackbarMessage( qsTr( "秒级时间戳已复制到剪贴板" ) );
                }
            }

            MaterialLabel {
                id: labelForMillisecondsTimestamp
                x: 40
                y: 160
                width: 330
                text: qsTr( "毫秒时间戳：" )
                wrapMode: Text.WordWrap
            }

            MaterialButton {
                x: 390
                y: 130
                width: 190
                height: 40
                text: qsTr( "复制毫秒时间戳" )

                onClicked: {
                    if ( millisecondsTimestampStringValue === "" )
                    {
                        materialUI.showSnackbarMessage( qsTr( "当前没有可复制的毫秒时间戳" ) );
                        return;
                    }

                    timestampTransformManage.setClipboardText( millisecondsTimestampStringValue );
                    materialUI.showSnackbarMessage( qsTr( "毫秒时间戳已复制到剪贴板" ) );
                }
            }

            MaterialLabel {
                x: 40
                y: 200
                width: 540
                text: qsTr( "可识别格式：yyyy-MM-dd hh:mm:ss(.zzz)、yyyy/MM/dd hh:mm:ss(.zzz)" )
                wrapMode: Text.WordWrap
            }
        }
    }
}
