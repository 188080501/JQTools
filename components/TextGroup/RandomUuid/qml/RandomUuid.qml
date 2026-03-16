/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import RandomUuid 1.0

Item {
    id: randomUuid
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    RandomUuidManage {
        id: randomUuidManage
    }

    Column {
        anchors.centerIn: parent
        width: 540
        spacing: 22

        JQCheckBox {
            id: checkBoxForNumber
            text: "包括大括号"
            checked: false
        }

        Row {
            spacing: 12

            JQButton {
                width: 120
                text: "随机UUID"

                onClicked: {
                    textFieldForUuid.text = randomUuidManage.randomUuid(
                                    checkBoxForNumber.checked
                                );
                    JQGlobal.showMessage( "随机UUID已经生成" );
                }
            }

            JQButton {
                width: 140
                text: "复制到剪贴板"

                onClicked: {
                    randomUuidManage.setClipboardText( textFieldForUuid.text );
                    JQGlobal.showMessage( "UUID已经复制到了剪贴板" );
                }
            }
        }

        JQTextField {
            id: textFieldForUuid
            width: parent.width
            placeholderText: "随机UUID"
        }
    }
}
