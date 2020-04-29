/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/"
import "qrc:/MaterialUI/Interface/"

ApplicationWindow {
    id: applicationWindow
    title: "JQTools"
    width: 800
    height: 600
    visible: true
    opacity: 0
    color: "#fafafa"

    minimumWidth: 800
    minimumHeight: 600

    Component.onCompleted: {
        mainPageContains.showPage( "首页", "qrc:/Welcome/Welcome.qml" );

        opacityAnimation.start();

        bookmarkListView.refresh(
                    [
                        { bookmarkName: "首页", titleName: "首页", qrcLocation: "qrc:/Welcome/Welcome.qml", children: [ ] },
                        {
                            bookmarkName: "文本类",
                            titleName: "文本类",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "UTF-16转换", titleName: "UTF-16转换", qrcLocation: "qrc:/Utf16Transform/Utf16Transform.qml" },
                                { bookmarkName: "RGB转16进制", titleName: "RGB转16进制", qrcLocation: "qrc:/RgbStringTransform/RgbStringTransform.qml" },
                                { bookmarkName: "大小写转换", titleName: "大小写转换", qrcLocation: "qrc:/CaseTransform/CaseTransform.qml" },
                                { bookmarkName: "密码随机器", titleName: "密码随机器", qrcLocation: "qrc:/RandomPassword/RandomPassword.qml" },
                                { bookmarkName: "UUID随机器", titleName: "UUID随机器", qrcLocation: "qrc:/RandomUuid/RandomUuid.qml" },
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
                                { bookmarkName: "Unix时间戳转换", titleName: "Unix时间戳转换", qrcLocation: "qrc:/TimestampTransform/TimestampTransform.qml" }
                            ]
                        },
                        {
                            bookmarkName: "制作类",
                            titleName: "制作类",
                            qrcLocation: "",
                            children:
                            [
                                { bookmarkName: "图标生成器", titleName: "图标生成器", qrcLocation: "qrc:/IconMaker/IconMaker.qml" },
                                { bookmarkName: "图标字体转PNG", titleName: "图标字体转PNG", qrcLocation: "qrc:/FontToPng/FontToPng.qml" },
                                { bookmarkName: "WebP图片制作器", titleName: "WebP图片制作器", qrcLocation: "qrc:/WebPMaker/WebPMaker.qml" },
                                { bookmarkName: "二维码生成器", titleName: "二维码生成器", qrcLocation: "qrc:/QRCodeMaker/QRCodeMaker.qml" },
                                { bookmarkName: "条形码生成器", titleName: "条形码生成器", qrcLocation: "qrc:/BarcodeMaker/BarcodeMaker.qml" }
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
                                { bookmarkName: "JPG图片压缩", titleName: "JPG图片压缩", qrcLocation: "qrc:/JpgOptimize/JpgOptimize.qml" },
                                { bookmarkName: "二维码识别器", titleName: "二维码识别器 ", qrcLocation: "qrc:/QRCodeReader/QRCodeReader.qml" },
                                { bookmarkName: "批量替换", titleName: "批量替换 ", qrcLocation: "qrc:/BatchReplacement/BatchReplacement.qml" },
                                { bookmarkName: "屏幕拾色器", titleName: "屏幕拾色器", qrcLocation: "notSupport" },
                                { bookmarkName: "局域网文件传输", titleName: "局域网文件传输", qrcLocation: "qrc:/LanFileTransport/LanFileTransport.qml" }
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
                                { bookmarkName: "CPP文件生成", titleName: "CPP文件生成", qrcLocation: "qrc:/CppFileMaker/CppFileMaker.qml" },
                                { bookmarkName: "TS文件翻译器", titleName: "TS文件翻译器", qrcLocation: "notSupport" }
                            ]
                        }
                    ] );
    }

    NumberAnimation {
        id: opacityAnimation
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
            id: currentItemTitleNameLabel
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
                versionStringLabel.opacity = 1;
            }

            onExited: {
                versionStringLabel.opacity = 0;
            }
        }

        MaterialLabel {
            id: versionStringLabel
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            text: "V" + ( ( JQToolsManage ) ? ( JQToolsManage.jqToolsVersionString() ) : ( "" ) )
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
        id: bookmarkListView
        y: 64
        width: 180
        height: parent.height - 64
        cacheBuffer: 9999

        model: ListModel {
            id: bookmarkListModel
        }

        delegate: Item {
            id: bookmarkItem
            width: bookmarkListView.width
            height: 42
            clip: true

            Behavior on height { NumberAnimation { easing.type: Easing.InOutQuad; duration: 400 } }

            Component.onCompleted: {
                for ( var index = 0; index < bookmarkChildrenItem.count; ++index )
                {
                    var buf = bookmarkChildrenItem.get(index);

                    secondBookmarkListModel.append( {
                                                          bookmarkName: buf[ "bookmarkName" ],
                                                          titleName: buf[ "titleName" ],
                                                          itemQrcLocation: buf["qrcLocation" ],
                                                      } );
                }

                secondBookmarkListView.height = bookmarkChildrenItem.count * 42;
                secondBookmarkListView.y = -1 * secondBookmarkListView.height;
            }

            Item {
                x: 0
                y: 42
                width: parent.width
                height: secondBookmarkListView.height
                clip: true

                ListView {
                    id: secondBookmarkListView
                    x: 0
                    y: 0
                    width: parent.width
                    height: 0
                    visible: y !== (-1 * secondBookmarkListView.height)
                    boundsBehavior: Flickable.StopAtBounds

                    Behavior on y { NumberAnimation { easing.type: Easing.InOutQuad; duration: 400 } }

                    model: ListModel {
                        id: secondBookmarkListModel
                    }

                    delegate: Item {
                        id: secondBookmarkContains
                        width: bookmarkListView.width
                        height: 42

                        MaterialButton {
                            anchors.fill: parent
                            elevation: 0
                            text: ""
                            visible: secondBookmarkListView.y === 0

                            MaterialLabel {
                                x: 36
                                height: parent.height
                                text: bookmarkName
                                font.pixelSize: 16
                                verticalAlignment: Text.AlignVCenter
                                color: ( currentItemTitleNameLabel.text === titleName ) ? ( "#1e88e5" ) : ( "#0000000" )

                                Behavior on color { ColorAnimation { duration: 200 } }
                            }

                            onClicked: {
                                mainPageContains.showPage( titleName, itemQrcLocation );
                            }
                        }

                        Rectangle {
                            anchors.fill: parent
                            color: "#ffffff"
                            visible: secondBookmarkListView.y !== 0

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
                    mainPageContains.showPage( titleName, itemQrcLocation );

                    if ( secondBookmarkListModel.count )
                    {
                        if (secondBookmarkListView.visible)
                        {
                            secondBookmarkListView.y = -1 * secondBookmarkListView.height;
                            bookmarkItem.height = 42;
                        }
                        else
                        {
                            secondBookmarkListView.y = 0;
                            bookmarkItem.height = 42 + secondBookmarkListView.height;
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
                    color: ( currentItemTitleNameLabel.text === titleName ) ? ( "#1e88e5" ) : ( "#0000000" )

                    Behavior on color { ColorAnimation { duration: 200 } }
                }
            }
        }

        function refresh( items ) {
            bookmarkListModel.clear();

            for (var index = 0; index < items.length; index++)
            {
                bookmarkListModel.append( {
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
                bookmarkListView.contentY -= wheel.angleDelta.y;

                if ( bookmarkListView.contentY < 0 )
                {
                    bookmarkListView.contentY = 0;
                }
                else
                {
                    var buf = bookmarkListView.contentHeight - bookmarkListView.height;

                    if ( buf > 0 )
                    {
                        if ( bookmarkListView.contentY > buf )
                        {
                            bookmarkListView.contentY = buf;
                        }
                    }
                    else
                    {
                        bookmarkListView.contentY = 0;
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
        id: mainPageContains
        x: 180
        y: 64
        z: -2
        width: parent.width - 180
        height: parent.height - 64

        property var pages: new Object

        function showPage( titleName, itemQrcLocation ) {
            showPageTimer.titleName = titleName;
            showPageTimer.itemQrcLocation = itemQrcLocation;
            showPageTimer.start();
        }

        Timer {
            id: showPageTimer
            interval: 5
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
                        if ( !( itemQrcLocation in mainPageContains.pages ) )
                        {
                            var component = Qt.createComponent( itemQrcLocation );

                            if (component.status === Component.Ready) {
                                var page = component.createObject( mainPageContains );
                                page.anchors.fill = mainPageContains;
                                mainPageContains.pages[ itemQrcLocation ] = page;
                            }
                        }

                        for ( var key in mainPageContains.pages )
                        {
                            mainPageContains.pages[ key ].visible = false;
                        }

                        currentItemTitleNameLabel.text = titleName;
                        mainPageContains.pages[ itemQrcLocation ].visible = true;

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
