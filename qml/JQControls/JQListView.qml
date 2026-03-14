import QtQuick 2.15
import QtQuick.Controls 2.15

ListView {
    id: jqListView
    clip: true
    boundsMovement: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar { }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel) {
            if ( jqListView.contentWidth > jqListView.width )
            {
                jqListView.contentX -= wheel.angleDelta.y;

                if ( jqListView.contentX < 0 )
                {
                    jqListView.contentX = 0;
                }
                else
                {
                    var diff = jqListView.contentWidth - jqListView.width;

                    if ( diff > 0 )
                    {
                        if ( jqListView.contentX > diff )
                        {
                            jqListView.contentX = diff;
                        }
                    }
                    else
                    {
                        jqListView.contentX = 0;
                    }
                }
            }
            else if ( jqListView.contentHeight > jqListView.height )
            {
                jqListView.contentY -= wheel.angleDelta.y;

                if ( jqListView.contentY < 0 )
                {
                    jqListView.contentY = 0;
                }
                else
                {
                    diff = jqListView.contentHeight - jqListView.height;

                    if ( diff > 0 )
                    {
                        if ( jqListView.contentY > diff )
                        {
                            jqListView.contentY = diff;
                        }
                    }
                    else
                    {
                        jqListView.contentY = 0;
                    }
                }
            }
        }
    }
}

