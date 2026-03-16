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

    Column {
        anchors.centerIn: parent
        width: 520
        spacing: 14

        Row {
            spacing: 16

            Column {
                spacing: 14

                JQTextField {
                    id: textFieldForColorName
                    width: 180
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

                Row {
                    spacing: 12

                    Rectangle {
                        width: 25
                        height: 25
                        color: textFieldForHexString.text
                        border.width: 1
                        border.color: "#000000"
                    }

                    JQTextField {
                        id: textFieldForHexString
                        width: 180
                        placeholderText: "颜色十六进制字符串"
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
                    }
                }

                Row {
                    spacing: 6

                    JQTextField {
                        id: textFieldForRed
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
                }
            }

            Column {
                spacing: 12

                JQButton {
                    width: 140
                    text: "颜色对话框"

                    onClicked: {
                        const chosenHexString = rgbStringTransformManage.getHexStringFromColorDialog(
                                    textFieldForHexString.text
                                );
                        if ( chosenHexString === "" ) { return; }
                        textFieldForHexString.text = chosenHexString;
                    }
                }

                JQButton {
                    width: 140
                    text: "从剪贴板粘贴"

                    onClicked: {
                        textFieldForHexString.text = rgbStringTransformManage.clipboardText();
                        JQGlobal.showMessage( "已从剪贴板粘贴颜色字符串" );
                    }
                }

                JQButton {
                    width: 140
                    text: "复制到剪贴板"

                    onClicked: {
                        rgbStringTransformManage.setClipboardText( textFieldForHexString.text );
                        JQGlobal.showMessage( "颜色十六进制字符串已经复制到了剪贴板" );
                    }
                }
            }
        }
    }
}
