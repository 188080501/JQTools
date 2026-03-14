import QtQuick 2.15
import QtQuick.Window 2.15
import "./"

Window {
    id: jqWindow
    width: 1920
    height: 1000
    minimumWidth: 640
    minimumHeight: 480
    color: "#f4f4f4"
    visible: false

    // 对外属性
    property bool enabledAutoShowMaximized: false

    property int autoMaximizedBindWidth: 1920

    Component.onCompleted: {
        JQGlobal.window = this;

        if ( enabledAutoShowMaximized )
        {
            if ( Screen.desktopAvailableWidth <= autoMaximizedBindWidth )
            {
                Qt.callLater( ()=>{ showMaximized(); } );
            }
            else
            {
                Qt.callLater( ()=>{ visible = true; } );
            }
        }
        else
        {
            visible = true;
        }
    }
}
