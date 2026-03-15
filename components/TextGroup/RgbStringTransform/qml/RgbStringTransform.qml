/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
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

        JQTextField {
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
                textFieldForRed.text = rgbStringTransformManage.getRed( textFieldForHexString.text );
                textFieldForGreen.text = rgbStringTransformManage.getGreen( textFieldForHexString.text );
                textFieldForBlue.text = rgbStringTransformManage.getBlue( textFieldForHexString.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        JQTextField {
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
                textFieldForRed.text = rgbStringTransformManage.getRed( textFieldForHexString.text );
                textFieldForGreen.text = rgbStringTransformManage.getGreen( textFieldForHexString.text );
                textFieldForBlue.text = rgbStringTransformManage.getBlue( textFieldForHexString.text );

                rgbStringTransform.changingFlag = false;
            }

            Rectangle {
                anchors.right: textFieldForHexString.left
                anchors.rightMargin: 16
                anchors.verticalCenter: parent.verticalCenter
                width: 25
                height: 25
                color: textFieldForHexString.text
                border.width: 1
                border.color: "#000000"
            }
        }

        JQTextField {
            id: textFieldForRed
            x: 156
            y: 313
            placeholderText: "红(R)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFieldForRed.text, textFieldForGreen.text, textFieldForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        JQTextField {
            id: textFieldForGreen
            x: 222
            y: 313
            placeholderText: "绿(G)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFieldForRed.text, textFieldForGreen.text, textFieldForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        JQTextField {
            id: textFieldForBlue
            x: 288
            y: 313
            placeholderText: "蓝(B)"
            width: 60
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForColorName.text = "";
                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFieldForRed.text, textFieldForGreen.text, textFieldForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        JQButton {
            x: 387
            y: 130
            width: 120
            text: "颜色对话框获取"

            onClicked: {
                const chosenHexString = rgbStringTransformManage.getHexStringFromColorDialog(
                            textFieldForHexString.text
                        );
                if ( chosenHexString === "" ) { return; }
                textFieldForHexString.text = chosenHexString;
            }
        }

        JQButton {
            x: 387
            y: 209
            width: 120
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForHexString.text = rgbStringTransformManage.clipboardText();
                JQGlobal.showMessage( "已从剪贴板粘贴颜色字符串" );
            }
        }

        JQButton {
            x: 387
            y: 276
            width: 120
            text: "复制到剪贴板"

            onClicked: {
                rgbStringTransformManage.setClipboardText( textFieldForHexString.text );
                JQGlobal.showMessage( "颜色十六进制字符串已经复制到了剪贴板" );
            }
        }
    }
}
