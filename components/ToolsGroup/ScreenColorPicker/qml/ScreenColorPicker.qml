/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import ScreenColorPicker 1.0

Item {
    id: screenColorPicker
    width: 620
    height: 540

    ScreenColorPickerManage {
        id: screenColorPickerManage
    }

    Item{
        anchors.centerIn: parent
        width: 620
        height: 540

        Connections{
            target: screenColorPickerManage
            function onColorSelect(c){
                colorlabel.color = c;
            }
        }

        Rectangle {
            id: colorlabel
            x: 130
            y: 220
            width: 70
            height: pickerButton.height
            border.color: "black"
            color: "blue"
        }

        JQTextField {
            x: 130
            y: colorlabel.y + colorlabel.height + 10
            text: colorlabel.color
            width: 120
        }

        JQButton {
            x: 320
            y: 290
            width: 120
            text: "复制代码"

            onClicked: {
                screenColorPickerManage.copyColorToClipboard();
                JQGlobal.showMessage( qsTr( "复制完成" ) );
            }
        }

        JQButton {
            id: pickerButton
            x: 320
            y: 220
            width: 120
            text: "打开拾色器"

            onClicked: {
                screenColorPickerManage.openPicker();
            }
        }
    }
}
