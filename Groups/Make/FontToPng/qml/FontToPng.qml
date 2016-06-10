import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import FontToPng 1.0

Item {
    id: fontToPng
    width: 620
    height: 540

    FontToPngManage {
        id: fontToPngManage
    }

    MaterialLabel {
        x: 22
        y: 28
        text: "当前选择的字体集："
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
    }

    MaterialMenuField {
        x: 164
        y: 10
        width: 200
        maxVisibleItems: 5
        model: [
            "所有字体集",
            "Elusive",
            "FontAwesome",
            "Foundation",
            "GlyphiconsHalflings",
            "IcoMoon",
            "IconFont",
            "Icons8",
            "IconWorks",
            "JustVector",
            "MaterialDesign",
            "Metrize",
            "Mfglabs",
            "OpenIconic",
            "Socicon",
            "Typicons"
        ]
    }
}
