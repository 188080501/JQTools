import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

Rectangle {
    id: swipeToRefresh
    width: parent.width
    height: 0
    color: "#00000000"

    property var base: parent.parent

    property int targetHeight: 150
    property real offsetY: 0
    property real swipePercentage: 0
    property real buttonBottomMargin: 5

    property var onRefreshCallback: null
    property var onCancelCallback: null

    property bool refreshing: false
    property bool finishing: false

    function refresh() {
        refreshing = true;
    }

    function finish() {
        refreshing = false;
        finishing = true;
        swipePercentage = 0;

        animation.start();
    }

    Component.onCompleted: {
        parent.z = 2;

        onRefreshCallback = materialUI.swipeToRefreshOnRefreshCallback;
        onCancelCallback = materialUI.swipeToRefreshOnCancelCallback;

        if (materialUI.swipeToRefreshOnCompleted)
        {
            materialUI.swipeToRefreshOnCompleted(swipeToRefresh);
        }

        materialUI.swipeToRefreshOnRefreshCallback = null;
        materialUI.swipeToRefreshOnCancelCallback = null;
        materialUI.swipeToRefreshOnCompleted = null;
    }

    Connections {
        target: base

        onYChanged: {
            if (base.y > 0)
            {
                var bufHeight;

                if (base.y > 2)
                {
                    bufHeight = (((base.y - 2) < targetHeight) ? (base.y - 2) : (targetHeight));
                }
                else
                {
                    bufHeight = 0;
                }

                if (refreshing)
                {
                    if (bufHeight > (targetHeight * 0.6))
                    {
                        swipeToRefresh.height = bufHeight;
                    }
                }
                else
                {
                    swipeToRefresh.height = bufHeight;
                }

                swipePercentage = swipeToRefresh.height / (targetHeight * 0.6);
                progressCircle.setValue(swipePercentage);

                if (swipePercentage >= 1)
                {
                    swipePercentage = 1;

                    if (!refreshing && !finishing && onRefreshCallback)
                    {
                        onRefreshCallback();
                    }
                }

                base.y = 0;
            }
            else if (base.y < 0)
            {
                if (refreshing)
                {
                    base.y = 0;
                }

                swipePercentage = 0;
            }
        }
    }

    PropertyAnimation {
        id: animation
        target: button
        properties: "scale"
        easing.type: Easing.OutQuad
        to: 0
        duration: 250

        onStopped: {
            swipeToRefresh.height = 0;
            button.scale = 1;
            finishing = false;
        }
    }

    MaterialActionButton {
        id: button
        anchors.bottom: parent.bottom
        anchors.bottomMargin: buttonBottomMargin
        anchors.horizontalCenter: parent.horizontalCenter
        width: 40
        height: 40
        backgroundColor: "#fafafa"

        MaterialProgressCircle {
            id: progressCircle
            width: 25
            height: 25
            anchors.centerIn: parent
            circleColor: "#a0a0a0"
            indeterminate: refreshing || finishing

            function setValue(value_) {
                if (value_ < 0.25)
                {
                    value = 0;
                }
                value = value_ * (4 / 3) - (1 / 3);
            }
        }

        MouseArea {
            anchors.fill: parent

            onClicked: {
                if (onCancelCallback)
                {
                    onCancelCallback();
                }
            }
        }
    }
}
