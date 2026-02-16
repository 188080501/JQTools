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
import QRCodeReader 1.0

Item {
    id: qrCodeReader
    width: 620
    height: 540

    QRCodeReaderManage {
        id: qrCodeReaderManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialTextField {
            id: textFieldForTag
            x: 40
            y: 50
            width: 540
            placeholderText: "被识别的标记"

            Component.onCompleted: {
                text = qrCodeReaderManage.decodeImage( "qrc:/QRCodeReaderImages/test.png" );
            }
        }

        Image {
            id: imageForQRCode
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -100
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 50
            width: 250
            height: 250
            source: "qrc:/QRCodeReaderImages/test.png"

            MaterialButton {
                anchors.left: parent.right
                anchors.leftMargin: 50
                anchors.verticalCenter: parent.verticalCenter
                text: "选取图片"

                onClicked: {
                    imageForQRCode.source = qrCodeReaderManage.chooseImage();

                    if ( imageForQRCode.source.toString() !== "" )
                    {
                        textFieldForTag.text = qrCodeReaderManage.decodeImage( imageForQRCode.source );
                    }
                    else
                    {
                        textFieldForTag.text = "";
                        materialUI.showSnackbarMessage( "用户取消操作" );
                    }
                }
            }
        }
    }
}
