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
import CppFileMaker 1.0

Item {
    id: cppFileMaker
    width: 620
    height: 540

    CppFileMakerManage {
        id: cppFileMakerManage
    }

    Column {
        anchors.centerIn: parent
        spacing: 36

        MaterialLabel {
            width: 200
            text: "生成CPP文件基本结构\n默认保存在桌面"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        MaterialTextField {
            id: textFieldForMacroProtectsPrefix
            width: 200
            height: 36
            placeholderText: "头文件保护前缀"
            text: "MyGroup"
        }

        MaterialTextField {
            id: textFieldForClassName
            width: 200
            height: 36
            placeholderText: "类名"
            text: "MyClass"
        }

        Item {
            width: 1
            height: 1
        }

        MaterialCheckBox {
            id: checkBoxForQmlExpand
            text: "QML扩展"
        }

        MaterialButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "生成"

            onClicked: {
                cppFileMakerManage.make(
                            textFieldForMacroProtectsPrefix.text,
                            textFieldForClassName.text,
                            checkBoxForQmlExpand.checked
                        );
            }
        }
    }
}
