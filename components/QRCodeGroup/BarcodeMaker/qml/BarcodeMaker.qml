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
import BarcodeMaker 1.0

Item {
    id: barcodeMaker
    width: 620
    height: 540

    BarcodeMakerManage {
        id: barcodeMakerManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialTextField {
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

            MaterialButton {
                anchors.left: parent.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                text: "保存为PNG"

                onClicked: {
                    materialUI.showLoading();

                    var reply = barcodeMakerManage.savePng(
                                textFieldForBarcodeId.text
                            );

                    materialUI.hideLoading();

                    switch ( reply )
                    {
                        case "cancel": materialUI.showSnackbarMessage( "取消保存" ); break;
                        case "error": materialUI.showSnackbarMessage( "保存失败" ); break;
                        case "OK": materialUI.showSnackbarMessage( "保存成功" ); break;
                        default: break;
                    }
                }
            }
        }
    }
}
