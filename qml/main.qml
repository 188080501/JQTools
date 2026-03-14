/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import JQControls 1.0
import "qrc:/BookmarkData.js" as BookmarkData

JQWindow {
    id: applicationWindow
    width: 960
    height: 720
    minimumWidth: 800
    minimumHeight: 600
    visible: true
    opacity: 0
    title: "JQTools"
    color: "#fafafa"

    Component.onCompleted: {
        mainPageContains.showPage( "首页", "qrc:/Welcome/Welcome.qml" );

        opacityAnimation.start();

        bookmarkListView.refresh( BookmarkData.items );
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

    JQPane {
        x: 180
        z: -1
        width: parent.width - 180
        height: 64
    }

    Rectangle {
        x: 180
        z: 1
        width: parent.width - 180
        height: 64
        color: "#2196F3"

        JQText {
            id: currentItemTitleNameLabel
            x: 60
            z: 1
            height: 64
            font.pixelSize: 20
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            color: "#ffffff"
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

    JQText {
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

                        JQButton {
                            id: secondLevelButton
                            anchors.fill: parent
                            text: ""
                            visible: secondBookmarkListView.y === 0
                            padding: 0
                            topInset: 0
                            bottomInset: 0
                            Material.background: "#00000000"

                            JQText {
                                x: 36
                                height: parent.height
                                text: bookmarkName
                                font.pixelSize: 16
                                verticalAlignment: Text.AlignVCenter
                                color: ( currentItemTitleNameLabel.text === titleName ) ? ( "#1e88e5" ) : ( "#000000" )

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

                            JQText {
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

            JQButton {
                id: firstLevelButton
                width: parent.width
                height: 42
                text: ""
                padding: 0
                topInset: 0
                bottomInset: 0
                Material.background: "#00000000"

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

                JQText {
                    x: 18
                    height: parent.height
                    text: bookmarkName
                    font.bold: false
                    font.weight: Font.Normal
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 16
                    color: ( currentItemTitleNameLabel.text === titleName ) ? ( "#1e88e5" ) : ( "#000000" )

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
                    default:
                        if ( !( itemQrcLocation in mainPageContains.pages ) )
                        {
                            var component = Qt.createComponent( itemQrcLocation );

                            if ( component.status === Component.Ready ) {
                                var page = component.createObject( mainPageContains );
                                if ( page )
                                {
                                    page.anchors.fill = mainPageContains;
                                    mainPageContains.pages[ itemQrcLocation ] = page;
                                }
                                else
                                {
                                    print( "[main] createObject failed:", itemQrcLocation, component.errorString() );
                                }
                            }
                            else
                            {
                                print( "[main] createComponent failed:", itemQrcLocation, component.errorString() );
                            }
                        }

                        for ( var key in mainPageContains.pages )
                        {
                            mainPageContains.pages[ key ].visible = false;
                        }

                        currentItemTitleNameLabel.text = titleName;
                        if ( itemQrcLocation in mainPageContains.pages )
                        {
                            mainPageContains.pages[ itemQrcLocation ].visible = true;
                        }
                        else
                        {
                            print( "[main] page not loaded:", itemQrcLocation );
                        }

                        break;
                }
            }
        }
    }

    Item {
        id: materialUI
        z: 2
        anchors.fill: parent

        property var onDarkBackgroundClicked: null
        property var onStealthBackgroundClicked: null
        property var stealthBackgroundFilterItem: null
        property string dialogCancelText: "取消"
        property string dialogOKText: "确定"

        function isSmartPhone() {
            return ( Qt.platform.os === "ios" ) || ( Qt.platform.os === "android" );
        }

        function showDarkBackground(onDarkBackgroundClicked) {
            darkBackground.opacity = 1;

            switch (arguments.length)
            {
                case 1:
                    materialUI.onDarkBackgroundClicked = onDarkBackgroundClicked;
                    break;
                default:
                    materialUI.onDarkBackgroundClicked = null;
                    break;
            }
        }

        function showStealthBackground(onStealthBackgroundClicked, stealthBackgroundFilterItem) {
            stealthBackground.opacity = 1;

            switch (arguments.length)
            {
                case 2:
                    materialUI.stealthBackgroundFilterItem = stealthBackgroundFilterItem;
                case 1:
                    materialUI.onStealthBackgroundClicked = onStealthBackgroundClicked;
                    break;
                default:
                    materialUI.onStealthBackgroundClicked = null;
                    break;
            }
        }

        function hideDarkBackground() {
            darkBackground.opacity = 0;
        }

        function hideStealthBackground() {
            stealthBackground.opacity = 0;
        }

        function showSnackbarMessage(message) {
            JQGlobal.showMessage( message );
        }

        function showLoading(text, callbackOnClicked) {
            loadingIndicatorContainer.visible = true;
            loadingIndicator.text = "";

            switch (arguments.length)
            {
                case 1:
                case 2:
                    loadingIndicator.text = text;
                    break;
                default:
                    break;
            }

            showDarkBackground(( arguments.length === 2 ) ? ( callbackOnClicked ) : ( null ));
        }

        function hideLoading() {
            loadingIndicatorContainer.visible = false;
            hideDarkBackground();
        }

        Rectangle {
            id: darkBackground
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

                onClicked: {
                    if ( materialUI.onDarkBackgroundClicked )
                    {
                        materialUI.onDarkBackgroundClicked();
                    }
                }
            }
        }

        Rectangle {
            id: stealthBackground
            anchors.fill: parent
            color: "#00000000"
            visible: opacity !== 0
            opacity: 0

            Behavior on opacity {
                NumberAnimation { duration: 500; easing.type: Easing.OutCubic }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton

                onPressed: {
                    if ( materialUI.stealthBackgroundFilterItem )
                    {
                        var item = materialUI.stealthBackgroundFilterItem;
                        var currentX = item.x;
                        var currentY = item.y;
                        var parent = item.parent;

                        while ( parent && ( "x" in parent ) )
                        {
                            currentX += parent.x;
                            currentY += parent.y;
                            parent = parent.parent;
                        }

                        if ((( mouseX > currentX ) && ( mouseX < ( currentX + item.width ) )) &&
                            (( mouseY > currentY ) && ( mouseY < ( currentY + item.height ) )))
                        {
                            mouse.accepted = false;
                        }
                    }
                }

                onClicked: {
                    if ( materialUI.onStealthBackgroundClicked )
                    {
                        materialUI.onStealthBackgroundClicked();
                    }
                }
            }
        }

        Item {
            id: loadingIndicatorContainer
            anchors.centerIn: parent
            visible: false
            z: 1
            width: loadingIndicator.implicitWidth
            height: loadingIndicator.implicitHeight

            JQLoadingIndicator {
                id: loadingIndicator
                anchors.centerIn: parent
                running: loadingIndicatorContainer.visible
                indicatorSize: 40
                textColor: "#ffffff"
            }
        }
    }
}
