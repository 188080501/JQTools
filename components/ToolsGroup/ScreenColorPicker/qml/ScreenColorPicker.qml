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

    MaterialButton {
       width: 120
       height: 40
       text: "打开取色器"
       //anchors.horizontalCenterOffset: 134
       //anchors.verticalCenterOffset: 32
       anchors.horizontalCenter: parent.horizontalCenter
       anchors.verticalCenter: parent.verticalCenter
       onClicked: {
           screenColorPickerManage.openPicker();
       }
    }
}
