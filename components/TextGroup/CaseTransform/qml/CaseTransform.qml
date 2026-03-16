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

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQTextField {
            id: textFieldForLower
            x: 40
            y: 97
            width: 540
            placeholderText: "小写字符串"
            text: "abc"
        }

        JQButton {
            x: 40
            y: 55
            width: 140
            text: "复制到剪贴板"

            onClicked: {
                caseTransformManage.setClipboardText( textFieldForLower.text );
                JQGlobal.showMessage( "小写字符串已经复制到了剪贴板" );
            }
        }

        JQButton {
            x: 166
            y: 55
            width: 140
            text: "处理剪贴板"

            onClicked: {
                textFieldForSource.text = caseTransformManage.clipboardText();
                caseTransformManage.setClipboardText( textFieldForLower.text );
                JQGlobal.showMessage( "小写字符串已经复制到了剪贴板" );
            }
        }

        JQTextField {
            id: textFieldForSource
            x: 40
            y: 247
            width: 540
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

        JQButton {
            x: 40
            y: 205
            width: 140
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForSource.text = caseTransformManage.clipboardText();
                JQGlobal.showMessage( "已从剪贴板粘贴源字符串" );
            }
        }

        JQTextField {
            id: textFieldForUpper
            x: 40
            y: 403
            width: 540
            placeholderText: "大写字符串"
            text: "ABC"
        }

        JQButton {
            x: 40
            y: 361
            width: 140
            text: "复制到剪贴板"

            onClicked: {
                caseTransformManage.setClipboardText( textFieldForUpper.text );
                JQGlobal.showMessage( "大写字符串已经复制到了剪贴板" );
            }
        }

        JQButton {
            x: 166
            y: 361
            width: 140
            text: "处理剪贴板"

            onClicked: {
                textFieldForSource.text = caseTransformManage.clipboardText();
                caseTransformManage.setClipboardText( textFieldForUpper.text );
                JQGlobal.showMessage( "大写字符串已经复制到了剪贴板" );
            }
        }
    }
}
