import QtQuick 2.15
import QtQuick.Controls 2.15

Flickable {
    id: jqFlickable
    clip: true
    boundsMovement: Flickable.StopAtBounds

    ScrollBar.vertical: ScrollBar { }

    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.NoButton

        onWheel: function(wheel) {
            if ( jqFlickable.contentWidth > jqFlickable.width )
            {
                jqFlickable.contentX -= wheel.angleDelta.y;

                if ( jqFlickable.contentX < 0 )
                {
                    jqFlickable.contentX = 0;
                }
                else
                {
                    var diff = jqFlickable.contentWidth - jqFlickable.width;

                    if ( diff > 0 )
                    {
                        if ( jqFlickable.contentX > diff )
                        {
                            jqFlickable.contentX = diff;
                        }
                    }
                    else
                    {
                        jqFlickable.contentX = 0;
                    }
                }
            }
            else if ( jqFlickable.contentHeight > jqFlickable.height )
            {
                jqFlickable.contentY -= wheel.angleDelta.y;

                if ( jqFlickable.contentY < 0 )
                {
                    jqFlickable.contentY = 0;
                }
                else
                {
                    diff = jqFlickable.contentHeight - jqFlickable.height;

                    if ( diff > 0 )
                    {
                        if ( jqFlickable.contentY > diff )
                        {
                            jqFlickable.contentY = diff;
                        }
                    }
                    else
                    {
                        jqFlickable.contentY = 0;
                    }
                }
            }
        }
    }
}

