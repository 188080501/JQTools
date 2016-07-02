import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import Utf16Transform 1.0

Item {
    id: utf16Transform
    width: 620
    height: 540

    property bool changingFlag: false

    Utf16TransformManage {
        id: utf16TransformManage
    }

    MaterialLabel {
        x: 162
        text:
"UTF16-转换工具，可以将文本和UTF-16之间互转
例如将 “中文” 与 “\\u4E2D\\u6587” 互转"
        anchors.horizontalCenterOffset: -91
        anchors.top: parent.top
        anchors.topMargin: 18
        anchors.horizontalCenter: parent.horizontalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    MaterialButton {
        x: 420
        width: 120
        height: 40
        text: "处理剪切板内容"
        anchors.horizontalCenterOffset: 160
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 18

        onClicked: {
            textFieldForSource.text = utf16TransformManage.clipboardText();
            utf16TransformManage.setClipboardText( textFieldForTarget.text );
            materialUI.showSnackbarMessage( "UTF-16字符串已经复制到了剪切板" );
        }
    }

    MaterialLabel {
        text: "文本字符串"
        anchors.horizontalCenterOffset: 0
        anchors.bottom: itemForSource.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: itemForSource.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
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
        width: (utf16Transform.width - 40) / 2
        height: utf16Transform.height - 110
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

            onTextChanged: {
                if ( utf16Transform.changingFlag ) { return; }

                utf16Transform.changingFlag = true;

                textFieldForTarget.text = utf16TransformManage.toUtf16( textFieldForSource.text );

                utf16Transform.changingFlag = false;
            }
        }
    }

    MaterialLabel {
        text: "UTF-16字符串"
        anchors.horizontalCenterOffset: 0
        anchors.bottom: itemForTarget.top
        anchors.bottomMargin: 10
        anchors.horizontalCenter: itemForTarget.horizontalCenter
        horizontalAlignment: Text.AlignHCenter
    }

    RectangularGlow {
        z: -1
        anchors.fill: itemForTarget
        glowRadius: 6
        spread: 0.22
        color: "#20000000"
    }

    Item {
        id: itemForTarget
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: (utf16Transform.width - 40) / 2
        height: utf16Transform.height - 110
        clip: true

        Rectangle {
            anchors.fill: parent
            color: "#ffffff"
        }

        TextEdit {
            id: textFieldForTarget
            x: 5
            y: 5
            width: parent.width - 10
            height: parent.height - 10
            wrapMode: TextInput.WrapAnywhere
            selectByMouse: true
            selectionColor: "#2799f3"

            onTextChanged: {
                if ( utf16Transform.changingFlag ) { return; }

                utf16Transform.changingFlag = true;

                textFieldForSource.text = utf16TransformManage.fromUtf16( textFieldForTarget.text );

                utf16Transform.changingFlag = false;
            }
        }
    }
}
