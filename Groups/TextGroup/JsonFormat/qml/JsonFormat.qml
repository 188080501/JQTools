import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import JsonFormat 1.0

Item {
    id: jsonFormat
    width: 620
    height: 540

    function format() {
        if ( !jsonFormatManage.check( textFieldForSource.text ) )
        {
            materialUI.showSnackbarMessage( "无效的JSON字符串" );
            return false;
        }

        textFieldForSource.text = jsonFormatManage.format( textFieldForSource.text, checkBoxForCompact.checked );
        return true;
    }

    JsonFormatManage {
        id: jsonFormatManage
    }

    MaterialButton {
        x: 386
        text: "格式化"
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: jsonFormat.format();
    }

    MaterialButton {
        x: 386
        text: "处理剪切板内容"
        anchors.horizontalCenterOffset: 172
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 39

        onClicked: {
            textFieldForSource.text = jsonFormatManage.clipboardText();
            if ( !jsonFormat.format() ) { return; }
            jsonFormatManage.setClipboardText( textFieldForSource.text );
            materialUI.showSnackbarMessage( "格式化后的JSON字符串已经复制到了剪切板" );
        }
    }

    MaterialCheckBox {
        id: checkBoxForCompact
        x: 192
        text: "压缩模式"
        anchors.horizontalCenterOffset: -147
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    RectangularGlow {
        z: -1
        anchors.fill: itemForSource
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    Item {
        id: itemForSource
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: jsonFormat.width - 20
        height: jsonFormat.height - 110
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        TextEdit {
            id: textFieldForSource
            x: 5
            y: 5
            width: parent.width - 10
            height: parent.height - 10
            wrapMode: TextInput.WrapAnywhere
            selectByMouse: true
            selectionColor: "#2799f3"
        }
    }
}
