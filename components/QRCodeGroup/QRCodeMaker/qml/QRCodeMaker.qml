/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import QRCodeMaker 1.0

Item {
    id: qrCodeMaker
    width: 620
    height: 540
    property bool loadingVisible: false

    QRCodeMakerManage {
        id: qrCodeMakerManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQTextField {
            id: textFieldForSourceText
            x: 40
            y: 30
            width: 540
            placeholderText: "需要被编码的字符串"
            text: "JQTools"
        }

        JQText {
            x: 40
            y: 105
            text: "导出分辨率："
            height: 56
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter

            JQComboBox {
                id: menuFieldForResolution
                anchors.left: parent.right
                anchors.leftMargin: 12
                anchors.verticalCenter: parent.verticalCenter
                width: 130
                model: [
                    "128",
                    "256",
                    "512",
                    "1024",
                    "2048",
                    "4096"
                ]
                currentIndex: 2
            }
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

            JQButton {
                anchors.left: parent.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                width: 120
                text: "保存为PNG"

                onClicked: {
                    qrCodeMaker.loadingVisible = true;

                    var reply = qrCodeMakerManage.savePng(
                                textFieldForSourceText.text,
                                parseInt( menuFieldForResolution.currentText )
                            );

                    qrCodeMaker.loadingVisible = false;

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
            visible: qrCodeMaker.loadingVisible
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
