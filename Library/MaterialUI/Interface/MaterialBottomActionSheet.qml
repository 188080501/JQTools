/*
 * QML Material - An application framework implementing Material Design.
 * Copyright (C) 2015 Michael Spencer <sonrisesoftware@gmail.com>
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

/*!
   \qmltype BottomActionSheet
   \inqmlmodule Material 0.1

   \brief Represents a bottom sheet displaying a list of actions with an optional title.

 */
BottomSheet {
    id: bottomSheet

    property string title

    property var callbackOnCancel: null
    property var callbackOnOK: null

    implicitHeight: title !== "" ? header.height + listViewContainer.implicitHeight
                                 : listViewContainer.implicitHeight

    function show(title, sheetData, callbackOnCancel, callbackOnOK) {
        bottomSheet.title = title;
        bottomSheet.callbackOnCancel = callbackOnCancel;
        bottomSheet.callbackOnOK = callbackOnOK;
        bottomSheet.open();

        materialUI.showDarkBackground(function() {
            bottomSheet.close();
            materialUI.hideDarkBackground();

            if (bottomSheet.callbackOnCancel)
            {
                bottomSheet.callbackOnCancel();
            }
        });

        listModel.clear();
        for (var index = 0; index < sheetData.length; index++)
        {
            listModel.append({
                                 itemIndex: index,
                                 itemText: sheetData[index]["text"],
                                 itemFlag: ("flag" in sheetData[index]) ? (sheetData[index]["flag"]) : (null),
                                 hasDividerAfter: ("hasDividerAfter" in sheetData[index]) ? (sheetData[index]["hasDividerAfter"]) : (false)
                             });
        }
    }

    Column {
        id: column

        anchors.fill: parent

        Subheader {
            id: header
            text: title
            visible: title !== ""
            height: (56)
            style: "subheading"
            backgroundColor: "white"
            elevation: listView.atYBeginning ? 0 : 1
            fullWidth: true
            z: 2
        }

        Item {
            id: listViewContainer

            width: parent.width
            height: title !== "" ? parent.height - header.height : parent.height

            implicitHeight: listView.contentHeight + listView.topMargin + listView.bottomMargin

            Flickable {
                id: listView
                width: parent.width
                height: parent.height

                interactive: bottomSheet.height < bottomSheet.implicitHeight

                topMargin: title !== "" ? 0 : (8)
                bottomMargin: (8)

                contentWidth: width
                contentHeight: subColumn.height

                Column {
                    id: subColumn
                    width: parent.width

                    Repeater {
                        model: ListModel {
                            id: listModel
                        }

                        delegate: Column {
                            width: subColumn.width

                            Standard {
                                id: listItem
                                text: itemText
                                visible: subColumn.visible
                                enabled: subColumn.enabled

                                onClicked: {
                                    actionSheet.close();

                                    materialUI.hideDarkBackground();

                                    if (callbackOnOK)
                                    {
                                        callbackOnOK(itemIndex, itemText, (((typeof itemFlag) !== "undefined") ? (itemFlag) : (null)));
                                    }
                                }
                            }

                            Divider {
                                visible: hasDividerAfter
                            }
                        }
                    }
                }
            }

            Scrollbar {
                flickableItem: listView
            }
        }
    }
}
