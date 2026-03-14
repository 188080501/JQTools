import QtQuick 2.15
import QtQuick.Controls 2.15
import JQControls 1.0

JQMenuItem {
    id: jqMenuDialogOpener

    property url dialogUrl
    property var dialogProperties

    onClicked: {
        JQGlobal.createObjectAndOpen( dialogUrl, dialogProperties )
    }
}
