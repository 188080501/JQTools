import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"

Item {
    width: 300
    height: 400

    MaterialLabel {
        x: 28
        y: 50
        text: "字体集："
        font.pixelSize: 16
    }

    MaterialLabel {
        id: labelForFamilieName
        x: 145
        y: 13
        width: 120
        height: 56
        text: dialogForSaveIcon.familieName
    }

    MaterialLabel {
        x: 28
        y: 112
        text: "字符代码："
        font.pixelSize: 16
    }

    MaterialLabel {
        id: labelForCharCode
        x: 145
        y: 75
        width: 120
        height: 56
        text: "(\\u" + dialogForSaveIcon.charCode + ")"
    }

    MaterialLabel {
        x: 28
        y: 174
        text: "字符名称："
        font.pixelSize: 16
    }

    MaterialLabel {
        id: labelForCharName
        x: 145
        y: 137
        width: 120
        height: 56
        text: dialogForSaveIcon.charName
    }
}
