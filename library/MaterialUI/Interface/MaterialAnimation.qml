import QtQuick 2.7

SequentialAnimation {
    id: animation

    property var target: null
    property string property
    property int duration: 1500
    property real from
    property real to

    property real fromToOffset: to - from

    ParallelAnimation {

        NumberAnimation {
            target: animation.target
            property: animation.property
            easing.type: Easing.InCubic
            duration: animation.duration * 0.27
            from: animation.from
            to: animation.from + animation.fromToOffset * 0.27
        }
    }

    ParallelAnimation {

        NumberAnimation {
            target: animation.target
            property: animation.property
            easing.type: Easing.OutExpo
            duration: animation.duration * 1.43
            to: animation.from + animation.fromToOffset * 1.022369
        }

        SequentialAnimation {

            PauseAnimation {
                duration: animation.duration * 0.73
            }

            ScriptAction {

                script: {
                    animation.running = false;

                    var buf = animation.property.toString().split( "." );
                    if ( buf.length === 1 )
                    {
                        animation.target[ buf[ 0 ] ] = animation.to;
                    }
                    else if ( buf.length === 2 )
                    {
                        animation.target[ buf[ 0 ] ][ buf[ 1 ] ] = animation.to;
                    }
                    else
                    {
                        print( "error property:", animation.property );
                    }
                }
            }
        }
    }
}
