import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: jqDialog
    width: {
        var result = centerItem.width + padding * 2;
        result += ( result % 2 );
        return result;
    }
    height: {
        var result = centerItem.height + padding * 2 + ( ( title === "" ) ? ( 0 ) : ( 45 ) );
        result += ( result % 2 );
        return result;
    }
    closePolicy: Dialog.NoAutoClose
    modal: true
    padding: 30

    property var centerItem

    property bool destroyOnClosed: true

    onClosed: {
        if ( destroyOnClosed )
        {
            destroy();
        }
    }

    MouseArea {
        anchors.fill: centerItem
        z: -1

        onClicked: {
            forceActiveFocus();
        }
    }
}

