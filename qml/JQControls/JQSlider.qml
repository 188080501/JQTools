import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Slider {
    id: jqSlider
    width: 240
    height: 40
    from: 0
    to: 100
    stepSize: 1
    value: defaultValue
    Material.accent: Material.LightBlue

    property real defaultValue: from
}
