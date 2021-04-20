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

    Component.onCompleted: {
        changingFlag = false;
    }

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
            width: 50
            height: pickerButton.height
            x: 150
            y: 220
            border.color: "black"
            color: "blue"
        }

        MaterialButton {
            x: 230
            y: 220
            text: "复制"
            onClicked: {
                screenColorPickerManage.openPicker();
            }
        }

        MaterialButton {
            id: pickerButton
            x: 350
            y: 220
            text: "打开拾色器"
            onClicked: {
                screenColorPickerManage.openPicker();
            }
        }
    }
}
