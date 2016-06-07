/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014 Jordan Neidlinger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 2.1 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
import QtQuick 2.5
import QtQuick.Controls 1.4 as Controls
import QtQuick.Controls.Styles 1.4 as ControlStyles
import "../Element"

Controls.RadioButton {
    id: radioButton

    /*!
       The switch color. By default this is the app's accent color
     */
    property color color: "#2196f3"

    /*!
       Set to \c true if the switch is on a dark background
     */
    property bool darkBackground

    style: ControlStyles.RadioButtonStyle {
        label: MaterialLabel {
            text: control.text
            color: control.enabled ? radioButton.darkBackground ? "#ffffff"
                                                                : "#d8000000"
                                   : radioButton.darkBackground ? "#4cffffff"
                                                                : "#42000000"
        }

        background: Rectangle {
            color: "transparent"
        }

        indicator: Rectangle {
            implicitWidth: (48)
            implicitHeight: (48)
            radius: implicitHeight / 2
            color: control.activeFocus ? alpha(radioButton.color, 0.20) : "transparent"

            function alpha(color, alpha) {
                var realColor = Qt.darker(color, 1)
                realColor.a = alpha
                return realColor
            }

            Rectangle {
                anchors.centerIn: parent
                implicitWidth: (20)
                implicitHeight: (20)
                radius: implicitHeight / 2
                color: "transparent"
                border.color: control.enabled
                    ? control.checked ? radioButton.color
                                      : radioButton.darkBackground ? "#b2ffffff"
                                                                   : "#89000000"
                    : radioButton.darkBackground ? "#4cffffff"
                                                 : "#42000000"
                border.width: (2)
                antialiasing: true

                Behavior on border.color {
                    ColorAnimation { duration: 200}
                }

                Rectangle {
                    anchors.centerIn: parent
                    implicitWidth: control.checked ? (10) : 0
                    implicitHeight: control.checked ? (10) : 0
                    color: control.enabled ? radioButton.color
                                           : radioButton.darkBackground ? "#4cffffff"
                                                                        : "#42000000"
                    radius: implicitHeight / 2
                    antialiasing: true

                    Behavior on implicitWidth {
                        NumberAnimation { easing.type: Easing.InOutQuad; duration: 200 }
                    }

                    Behavior on implicitHeight {
                        NumberAnimation { easing.type: Easing.InOutQuad; duration: 200 }
                    }
                }
            }
        }

        spacing: 0
    }

    Ink {
        anchors {
            left: parent.left
            leftMargin: (4)
            verticalCenter: parent.verticalCenter
        }

        width: (40)
        height: (40)
        color: radioButton.checked ? alpha(radioButton.color, 0.20) : Qt.rgba(0,0,0,0.1)

        circular: true
        centered: true

        onClicked: {
            if (radioButton.canToggle || !radioButton.checked)
                radioButton.checked = !radioButton.checked
        }
    }
}
