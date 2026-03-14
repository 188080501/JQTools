/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import BarcodeMaker 1.0

Item {
    id: barcodeMaker
    width: 620
    height: 540
    property bool loadingVisible: false

    BarcodeMakerManage {
        id: barcodeMakerManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQTextField {
            id: textFieldForBarcodeId
            x: 40
            y: 50
            width: 540
            placeholderText: "条形码ID\n目前仅支持EAN-13，并且需以6开头"
            text: "6901234567892"
        }

        Image {
            id: imageForBarcode
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -100
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 50
            width: 250
            height: 250
            fillMode: Image.PreserveAspectFit
            source: "image://BarcodeMaker/" + textFieldForBarcodeId.text

            JQButton {
                anchors.left: parent.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                width: 120
                text: "保存为PNG"

                onClicked: {
                    barcodeMaker.loadingVisible = true;

                    var reply = barcodeMakerManage.savePng(
                                textFieldForBarcodeId.text
                            );

                    barcodeMaker.loadingVisible = false;

                    switch ( reply )
                    {
                        case "cancel": JQGlobal.showMessage( "取消保存" ); break;
                        case "error": JQGlobal.showMessage( "保存失败" ); break;
                        case "OK": JQGlobal.showMessage( "保存成功" ); break;
                        default: break;
                    }
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            z: 999
            visible: barcodeMaker.loadingVisible
            color: "#55000000"

            JQLoadingIndicator {
                anchors.centerIn: parent
                text: "处理中..."
            }

            MouseArea {
                anchors.fill: parent
            }
        }
    }
}
