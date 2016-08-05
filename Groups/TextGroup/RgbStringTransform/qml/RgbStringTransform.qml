import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import RgbStringTransform 1.0

Item {
    id: rgbStringTransform
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    RgbStringTransformManage {
        id: rgbStringTransformManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialTextField {
            id: textFieldForColorName
            x: 202
            y: 124
            width: 100
            text: "white"
            placeholderText: "颜色描述"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForHexString.text = rgbStringTransformManage.getHexStringFromColorName( textFieldForColorName.text );
                textFiedForRed.text = rgbStringTransformManage.getRed( textFieldForHexString.text );
                textFiedForGreen.text = rgbStringTransformManage.getGreen( textFieldForHexString.text );
                textFiedForBlue.text = rgbStringTransformManage.getBlue( textFieldForHexString.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFieldForHexString
            x: 202
            y: 214
            placeholderText: "颜色十六进制字符串"
            width: 100
            text: "#ffffff"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFiedForRed.text = rgbStringTransformManage.getRed( textFieldForHexString.text );
                textFiedForGreen.text = rgbStringTransformManage.getGreen( textFieldForHexString.text );
                textFiedForBlue.text = rgbStringTransformManage.getBlue( textFieldForHexString.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForRed
            x: 156
            y: 313
            placeholderText: "红(R)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForGreen
            x: 222
            y: 313
            placeholderText: "绿(G)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForBlue
            x: 288
            y: 313
            placeholderText: "蓝(B)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialButton {
            x: 387
            y: 209
            width: 120
            text: "从剪切板黏贴"

            onClicked: {
                textFieldForHexString.text = rgbStringTransformManage.clipboardText();
                materialUI.showSnackbarMessage( "已从剪切板复制了颜色字符串" );
            }
        }

        MaterialButton {
            x: 387
            y: 276
            width: 120
            text: "复制到剪切板"

            onClicked: {
                rgbStringTransformManage.setClipboardText( textFieldForHexString.text );
                materialUI.showSnackbarMessage( "颜色十六进制字符串已经复制到了剪切板" );
            }
        }

        Rectangle {
            x: 165
            y: 252
            width: 25
            height: 25
            color: textFieldForHexString.text
            border.width: 1
            border.color: "#000000"
        }
    }
}
