/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014 Michael Spencer
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
import QtQuick.Controls 1.4

Label {
    id: label
    property string style: "body1"

    property var fontStyles: {
        "display4": {
            "size": 112,
            "font": "light"
        },

        "display3": {
            "size": 56,
            "font": "regular"
        },

        "display2": {
            "size": 45,
            "font": "regular"
        },

        "display1": {
            "size": 34,
            "font": "regular"
        },

        "headline": {
            "size": 24,
            "font": "regular"
        },

        "title": {
            "size": 20,
            "font": "regular"
        },

        "dialog": {
            "size": 18,
            "font": "regular"
        },

        "subheading": {
            "size": 16,
            "font": "regular"
        },

        "body2": {
            "size": 14,
            "font": "medium"
        },

        "body1": {
            "size": 14,
            "font": "regular"
        },

        "caption": {
            "size": 12,
            "font": "regular"
        },

        "menu": {
            "size": 14,
            "font": "medium"
        },

        "button": {
            "size": 14,
            "font": "medium"
        },

        "tooltip": {
            "size": 14,
            "font": "medium"
        },
    }

    property var fontInfo: fontStyles[style]

    renderType: Text.QtRendering

    font.pixelSize: fontInfo.size
    font.family: {
        switch (Qt.platform.os)
        {
            case "windows": return "微软雅黑";
            default: return "Roboto";
        }
    }

    color: "#d8000000"
}
