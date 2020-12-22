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

        MaterialTextField {
            id: textFieldForPassword
            x: 40
            y: 317
            width: 540
            placeholderText: "随机UUID"
        }

        MaterialCheckBox {
            id: checkBoxForNumber
            x: 34
            y: 181
            text: "包括大括号"
            checked: false
        }

        MaterialButton {
            x: 40
            y: 259
            width: 120
            text: "随机UUID"

            onClicked: {
                textFieldForPassword.text = randomUuidManage.randomUuid(
                                checkBoxForNumber.checked
                            );
                materialUI.showSnackbarMessage( "随机UUID已经生成" );
            }
        }

        MaterialButton {
            x: 166
            y: 259
            width: 120
            text: "复制到剪切板"

            onClicked: {
                randomUuidManage.setClipboardText( textFieldForPassword.text );
                materialUI.showSnackbarMessage( "UUID已经复制到了剪切板" );
            }
        }
    }
}
