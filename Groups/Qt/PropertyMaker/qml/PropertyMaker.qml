import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import PropertyMaker 1.0

Item {
    id: propertyMaker
    width: 620
    height: 540

    function make() {
        textFieldForTarget.text = propertyMakerManage.make(
                    textFieldForSource.text,
                    checkBoxForWithSlot.checked,
                    checkBoxForWithInline.checked
                );
        return true;
    }

    PropertyMakerManage {
        id: propertyMakerManage

        Component.onCompleted: propertyMaker.make();
    }

    MaterialCheckBox {
        id: checkBoxForWithSlot
        x: 188
        text: "槽函数"
        anchors.horizontalCenterOffset: -217
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 11
        checked: true
    }

    MaterialCheckBox {
        id: checkBoxForWithInline
        x: 42
        text: "内联函数"
        anchors.horizontalCenterOffset: -79
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 11
        checked: true
    }

    MaterialButton {
        x: 386
        text: "生成代码"
        anchors.horizontalCenterOffset: 67
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20

        onClicked: propertyMaker.make();
    }

    MaterialButton {
        x: 420
        width: 120
        text: "处理剪切板内容"
        anchors.horizontalCenterOffset: 221
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20

        onClicked: {
            textFieldForSource.text = propertyMakerManage.clipboardText();
            if ( !propertyMaker.make() ) { return; }
            propertyMakerManage.setClipboardText( textFieldForTarget.text );
            materialUI.showSnackbarMessage( "生成的代码已经复制到了剪切板" );
        }
    }

    MaterialLabel {
        text: "Q_PROPERTY代码"
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
        width: (propertyMaker.width - 40) / 2
        height: propertyMaker.height - 110
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
            text:
"Q_PROPERTY(QString name_ READ name WRITE setName RESET resetName NOTIFY nameChanged)
Q_PROPERTY(int age_ READ age WRITE setAge)"
            selectionColor: "#2799f3"
        }
    }

    MaterialLabel {
        text: "生成的代码"
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
        width: (propertyMaker.width - 40) / 2
        height: propertyMaker.height - 110
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
        }
    }
}
