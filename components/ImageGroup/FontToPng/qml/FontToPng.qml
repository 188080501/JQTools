/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls.Material 2.15
import JQControls 1.0

Item {
    id: fontToPng
    width: 620
    height: 540
    clip: true
    property bool loadingVisible: false

    function refresh() {
        var charList = FontToPngManage.getCharList( menuFieldForFontName.currentText, textFieldForSearchKey.text );

        listModel.clear();
        for ( var index = 0; index < charList.length; ++index )
        {
            listModel.append( {
                                 fontFamilyName: charList[ index ][ "fontFamilyName" ],
                                 charCode: charList[ index ][ "charCode" ],
                                 charName: charList[ index ][ "charName" ],
                                 charPreviewUrl: charList[ index ][ "charPreviewUrl" ]
                              } );
        }

        labelForIconCount.iconCount = charList.length;
    }

    Component.onCompleted: {
        timerForInitializeFonts.start();
    }

    Timer {
        id: timerForInitializeFonts
        interval: 50
        repeat: false

        onTriggered: {
            fontToPng.loadingVisible = true;

            FontToPngManage.initializeFonts();
            fontToPng.refresh();

            fontToPng.loadingVisible = false;
        }
    }

    JQPane {
        z: -1
        width: parent.width
        height: 80
    }

    Rectangle {
        z: 1
        width: parent.width
        height: 80
        color: "#fafafa"

        JQText {
            x: 22
            anchors.verticalCenter: parent.verticalCenter
            text: "字体集："
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
        }

        JQComboBox {
            id: menuFieldForFontName
            x: 90
            anchors.verticalCenter: parent.verticalCenter
            width: 200
            model: [
                "所有字体集",
                "Elusive",
                "Feather",
                "FontAwesome",
                "Foundation",
                "GlyphiconsHalflings",
                "IcoMoon",
                "IconFont",
                "Icons8",
                "IconWorks",
                "Ionicons",
                "JustVector",
                "MaterialDesign",
                "MaterialIcons",
                "Metrize",
                "Mfglabs",
                "OpenIconic",
                "Socicon",
                "Typicons"
            ]

            onCurrentTextChanged: fontToPng.refresh();
        }

        JQTextField {
            id: textFieldForSearchKey
            x: 330
            anchors.verticalCenter: parent.verticalCenter
            width: 150
            height: 56
            placeholderText: "搜索"

            property bool isChanged: false

            onTextChanged: {
                isChanged = true;
            }

            onEditingFinished: {
                if ( isChanged )
                {
                    isChanged = false;
                    fontToPng.refresh();
                }
            }
        }

        JQText {
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
            id: rectangleForChar
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

            JQText {
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

            JQText {
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
                    rectangleForChar.color = "#33a1a1a1"
                }

                onExited: {
                    rectangleForChar.color = "#00000000"
                }

                onClicked: {
                    if ( mouse.button & Qt.LeftButton )
                    {
                        backgroundForDialog.opacity = 1.0;
                        dialogForSaveIcon.fontFamilyName = fontFamilyName;
                        dialogForSaveIcon.charCode = charCode;
                        dialogForSaveIcon.charName = charName;
                        dialogForSaveIcon.open();
                    }
                    else if ( mouse.button & Qt.RightButton )
                    {
                        FontToPngManage.setClipboardText( "\\u" + charCode );
                        JQGlobal.showMessage( "编号已经复制到了剪贴板" );
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

    JQDialog {
        id: dialogForSaveIcon
        z: 10
        title: "保存图标"
        destroyOnClosed: false
        centerItem: contentForSaveDialog

        property string fontFamilyName
        property string charCode
        property string charName

        onClosed: {
            backgroundForDialog.opacity = 0;
        }

        function saveIcon() {
            backgroundForDialog.opacity = 0;
            fontToPng.loadingVisible = true;

            var reply = FontToPngManage.saveIcon(
                        dialogForSaveIcon.fontFamilyName,
                        dialogForSaveIcon.charCode,
                        parseInt( textFieldForSize.text ),
                        textFieldForColor.text
                    );

            fontToPng.loadingVisible = false;

            switch ( reply )
            {
                case "cancel": JQGlobal.showMessage( "取消保存" ); break;
                case "error": JQGlobal.showMessage( "保存失败" ); break;
                case "OK": JQGlobal.showMessage( "保存成功" ); break;
                default: break;
            }
        }

        Item {
            id: contentForSaveDialog
            width: 300
            height: 380

            JQText {
                x: 28
                y: 10
                text: "字体集："
                font.pixelSize: 16
            }

            JQText {
                id: labelForFontFamilyName
                x: 100
                y: 10
                width: 120
                text: dialogForSaveIcon.fontFamilyName
            }

            JQText {
                x: 28
                y: 72
                text: "字符代码："
                font.pixelSize: 16
            }

            JQText {
                id: labelForCharCode
                x: 115
                y: 75
                width: 120
                height: 56
                text: "\\u" + dialogForSaveIcon.charCode
            }

            JQText {
                x: 28
                y: 133
                text: "字符名称："
                font.pixelSize: 16
            }

            JQText {
                id: labelForCharName
                x: 115
                y: 133
                width: 120
                height: 56
                text: dialogForSaveIcon.charName
            }

            JQText {
                x: 28
                y: 176
                height: 55
                text: "大小（像素）："
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            JQTextField {
                id: textFieldForSize
                x: 145
                y: 176
                width: 120
                text: "1000"
                validator: RegExpValidator { regExp: /^(-?\d+)$/ }
            }

            JQText {
                x: 28
                y: 238
                height: 55
                text: "颜色："
                font.pixelSize: 16
                verticalAlignment: Text.AlignVCenter
            }

            JQTextField {
                id: textFieldForColor
                x: 82
                y: 238
                width: 150
                text: "#000000"
            }

            Row {
                x: 80
                y: 335
                spacing: 16

                JQButton {
                    text: "取消"

                    onClicked: {
                        dialogForSaveIcon.close();
                    }
                }

                JQButton {
                    text: "保存"
                    Material.background: Material.Blue
                    Material.foreground: "#ffffff"

                    onClicked: {
                        dialogForSaveIcon.close();
                        dialogForSaveIcon.saveIcon();
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        z: 20
        visible: fontToPng.loadingVisible
        color: "#55000000"

        JQLoadingIndicator {
            anchors.centerIn: parent
            text: "处理中..."
        }

        MouseArea {
            anchors.fill: parent
        }
    }
}
