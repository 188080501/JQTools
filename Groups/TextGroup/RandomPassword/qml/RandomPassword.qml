import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import RandomPassword 1.0

Item {
    id: randomPassword
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    RandomPasswordManage {
        id: randomPasswordManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialLabel {
            x: 40
            y: 132
            text: "密码长度："
        }

        MaterialTextField {
            id: textFieldForLength
            x: 116
            y: 91
            width: 50
            characterLimit: 2
            characterLimitVisible: false
            validator: RegExpValidator{ regExp: /^([0-9]+)$/ }
            text: "15"
        }

        MaterialTextField {
            id: textFieldForPassword
            x: 40
            y: 317
            width: 540
            placeholderText: "随机密码"
        }

        MaterialCheckBox {
            id: checkBoxForNumber
            x: 34
            y: 181
            text: "允许数字"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForEnglishCharacters
            x: 154
            y: 181
            text: "允许英文字符"
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForCaseSensitive
            x: 302
            y: 181
            text: "区分大小写"
            checked: true
            enabled: checkBoxForEnglishCharacters.checked
        }

        MaterialCheckBox {
            id: checkBoxForDividingLine
            x: 436
            y: 181
            text: "插入分割线"
            checked: true
        }

        MaterialButton {
            x: 40
            y: 259
            width: 120
            text: "随机密码"

            onClicked: {
                textFieldForPassword.text = randomPasswordManage.randomPassword(
                                parseInt( textFieldForLength.text ),
                                checkBoxForNumber.checked,
                                checkBoxForEnglishCharacters.checked,
                                checkBoxForCaseSensitive.checked,
                                checkBoxForDividingLine.checked
                            );
                materialUI.showSnackbarMessage( "随机密码已经生成" );
            }
        }

        MaterialButton {
            x: 166
            y: 259
            width: 120
            text: "复制到剪切板"

            onClicked: {
                randomPasswordManage.setClipboardText( textFieldForPassword.text );
                materialUI.showSnackbarMessage( "URL已经复制到了剪切板" );
            }
        }
    }
}
