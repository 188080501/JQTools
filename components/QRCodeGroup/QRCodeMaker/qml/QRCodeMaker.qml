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
import QRCodeMaker 1.0

Item {
    id: qrCodeMaker
    width: 620
    height: 540

    QRCodeMakerManage {
        id: qrCodeMakerManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialTextField {
            id: textFieldForSourceText
            x: 40
            y: 30
            width: 540
            placeholderText: "需要被编码的字符串"
            text: "JQTools"
        }

        MaterialLabel {
            x: 40
            y: 105
            text: "导出分辨率："
            height: 56
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
        }

        MaterialMenuField {
            id: menuFieldForResolution
            x: 145
            y: 105
            width: 130
            model: [
                "128",
                "256",
                "512",
                "1024",
                "2048",
                "4096"
            ]
            selectedIndex: 2
        }

        Image {
            id: imageForQRCode
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -100
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 80
            width: 250
            height: 250
            fillMode: Image.PreserveAspectFit
            source: "image://QRCodeMaker/" + textFieldForSourceText.text

            MaterialButton {
                anchors.left: parent.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                text: "保存为PNG"

                onClicked: {
                    materialUI.showLoading();

                    var reply = qrCodeMakerManage.savePng(
                                textFieldForSourceText.text,
                                parseInt( menuFieldForResolution.selectedText )
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
