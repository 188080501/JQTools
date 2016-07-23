import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"

ApplicationWindow {
    id: applicationWindow
    title: qsTr("JQTools")
    width: 800
    height: 600
    visible: true
    opacity: 0
    color: "#fafafa"

    minimumWidth: 640
    minimumHeight: 480

    Component.onCompleted: {
        itemForMainPage.showPage( "首页", "qrc:/Welcome/Welcome.qml" );

        animationForOpacity.start();

        listViewForBookmark.refresh(
                    [
                        { bookmarkName: "首页", titleName: "首页", qrcLocation: "qrc:/Welcome/Welcome.qml", children: [ ] },
                        {
                            bookmarkName: "文本类", titleName: "文本类", children:
                            [
                                { bookmarkName: "UTF-16转换", titleName: "UTF-16转换", qrcLocation: "qrc:/Utf16Transform/Utf16Transform.qml" },
                                { bookmarkName: "RGB转16进制", titleName: "RGB转16进制", qrcLocation: "qrc:/RgbStringTransform/RgbStringTransform.qml" },
                                { bookmarkName: "大小写转换", titleName: "大小写转换", qrcLocation: "qrc:/CaseTransform/CaseTransform.qml" },
                                { bookmarkName: "密码随机器", titleName: "密码随机器", qrcLocation: "qrc:/RandomPassword/RandomPassword.qml" },
                                { bookmarkName: "URL转码", titleName: "URL转码", qrcLocation: "qrc:/UrlEncode/UrlEncode.qml" },
                                { bookmarkName: "JSON格式化", titleName: "JSON格式化", qrcLocation: "qrc:/JsonFormat/JsonFormat.qml" }
                            ]
                        },
                        {
                            bookmarkName: "计算类",
                            titleName: "计算类",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "HASH计算器", titleName: "HASH计算器", qrcLocation: "qrc:/HashCalculate/HashCalculate.qml" },
                                { bookmarkName: "Unix时间戳转换", titleName: "Unix时间戳转换", qrcLocation: "qrc:/TimestampTransform/TimestampTransform.qml" },
                                { bookmarkName: "屏幕二维码解析器", titleName: "屏幕二维码解析器", qrcLocation: "notSupport" }
                            ]
                        },
                        {
                            bookmarkName: "制作类",
                            titleName: "制作类",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "图标生成器", titleName: "图标生成器", qrcLocation: "qrc:/IconMaker/IconMaker.qml" },
                                { bookmarkName: "图标字体转PNG", titleName: "图标字体转PNG", qrcLocation: "qrc:/FontToPng/FontToPng.qml" }
                            ]
                        },
                        {
                            bookmarkName: "工具类",
                            titleName: "工具类",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "代码行数统计", titleName: "代码行数统计", qrcLocation: "qrc:/LinesStatistics/LinesStatistics.qml" },
                                { bookmarkName: "PNG图片压缩", titleName: "PNG图片压缩", qrcLocation: "qrc:/PngOptimize/PngOptimize.qml" },
                                { bookmarkName: "屏幕拾色器", titleName: "屏幕拾色器", qrcLocation: "notSupport" },
                                { bookmarkName: "局域网文件传输", titleName: "局域网文件传输", qrcLocation: "notSupport" },
                                { bookmarkName: "局域网远程构建", titleName: "局域网远程构建", qrcLocation: "notSupport" }
                            ]
                        },
                        {
                            bookmarkName: "Qt相关",
                            titleName: "Qt相关",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "PNG警告消除", titleName: "PNG警告消除", qrcLocation: "qrc:/PngWarningRemover/PngWarningRemover.qml" },
                                { bookmarkName: "PROPERTY生成", titleName: "PROPERTY生成", qrcLocation: "qrc:/PropertyMaker/PropertyMaker.qml" },
                                { bookmarkName: "TS文件翻译器", titleName: "TS文件翻译器", qrcLocation: "notSupport" }
                            ]
                        }
                    ] );
    }

    NumberAnimation {
        id: animationForOpacity
        target: applicationWindow
        property: "opacity"
        easing.type: Easing.OutCubic
        duration: 300
        to: 1
    }

    Rectangle {
        x: 0
        y: 0
        z: 1
        width: 180
        height: 64
    }

    RectangularGlow {
        x: 180
        z: -1
        width: parent.width - 180
        height: 64
        glowRadius: 5
        spread: 0.22
        color: "#30000000"
        cornerRadius: 3
    }

    Rectangle {
        x: 180
        z: 1
        width: parent.width - 180
        height: 64
        color: "#2196F3"

        MaterialLabel {
            id: labelForCurrentItemTitleName
            x: 60
            z: 1
            height: 64
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.Left
            color: "#ffffff"
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onEntered: {
                labelForVersionString.opacity = 1;
            }

            onExited: {
                labelForVersionString.opacity = 0;
            }
        }

        MaterialLabel {
            id: labelForVersionString
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "V" + JQToolsManage.jqToolsVersionString()
            color: "#88ffffff"
            opacity: 0

            Behavior on opacity { NumberAnimation { easing.type: Easing.InOutQuad; duration: 400 } }
        }
    }

    Rectangle {
        x: 0
        y: 63
        z: 1
        width: 180
        height: 1
        color: "#e1e1e1"
    }

    MaterialLabel {
        z: 1
        width: 180
        height: 64
        text: "JQTools"
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        color: "#757575"
    }

    Rectangle {
        y: 64
        width: 180
        height: parent.height - 64
        color: "#ffffff"
    }

    ListView {
        id: listViewForBookmark
        y: 64
        width: 180
        height: parent.height - 64

        model: ListModel {
            id: listModelForBookmark
        }

        delegate: Item {
            id: itemForBookmark
            width: listViewForBookmark.width
            height: 42
            clip: true

            Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 400 } }

            Component.onCompleted: {
                for (var index = 0; index < bookmarkChildrenItem.count; index++)
                {
                    var buf = bookmarkChildrenItem.get(index);

                    listModelForSecondBookmark.append( {
                                                          bookmarkName: buf["bookmarkName"],
                                                          titleName: buf["titleName"],
                                                          itemQrcLocation: buf["qrcLocation"],
                                                      } );
                }

                listViewForSecondBookmark.height = bookmarkChildrenItem.count * 42;
                listViewForSecondBookmark.y = -1 * listViewForSecondBookmark.height;
            }

            Item {
                x: 0
                y: 42
                width: parent.width
                height: listViewForSecondBookmark.height
                clip: true

                ListView {
                    id: listViewForSecondBookmark
                    x: 0
                    y: 0
                    width: parent.width
                    height: 0
                    visible: y !== (-1 * listViewForSecondBookmark.height)
                    boundsBehavior: Flickable.StopAtBounds

                    Behavior on y { NumberAnimation { easing.type: Easing.InOutQuad; duration: 400 } }

                    model: ListModel {
                        id: listModelForSecondBookmark
                    }

                    delegate: Item {
                        id: itemForSecondBookmark
                        width: listViewForBookmark.width
                        height: 42

                        MaterialButton {
                            anchors.fill: parent
                            elevation: 0
                            text: ""
                            visible: listViewForSecondBookmark.y === 0

                            MaterialLabel {
                                x: 36
                                height: parent.height
                                text: bookmarkName
                                font.pixelSize: 16
                                verticalAlignment: Text.AlignVCenter
                                color: ( labelForCurrentItemTitleName.text === titleName ) ? ( "#1e88e5" ) : ( "#0000000" )

                                Behavior on color { ColorAnimation { duration: 200 } }
                            }

                            onClicked: {
                                itemForMainPage.showPage( titleName, itemQrcLocation );
                            }
                        }

                        Rectangle {
                            anchors.fill: parent
                            color: "#ffffff"
                            visible: listViewForSecondBookmark.y !== 0

                            MaterialLabel {
                                x: 36
                                height: parent.height
                                text: bookmarkName
                                font.pixelSize: 16
                                verticalAlignment: Text.AlignVCenter
                            }
                        }
                    }
                }
            }

            MaterialButton {
                width: parent.width
                height: 42
                elevation: 0
                textHorizontalAlignment: Text.AlignLeft

                onClicked: {
                    itemForMainPage.showPage( titleName, itemQrcLocation );

                    if (listModelForSecondBookmark.count)
                    {
                        if (listViewForSecondBookmark.visible)
                        {
                            listViewForSecondBookmark.y = -1 * listViewForSecondBookmark.height;
                            itemForBookmark.height = 42;
                        }
                        else
                        {
                            listViewForSecondBookmark.y = 0;
                            itemForBookmark.height = 42 + listViewForSecondBookmark.height;
                        }
                    }
                }

                MaterialLabel {
                    x: 18
                    height: parent.height
                    text: bookmarkName
                    font.bold: true
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16
                    color: ( labelForCurrentItemTitleName.text === titleName ) ? ( "#1e88e5" ) : ( "#0000000" )

                    Behavior on color { ColorAnimation { duration: 200 } }
                }
            }
        }

        function refresh( items ) {
            listModelForBookmark.clear();

            for (var index = 0; index < items.length; index++)
            {
                listModelForBookmark.append( {
                                                bookmarkName: items[index]["bookmarkName"],
                                                titleName: items[index]["titleName"],
                                                itemQrcLocation: items[index]["qrcLocation"],
                                                bookmarkChildrenItem: items[index]["children"]
                                            } );
            }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.MidButton

            onWheel: {
                listViewForBookmark.contentY -= wheel.angleDelta.y;

                if ( listViewForBookmark.contentY < 0 )
                {
                    listViewForBookmark.contentY = 0;
                }
                else
                {
                    var buf = listViewForBookmark.contentHeight - listViewForBookmark.height;

                    if ( buf > 0 )
                    {
                        if ( listViewForBookmark.contentY > buf )
                        {
                            listViewForBookmark.contentY = buf;
                        }
                    }
                    else
                    {
                        listViewForBookmark.contentY = 0;
                    }
                }
            }
        }
    }

    Rectangle {
        x: 180
        y: 0
        z: 1
        width: 1
        height: parent.height
        color: "#dcdcdc"
    }

    Item {
        id: itemForMainPage
        x: 180
        y: 64
        z: -2
        width: parent.width - 180
        height: parent.height - 64

        property var pages: new Object

        function showPage( titleName, itemQrcLocation ) {
            timerForShowPage.titleName = titleName;
            timerForShowPage.itemQrcLocation = itemQrcLocation;
            timerForShowPage.start();
        }

        Timer {
            id: timerForShowPage
            interval: 0
            repeat: false
            running: false

            property string titleName
            property string itemQrcLocation

            onTriggered: {
                switch( itemQrcLocation )
                {
                    case "": break;
                    case "notSupport": materialUI.showSnackbarMessage( "此功能暂未开放" ); break;
                    default:
                        if ( !( itemQrcLocation in itemForMainPage.pages ) )
                        {
                            var component = Qt.createComponent( itemQrcLocation );

                            if (component.status === Component.Ready) {
                                var page = component.createObject( itemForMainPage );
                                page.anchors.fill = itemForMainPage;
                                itemForMainPage.pages[ itemQrcLocation ] = page;
                            }
                        }

                        for ( var key in itemForMainPage.pages )
                        {
                            itemForMainPage.pages[ key ].visible = false;
                        }

                        labelForCurrentItemTitleName.text = titleName;
                        itemForMainPage.pages[ itemQrcLocation ].visible = true;

                        break;
                }
            }
        }
    }

    MaterialUI {
        id: materialUI
        z: 2
        anchors.fill: parent
        dialogCancelText: "取消"
        dialogOKText: "确定"
    }
}
