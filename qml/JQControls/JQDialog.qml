import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    id: jqDialog
    font.family: "MiSans"
    font.bold: false
    font.weight: Font.Normal
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
    x: parent ? Math.round( ( parent.width - width ) / 2 ) : 0
    y: parent ? Math.round( ( parent.height - height ) / 2 ) : 0
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
