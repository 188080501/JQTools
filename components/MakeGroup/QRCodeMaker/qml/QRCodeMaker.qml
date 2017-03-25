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
}
