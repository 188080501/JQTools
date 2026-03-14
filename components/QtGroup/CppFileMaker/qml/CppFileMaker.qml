/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
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
        spacing: 24

        JQText {
            width: 200
            text: "生成CPP文件基本结构\n默认保存在桌面"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        JQTextField {
            id: textFieldForMacroProtectsPrefix
            width: 200
            text: "MyGroup"

            JQText {
                anchors.right: parent.left
                anchors.rightMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                text: "头文件保护前缀："
            }
        }

        JQTextField {
            id: textFieldForClassName
            width: 200
            text: "MyClass"

            JQText {
                anchors.right: parent.left
                anchors.rightMargin: 8
                anchors.verticalCenter: parent.verticalCenter
                text: "类名："
            }
        }

        Item {
            width: 1
            height: 1
        }

        JQCheckBox {
            id: checkBoxForQmlExpand
            text: "QML扩展"
        }

        JQButton {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "生成"

            onClicked: {
                cppFileMakerManage.make(
                            textFieldForMacroProtectsPrefix.text,
                            textFieldForClassName.text,
                            checkBoxForQmlExpand.checked
                        );
                JQGlobal.showMessage( "生成成功" );
            }
        }
    }
}
