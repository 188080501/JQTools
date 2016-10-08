/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2014 Bogdan Cuza <bogdan.cuza@hotmail.com>
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
import "../Element"

/*
 * Note that this is a FocusScope, not a TextInput. If you need to read or
 * write properties of the input itself, use the input property.
 */
FocusScope {
   id: field

   property color accentColor: "#2196f3"
   property color errorColor: "#F44336"

   property alias readOnly: textInput.readOnly

   property alias text: textInput.text
   property alias echoMode: textInput.echoMode

   property alias validator: textInput.validator

   property alias placeholderText: fieldPlaceholder.text
   property alias helperText: helperTextLabel.text

   readonly property int characterCount: text.length

   property bool floatingLabel: true
   property bool hasError: false
   property int characterLimit: -1
   property bool characterLimitVisible: true

   readonly property rect inputRect: Qt.rect(textInput.x, textInput.y, textInput.width, textInput.height)

   readonly property alias input: textInput

   signal accepted()
   signal editingFinished()

   implicitHeight: __internal.showHelperText ? helperTextLabel.y + helperTextLabel.height + (4)
                          : underline.y + (8)
   width: (200)
   height: (56)

   QtObject {
       id: __internal

       property bool showHelperText: helperText.length > 0
       property bool showCharacterCounter: (characterLimit > 0) && characterLimitVisible
   }

   MouseArea {
      anchors.fill: parent
      onClicked: field.forceActiveFocus(Qt.MouseFocusReason)
   }

   TextInput {
      id: textInput

      focus: true

      color: "#d8000000"
      selectedTextColor: "white"
      selectionColor: Qt.darker(field.accentColor, 1)

//      selectByMouse: Device.type === Device.desktop
      selectByMouse: true

      activeFocusOnTab: true

      maximumLength: (characterLimit !== -1) ? (characterLimit) : (32767)
      width: parent.width

      clip: true

      y: {
         if ( !floatingLabel )
            return (16)
         if ( floatingLabel && !__internal.showHelperText )
            return (40)
         return (28)
      }

      font {
         family: {
             if ((echoMode == TextInput.Password) && (field.text.length > 0))
             {
                 return "";
             }

             switch (Qt.platform.os)
             {
                 case "windows": return "微软雅黑";
                 default: return "Roboto";
             }
         }

         pixelSize: (16)
      }

      onAccepted: field.accepted()
      onEditingFinished: field.editingFinished()

      MouseArea {
          anchors.fill: parent
          cursorShape: Qt.IBeamCursor
          acceptedButtons: Qt.NoButton
      }
   }

   MaterialLabel {
      id: fieldPlaceholder

      text: field.placeholderText

      font.pixelSize: (16)

      anchors.baseline: textInput.baseline
      anchors.bottomMargin: (8)

      color: "#42000000"

      states: [
         State {
            name: "floating"
            when: textInput.displayText.length > 0 && floatingLabel
            AnchorChanges {
               target: fieldPlaceholder
               anchors.baseline: undefined
               anchors.bottom: textInput.top
            }
            PropertyChanges {
               target: fieldPlaceholder
               font.pixelSize: (12)
            }
         },
         State {
            name: "hidden"
            when: textInput.displayText.length > 0 && !floatingLabel
            PropertyChanges {
               target: fieldPlaceholder
               visible: false
            }
         }
      ]

      transitions: [
         Transition {
            id: floatingTransition
            enabled: false
            AnchorAnimation {
               duration: 200
            }
            NumberAnimation {
               duration: 200
               property: "font.pixelSize"
            }
         }
      ]

      Component.onCompleted: floatingTransition.enabled = true
   }

   Rectangle {
      id: underline
      color: field.hasError || (__internal.showCharacterCounter && field.characterCount > field.characterLimit)
             ? field.errorColor : field.activeFocus ? field.accentColor : "#42000000"

      height: field.activeFocus ? (2) : (1)

      anchors {
         left: parent.left
         right: parent.right
         top: textInput.bottom
         topMargin: (8)
      }

      Behavior on height {
         NumberAnimation { duration: 200 }
      }

      Behavior on color {
         ColorAnimation { duration: 200 }
      }
   }

   MaterialLabel {
      id: helperTextLabel
      visible: __internal.showHelperText
      font.pixelSize: (12)
      color: field.hasError ? field.errorColor : Qt.darker("#42000000")
      anchors {
         left: parent.left
         right: parent.right
         top: underline.top
         topMargin: (4)
      }

      Behavior on color {
         ColorAnimation { duration: 200 }
      }
   }

   MaterialLabel {
      id: characterCounterLabel
      visible: __internal.showCharacterCounter
      font.pixelSize: (12)
      font.weight: Font.Light
      color: field.characterCount <= field.characterLimit ? Qt.darker("#42000000") : field.errorColor
      text: field.characterCount + " / " + field.characterLimit
      anchors {
         right: parent.right
         top: underline.top
         topMargin: (8)
      }

      Behavior on color {
         ColorAnimation { duration: 200 }
      }
   }
}
