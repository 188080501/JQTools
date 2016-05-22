import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
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

        MaterialTextField {
            id: textFieldForLower
            x: 40
            y: 97
            width: 540
            placeholderText: "小写字符串"
            text: "abc"
        }

        MaterialButton {
            x: 40
            y: 55
            width: 120
            text: "复制到剪切板"

            onClicked: {
                caseTransformManage.setClipboardText( textFieldForLower.text );
                materialUI.showSnackbarMessage( "小写字符串已经复制到了剪切板" );
            }
        }

        MaterialTextField {
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

        MaterialButton {
            x: 40
            y: 205
            width: 120
            text: "从剪切板黏贴"

            onClicked: {
                textFieldForSource.text = caseTransformManage.clipboardText();
                materialUI.showSnackbarMessage( "已从剪切板复制了源字符串" );
            }
        }

        MaterialTextField {
            id: textFieldForUpper
            x: 40
            y: 403
            width: 540
            placeholderText: "大写字符串"
            text: "ABC"
        }

        MaterialButton {
            x: 40
            y: 361
            width: 120
            text: "复制到剪切板"

            onClicked: {
                caseTransformManage.setClipboardText( textFieldForUpper.text );
                materialUI.showSnackbarMessage( "大写字符串已经复制到了剪切板" );
            }
        }
    }
}
