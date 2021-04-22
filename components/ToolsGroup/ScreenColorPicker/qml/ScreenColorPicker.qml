/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 1.4

import "qrc:/MaterialUI/Interface/"
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

        Rectangle{
            id: colorlabel
            width: 70
            height: pickerButton.height
            x: 150
            y: 220
            border.color: "black"
            color: "blue"
        }

        MaterialTextField{
            x: 150
            y: 260
            text: colorlabel.color
            width: colorlabel.width
        }

        MaterialButton {
            x: 300
            y: 290
            text: "复制代码"
            onClicked: {
                screenColorPickerManage.copyColorToClipboard();
            }
        }

        MaterialButton {
            id: pickerButton
            x: 300
            y: 220
            text: "打开拾色器"
            onClicked: {
                screenColorPickerManage.openPicker();
            }
        }
    }
}
