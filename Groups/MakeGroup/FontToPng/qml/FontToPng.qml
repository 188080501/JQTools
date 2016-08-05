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
        timerForBegin.start();
    }

    Timer {
        id: timerForBegin
        interval: 50
        repeat: false

        onTriggered: {
            materialUI.showLoading();

            FontToPngManage.begin();
            fontToPng.refresh();

            materialUI.hideLoading();
        }
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
        x: ( parent.width % 86 ) / 2
        y: 80
        width: parent.width
        height: parent.height - y
        cellWidth: 86
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
                        backgroundForDialog.opacity = 1.0;
                        dialogForSaveIcon.familieName = familieName;
                        dialogForSaveIcon.charCode = charCode;
                        dialogForSaveIcon.charName = charName;
                        dialogForSaveIcon.open();
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

    Rectangle {
        id: backgroundForDialog
        z: 10
        anchors.fill: parent
        color: "#55000000"
        visible: opacity !== 0
        opacity: 0

        Behavior on opacity {
            NumberAnimation { duration: 500; easing.type: Easing.OutCubic }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
        }
    }

    MaterialDialog {
        id: dialogForSaveIcon
        z: 10
        width: 350
        height: 440
        title: "保存图标"
        negativeButtonText: materialUI.dialogCancelText
        positiveButtonText: materialUI.dialogOKText

        property string familieName
        property string charCode
        property string charName

        onRejected: {
            backgroundForDialog.opacity = 0;
        }

        onAccepted: {
            backgroundForDialog.opacity = 0;

            materialUI.showLoading();

            var reply = FontToPngManage.saveIcon(
                        dialogForSaveIcon.familieName,
                        dialogForSaveIcon.charCode,
                        parseInt( labelForSize.text ),
                        textFieldForColor.text
                    );

            materialUI.hideLoading();

            switch ( reply )
            {
                case "cancel": materialUI.showSnackbarMessage( "取消保存" ); break;
                case "error": materialUI.showSnackbarMessage( "保存失败" ); break;
                case "OK": materialUI.showSnackbarMessage( "保存成功" ); break;
                default: break;
            }
        }

        Item {
            width: 300
            height: 320

            MaterialLabel {
                x: 28
                y: 10
                text: "字体集："
                font.pixelSize: 16
            }

            MaterialLabel {
                id: labelForFamilieName
                x: 100
                y: 13
                width: 120
                height: 56
                text: dialogForSaveIcon.familieName
            }

            MaterialLabel {
                x: 28
                y: 72
                text: "字符代码："
                font.pixelSize: 16
            }

            MaterialLabel {
                id: labelForCharCode
                x: 115
                y: 75
                width: 120
                height: 56
                text: "\\u" + dialogForSaveIcon.charCode
            }

            MaterialLabel {
                x: 28
                y: 133
                text: "字符名称："
                font.pixelSize: 16
            }

            MaterialLabel {
                id: labelForCharName
                x: 115
                y: 137
                width: 120
                height: 56
                text: dialogForSaveIcon.charName
            }

            MaterialLabel {
                x: 28
                y: 196
                text: "大小（像素）："
                font.pixelSize: 16
            }

            MaterialTextField {
                id: labelForSize
                x: 145
                y: 157
                width: 120
                height: 56
                text: "1000"
                validator: RegExpValidator { regExp: /^(-?\d+)$/ }
            }

            MaterialLabel {
                x: 28
                y: 258
                text: "颜色："
                font.pixelSize: 16
            }

            MaterialTextField {
                id: textFieldForColor
                x: 82
                y: 220
                width: 150
                placeholderText: "十六进制值或者描述字符串"
                text: "#000000"
            }
        }
    }
}
