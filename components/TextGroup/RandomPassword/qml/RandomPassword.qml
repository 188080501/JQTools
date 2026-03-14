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
import RandomPassword 1.0
import JQControls 1.0

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
            y: 92
            text: qsTr( "密码长度：" )

            MaterialTextField {
                id: textFieldForLength
                anchors.left: parent.right
                anchors.leftMargin: 10
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -22
                width: 60
                characterLimit: 3
                characterLimitVisible: false
                validator: RegExpValidator { regExp: /^([0-9]+)$/ }
                text: "11"
            }
        }

        MaterialCheckBox {
            id: checkBoxForNumber
            x: 34
            y: 141
            text: qsTr( "允许数字" )
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForEnglishCharacters
            x: 164
            y: 141
            text: qsTr( "允许英文字符" )
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForIncludeUppercaseLetters
            x: 312
            y: 141
            text: qsTr( "包含大写字母" )
            checked: true
            enabled: checkBoxForEnglishCharacters.checked
        }

        MaterialCheckBox {
            id: checkBoxForDividingLine
            x: 446
            y: 141
            text: qsTr( "插入分割线" )
            checked: true
        }

        MaterialCheckBox {
            id: checkBoxForSpecialCharacters
            x: 34
            y: 186
            text: qsTr( "允许特殊字符" )
            checked: false
        }

        MaterialCheckBox {
            id: checkBoxForExcludeAmbiguousCharacters
            x: 164
            y: 186
            text: qsTr( "排除易混淆字符" )
            checked: false
        }

        MaterialCheckBox {
            id: checkBoxForEnsureEachSelectedType
            x: 312
            y: 186
            text: qsTr( "每类至少一个字符" )
            checked: true
        }

        MaterialTextField {
            id: textFieldForCustomSpecialCharacters
            x: 40
            y: 240
            width: 540
            placeholderText: qsTr( "特殊字符集" )
            text: "!@#$%^&*()-_=+[]{}:,.?"
            enabled: checkBoxForSpecialCharacters.checked
        }

        MaterialTextField {
            id: textFieldForPassword
            x: 40
            y: 430
            width: 540
            placeholderText: qsTr( "随机密码" )
        }

        MaterialButton {
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
                    materialUI.showSnackbarMessage( qsTr( "生成失败，请检查长度和选项配置" ) );
                    return;
                }

                textFieldForPassword.text = randomPasswordString;
                materialUI.showSnackbarMessage( qsTr( "随机密码已经生成" ) );
            }
        }

        MaterialButton {
            x: 166
            y: 380
            width: 120
            text: qsTr( "复制到剪贴板" )

            onClicked: {
                randomPasswordManage.setClipboardText( textFieldForPassword.text );
                materialUI.showSnackbarMessage( qsTr( "密码已经复制到了剪贴板" ) );
            }
        }
    }
}
