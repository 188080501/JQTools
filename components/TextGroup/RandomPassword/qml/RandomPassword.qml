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

    Column {
        anchors.centerIn: parent
        width: 540
        spacing: 16

        Row {
            spacing: 10

            JQText {
                text: qsTr( "密码长度：" )
                anchors.verticalCenter: parent.verticalCenter
            }

            JQTextField {
                id: textFieldForLength
                width: 60
                maximumLength: 3
                validator: IntValidator { bottom: 0 }
                text: "11"
            }
        }

        Grid {
            columns: 3
            columnSpacing: 20
            rowSpacing: 10

            JQCheckBox {
                id: checkBoxForNumber
                text: qsTr( "允许数字" )
                checked: true
            }

            JQCheckBox {
                id: checkBoxForEnglishCharacters
                text: qsTr( "允许英文字符" )
                checked: true
            }

            JQCheckBox {
                id: checkBoxForIncludeUppercaseLetters
                text: qsTr( "包含大写字母" )
                checked: true
                enabled: checkBoxForEnglishCharacters.checked
            }

            JQCheckBox {
                id: checkBoxForDividingLine
                text: qsTr( "插入分割线" )
                checked: true
            }

            JQCheckBox {
                id: checkBoxForSpecialCharacters
                text: qsTr( "允许特殊字符" )
                checked: false
            }

            JQCheckBox {
                id: checkBoxForExcludeAmbiguousCharacters
                text: qsTr( "排除易混淆字符" )
                checked: false
            }
        }

        JQCheckBox {
            id: checkBoxForEnsureEachSelectedType
            width: 190
            text: qsTr( "每类至少一个字符" )
            checked: true
        }

        JQTextField {
            id: textFieldForCustomSpecialCharacters
            width: parent.width
            placeholderText: qsTr( "特殊字符集" )
            text: "!@#$%^&*()-_=+[]{}:,.?"
            enabled: checkBoxForSpecialCharacters.checked
        }

        Row {
            spacing: 12

            JQButton {
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
                width: 140
                text: qsTr( "复制到剪贴板" )

                onClicked: {
                    randomPasswordManage.setClipboardText( textFieldForPassword.text );
                    JQGlobal.showMessage( qsTr( "密码已经复制到了剪贴板" ) );
                }
            }
        }

        JQTextField {
            id: textFieldForPassword
            width: parent.width
            placeholderText: qsTr( "随机密码" )
        }
    }
}
