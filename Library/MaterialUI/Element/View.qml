/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014-2015 Michael Spencer <sonrisesoftware@gmail.com>
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
import QtGraphicalEffects 1.0

/*!
   \qmltype View
   \inqmlmodule Material 0.1

   \brief Provides a base view component, with support for Material Design elevation, 
   background colors, and tinting.
 */
Item {
    id: item
    width: 100
    height: 62

    property int elevation: 0
    property real radius: 0

    property string style: "default"

    property color backgroundColor: elevation > 0 ? "white" : "transparent"
    property color tintColor: "transparent"

    property alias border: rect.border

    property bool fullWidth
    property bool fullHeight

    property alias clipContent: rect.clip

    default property alias data: rect.data

    property bool elevationInverted: false

    property var bottomShadowData: [
        {
            "opacity": 0,
            "offset": 0,
            "blur": 0
        },

        {
            "opacity": 0.24,
            "offset": 1,
            "blur": 1
        },

        {
            "opacity": 0.23,
            "offset": 3,
            "blur": 3
        },

        {
            "opacity": 0.23,
            "offset": 6,
            "blur": 6
        },

        {
            "opacity": 0.22,
            "offset": 10,
            "blur": 10
        },

        {
            "opacity": 0.22,
            "offset": 15,
            "blur": 6
        }
    ]

    property var topShadowData: [
        {
            "opacity": 0,
            "offset": 0,
            "blur": 0
        },

        {
            "opacity": 0.12,
            "offset": 1,
            "blur": 1.5
        },

        {
            "opacity": 0.16,
            "offset": 3,
            "blur": 3
        },

        {
            "opacity": 0.19,
            "offset": 10,
            "blur": 10
        },

        {
            "opacity": 0.25,
            "offset": 14,
            "blur": 14
        },

        {
            "opacity": 0.30,
            "offset": 19,
            "blur": 19
        }
    ]

    Connections {
        onElevationChanged: {
            bottomShadowBlurAnimation.to = bottomShadowData[Math.min(elevation, 5)]["blur"];
            topShadowBlurAnimation.to = topShadowData[Math.min(elevation, 5)]["blur"];

            bottomShadowBlurAnimation.restart();
            topShadowBlurAnimation.restart();
        }

        Component.onCompleted: {
            bottomShadow.blur = bottomShadowData[Math.min(elevation, 5)]["blur"];
            topShadow.blur = topShadowData[Math.min(elevation, 5)]["blur"];
        }
    }

    NumberAnimation {
        id: bottomShadowBlurAnimation
        target: bottomShadow
        property: "blur"
        duration: 150
        easing.type: Easing.OutQuad
    }

    NumberAnimation {
        id: topShadowBlurAnimation
        target: topShadow
        property: "blur"
        duration: 150
        easing.type: Easing.OutQuad
    }

    RectangularGlow {
        id: bottomShadow
        property var elevationInfo: bottomShadowData[Math.min(elevation, 5)]
        property int blur: bottomShadowData[1]["blur"];
        property real horizontalShadowOffset: elevationInfo.offset * Math.sin((2 * Math.PI) * (parent.rotation / 360.0))
        property real verticalShadowOffset: elevationInfo.offset * Math.cos((2 * Math.PI) * (parent.rotation / 360.0))

        anchors.centerIn: parent
        width: parent.width + (fullWidth ? 10 : 0)
        height: parent.height + (fullHeight ? 20 : 0)
        anchors.horizontalCenterOffset: horizontalShadowOffset * (elevationInverted ? -1 : 1)
        anchors.verticalCenterOffset: verticalShadowOffset * (elevationInverted ? -1 : 1)
        glowRadius: blur
        opacity: elevationInfo.opacity
        spread: 0.05
        color: "black"
        cornerRadius: item.radius + glowRadius * 2.5
    }

    RectangularGlow {
        id: topShadow
        property var elevationInfo: topShadowData[Math.min(elevation, 5)]
        property int blur: topShadowData[1]["blur"];
        property real horizontalShadowOffset: elevationInfo.offset * Math.sin((2 * Math.PI) * (parent.rotation / 360.0))
        property real verticalShadowOffset: elevationInfo.offset * Math.cos((2 * Math.PI) * (parent.rotation / 360.0))

        anchors.centerIn: parent
        width: parent.width + (fullWidth ? 10 : 0)
        height: parent.height + (fullHeight ? 20 : 0)
        anchors.horizontalCenterOffset: horizontalShadowOffset * (elevationInverted ? -1 : 1)
        anchors.verticalCenterOffset: verticalShadowOffset * (elevationInverted ? -1 : 1)
        glowRadius: blur
        opacity: elevationInfo.opacity
        spread: 0.05
        color: "black"
        cornerRadius: item.radius + glowRadius * 2.5
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        color: Qt.tint(backgroundColor, tintColor)
        radius: item.radius
        antialiasing: parent.rotation || radius > 0 ? true : false
        clip: true

        Behavior on color {
            ColorAnimation { duration: 200 }
        }
    }
}
