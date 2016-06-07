import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles
import "../Element"

Controls.Switch {
    id: control

    /*!
       The switch color. By default this is the app's accent color
     */
    property color color: "#2196f3"

    /*!
       Set to \c true if the switch is on a dark background
     */
    property bool darkBackground

    style: ControlStyles.SwitchStyle {
        handle: View {
            width: (22)
            height: (22)
            radius: height / 2
            elevation: 2
            backgroundColor: control.enabled ? control.checked ? control.color
                                                               : darkBackground ? "#BDBDBD"
                                                                                : "#FAFAFA"
                                             : darkBackground ? "#424242"
                                                              : "#BDBDBD"
        }

        groove: Item {
            width: (40)
            height: (22)

            Rectangle {
                anchors.centerIn: parent
                width: parent.width - (2)
                height: (16)
                radius: height / 2
                color: control.enabled ? control.checked ? alpha(control.color, 0.5)
                                                         : darkBackground ? Qt.rgba(1, 1, 1, 0.26)
                                                                          : Qt.rgba(0, 0, 0, 0.26)
                                       : darkBackground ? Qt.rgba(1, 1, 1, 0.12)
                                                        : Qt.rgba(0, 0, 0, 0.12)

                function alpha(color, alpha) {
                    var realColor = Qt.darker(color, 1)
                    realColor.a = alpha
                    return realColor
                }

                Behavior on color {
                    ColorAnimation {
                        duration: 200
                    }
                }
            }
        }
    }
}
