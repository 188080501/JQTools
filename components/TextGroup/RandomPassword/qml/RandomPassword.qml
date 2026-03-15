/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
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

        JQText {
            x: 40
            y: 92
            text: qsTr( "密码长度：" )

            JQTextField {
                id: textFieldForLength
                anchors.left: parent.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                width: 60
                maximumLength: 3
                validator: IntValidator { bottom: 0 }
                text: "11"
            }
        }

        JQCheckBox {
            id: checkBoxForNumber
            x: 34
            y: 141
            text: qsTr( "允许数字" )
            checked: true
        }

        JQCheckBox {
            id: checkBoxForEnglishCharacters
            x: 224
            y: 141
            text: qsTr( "允许英文字符" )
            checked: true
        }

        JQCheckBox {
            id: checkBoxForIncludeUppercaseLetters
            x: 414
            y: 141
            text: qsTr( "包含大写字母" )
            checked: true
            enabled: checkBoxForEnglishCharacters.checked
        }

        JQCheckBox {
            id: checkBoxForDividingLine
            x: 34
            y: 186
            text: qsTr( "插入分割线" )
            checked: true
        }

        JQCheckBox {
            id: checkBoxForSpecialCharacters
            x: 224
            y: 186
            text: qsTr( "允许特殊字符" )
            checked: false
        }

        JQCheckBox {
            id: checkBoxForExcludeAmbiguousCharacters
            x: 414
            y: 186
            text: qsTr( "排除易混淆字符" )
            checked: false
        }

        JQCheckBox {
            id: checkBoxForEnsureEachSelectedType
            x: 34
            y: 231
            width: 190
            text: qsTr( "每类至少一个字符" )
            checked: true
        }

        JQTextField {
            id: textFieldForCustomSpecialCharacters
            x: 40
            y: 286
            width: 540
            placeholderText: qsTr( "特殊字符集" )
            text: "!@#$%^&*()-_=+[]{}:,.?"
            enabled: checkBoxForSpecialCharacters.checked
        }

        JQTextField {
            id: textFieldForPassword
            x: 40
            y: 430
            width: 540
            placeholderText: qsTr( "随机密码" )
        }

        JQButton {
            x: 40
            y: 380
            width: 120
            text: qsTr( "随机密码" )

            onClicked: {
                var randomPasswordString = randomPasswordManage.randomPassword(
                                parseInt( textFieldForLength.text ),
                                checkBoxForNumber.checked,
                                checkBoxForEnglishCharacters.checked,
                                checkBoxForIncludeUppercaseLetters.checked,
                                checkBoxForSpecialCharacters.checked,
                                textFieldForCustomSpecialCharacters.text,
                                checkBoxForExcludeAmbiguousCharacters.checked,
                                checkBoxForEnsureEachSelectedType.checked,
                                checkBoxForDividingLine.checked
                            );
                if ( randomPasswordString === "" )
                {
                    JQGlobal.showMessage( qsTr( "生成失败，请检查长度和选项配置" ) );
                    return;
                }

                textFieldForPassword.text = randomPasswordString;
                JQGlobal.showMessage( qsTr( "随机密码已经生成" ) );
            }
        }

        JQButton {
            x: 166
            y: 380
            width: 120
            text: qsTr( "复制到剪贴板" )

            onClicked: {
                randomPasswordManage.setClipboardText( textFieldForPassword.text );
                JQGlobal.showMessage( qsTr( "密码已经复制到了剪贴板" ) );
            }
        }
    }
}
