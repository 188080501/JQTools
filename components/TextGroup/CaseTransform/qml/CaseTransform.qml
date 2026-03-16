/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import CaseTransform 1.0

Item {
    id: caseTransform
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    CaseTransformManage {
        id: caseTransformManage
    }

    Column {
        anchors.centerIn: parent
        width: 540
        spacing: 22

        Row {
            spacing: 12

            JQButton {
                width: 140
                text: "复制到剪贴板"

                onClicked: {
                    caseTransformManage.setClipboardText( textFieldForLower.text );
                    JQGlobal.showMessage( "小写字符串已经复制到了剪贴板" );
                }
            }

            JQButton {
                width: 140
                text: "处理剪贴板"

                onClicked: {
                    textFieldForSource.text = caseTransformManage.clipboardText();
                    caseTransformManage.setClipboardText( textFieldForLower.text );
                    JQGlobal.showMessage( "小写字符串已经复制到了剪贴板" );
                }
            }
        }

        JQTextField {
            id: textFieldForLower
            width: parent.width
            placeholderText: "小写字符串"
            text: "abc"
        }

        JQButton {
            width: 140
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForSource.text = caseTransformManage.clipboardText();
                JQGlobal.showMessage( "已从剪贴板粘贴源字符串" );
            }
        }

        JQTextField {
            id: textFieldForSource
            width: parent.width
            placeholderText: "源字符串"
            text: "Abc"

            onTextChanged: {
                if ( caseTransform.changingFlag ) { return; }

                caseTransform.changingFlag = true;

                textFieldForLower.text = caseTransformManage.lower( textFieldForSource.text );
                textFieldForUpper.text = caseTransformManage.upper( textFieldForSource.text );

                caseTransform.changingFlag = false;
            }
        }

        Row {
            spacing: 12

            JQButton {
                width: 140
                text: "复制到剪贴板"

                onClicked: {
                    caseTransformManage.setClipboardText( textFieldForUpper.text );
                    JQGlobal.showMessage( "大写字符串已经复制到了剪贴板" );
                }
            }

            JQButton {
                width: 140
                text: "处理剪贴板"

                onClicked: {
                    textFieldForSource.text = caseTransformManage.clipboardText();
                    caseTransformManage.setClipboardText( textFieldForUpper.text );
                    JQGlobal.showMessage( "大写字符串已经复制到了剪贴板" );
                }
            }
        }

        JQTextField {
            id: textFieldForUpper
            width: parent.width
            placeholderText: "大写字符串"
            text: "ABC"
        }
    }
}
