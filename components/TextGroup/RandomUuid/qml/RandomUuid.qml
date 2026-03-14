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

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQTextField {
            id: textFieldForUuid
            x: 40
            y: 317
            width: 540
            placeholderText: "随机UUID"
        }

        JQCheckBox {
            id: checkBoxForNumber
            x: 34
            y: 181
            text: "包括大括号"
            checked: false
        }

        JQButton {
            x: 40
            y: 259
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
            x: 166
            y: 259
            width: 120
            text: "复制到剪贴板"

            onClicked: {
                randomUuidManage.setClipboardText( textFieldForUuid.text );
                JQGlobal.showMessage( "UUID已经复制到了剪贴板" );
            }
        }
    }
}
