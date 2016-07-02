import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"

Item {
    id: fontToPng
    width: 620
    height: 540
    clip: true

    function refresh() {
        var charList = FontToPngManage.getCharList( menuFieldForFamilieName.selectedText, textFieldForSearchKey.text );

        listModel.clear();
        for ( var index = 0; index < charList.length; ++index )
        {
            listModel.append( {
                                 familieName: charList[ index ][ "familieName" ],
                                 charCode: charList[ index ][ "charCode" ],
                                 charName: charList[ index ][ "charName" ],
                                 charPreviewUrl: charList[ index ][ "charPreviewUrl" ]
                              } );
        }

        labelForIconCount.iconCount = charList.length;
    }

    Component.onCompleted: {
        materialUI.showLoading();

        FontToPngManage.begin();
        fontToPng.refresh();

        materialUI.hideLoading();
    }

    RectangularGlow {
        z: -1
        width: parent.width
        height: 80
        glowRadius: 5
        spread: 0.22
        color: "#30000000"
        cornerRadius: 3
    }

    Rectangle {
        z: 1
        width: parent.width
        height: 80
        color: "#fafafa"

        MaterialLabel {
            x: 22
            y: 34
            text: "字体集："
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        MaterialMenuField {
            id: menuFieldForFamilieName
            x: 90
            y: 15
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

            onSelectedTextChanged: fontToPng.refresh();
        }

        MaterialTextField {
            id: textFieldForSearchKey
            x: 310
            y: -7
            width: 150
            height: 56
            placeholderText: "搜索"

            property bool isChenged: false

            onTextChanged: {
                isChenged = true;
            }

            onEditingFinished: {
                if ( isChenged )
                {
                    isChenged = false;
                    fontToPng.refresh();
                }
            }
        }

        MaterialLabel {
            id: labelForIconCount
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            color: "#a1a1a1"
            text: "当前图标数量：" + iconCount

            property int iconCount: 0
        }
    }

    GridView {
        x: (parent.width % 86) / 2
        y: 80
        width: parent.width
        height: parent.height - y
        cellWidth: 85
        cellHeight: 106
        clip: true

        model: ListModel {
            id: listModel
        }

        delegate: Rectangle {
            id: rectanglrForChar
            width: 86
            height: 106
            color: "#00000000"

            Behavior on color { ColorAnimation { duration: 100 } }

            Image {
                id: imageForChar
                x: 13
                y: 2
                width: 60
                height: 60
                source: charPreviewUrl
            }

            MaterialLabel {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 25
                width: parent.width - 4
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: charName
                elide: Text.ElideRight
                font.pixelSize: 14
            }

            MaterialLabel {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: "(\\u" + charCode + ")"
                font.pixelSize: 14
                color: "#818181"
            }

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                width: parent.width - 8
                height: 1
                color: "#a1a1a1"
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                hoverEnabled: true

                onEntered: {
                    rectanglrForChar.color = "#33a1a1a1"
                }

                onExited: {
                    rectanglrForChar.color = "#00000000"
                }

                onClicked: {
                    if ( mouse.button & Qt.LeftButton )
                    {
                        materialUI.showSnackbarMessage( "保存功能还在开发中" ); // TODO
                    }
                    else if ( mouse.button & Qt.RightButton )
                    {
                        FontToPngManage.setClipboardText( "\\u" + charCode );
                        materialUI.showSnackbarMessage( "编号已经复制到了剪切板" );
                    }
                }
            }
        }

        header: Item {
            width: 1
            height: 10
        }
    }
}
