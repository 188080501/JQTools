import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import TimestampTransform 1.0

Item {
    id: timestampTransform
    width: 620
    height: 540

    property bool changingFlag: false

    TimestampTransformManage {
        id: timestampTransformManage
    }

    MaterialTextField {
        id: textFieldForTimestampString
        x: 235
        y: 223
        width: 150
        placeholderText: "时间戳字符串"

        onTextChanged: {
            if ( timestampTransform.changingFlag ) { return; }

            timestampTransform.changingFlag = true;

            labelForDateTimeString.text = timestampTransformManage.dateTimeStringFromTimestampString( textFieldForTimestampString.text );

            timestampTransform.changingFlag = false;
        }

        Component.onCompleted: {
            textFieldForTimestampString.text = timestampTransformManage.currentDateTimeTimestampString();
        }
    }

    MaterialButton {
        x: 235
        y: 166
        width: 150
        text: "从剪切板黏贴"

        onClicked: {
            textFieldForTimestampString.text = timestampTransformManage.clipboardText();
            materialUI.showSnackbarMessage( "已从剪切板复制了时间戳字符串" );
        }
    }

    MaterialLabel {
        id: labelForDateTimeString
        x: 235
        y: 325
        width: 150
        height: 50
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenters
    }
}
