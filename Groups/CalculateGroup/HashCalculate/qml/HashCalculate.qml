import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import HashCalculate 1.0

Item {
    id: hashCalculate
    width: 620
    height: 540

    property bool changingFlag: false

    HashCalculateManage {
        id: hashCalculateManage

        onSourceChanged: {
            if ( hashCalculate.changingFlag ) { return; }

            hashCalculate.changingFlag = true;

            textFieldForSource.text = hashCalculateManage.source();

            hashCalculate.changingFlag = false;
        }

        onTargetChanged: {
            if ( hashCalculate.changingFlag ) { return; }

            hashCalculate.changingFlag = true;

            textFieldForTarget.text = hashCalculateManage.target();

            hashCalculate.changingFlag = false;
        }
    }

    MaterialLabel {
        text: "源字符串"
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
        anchors.top: parent.top
        anchors.topMargin: 40
        width: hashCalculate.width - 280
        height: (hashCalculate.height - 100) / 2
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
                if ( hashCalculate.changingFlag ) { return; }

                hashCalculate.changingFlag = true;

                hashCalculateManage.setSource( textFieldForSource.text );

                hashCalculate.changingFlag = false;
            }
        }
    }

    MaterialLabel {
        text: "计算结果"
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
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        width: hashCalculate.width - 280
        height: (hashCalculate.height - 100) / 2
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
            readOnly: true
            selectionColor: "#2799f3"
        }
    }

    Item {
        id: itemForButtons
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        width: 250
        height: 430

        MaterialButton {
            x: 8
            y: 11
            width: 110
            height: 40
            text: "黏贴内容"

            onClicked: {
                hashCalculateManage.pause();
            }
        }

        MaterialButton {
            x: 8
            y: 57
            width: 110
            height: 40
            text: "清空所有"

            onClicked: {
                hashCalculateManage.clear();
            }
        }

        MaterialButton {
            x: 124
            y: 11
            width: 110
            height: 40
            text: "复制结果"

            onClicked: {
                hashCalculateManage.copy();
                materialUI.showSnackbarMessage( "已将计算结果复制到了系统剪切板" );
            }
        }

        MaterialButton {
            x: 124
            y: 57
            width: 110
            height: 40
            text: "剪切到源"

            onClicked: {
                hashCalculateManage.cut();
            }
        }

        MaterialButton {
            x: 8
            y: 103
            width: 110
            height: 40
            text: "To Base64"

            onClicked: {
                hashCalculateManage.calculateToBase64();
            }
        }

        MaterialButton {
            x: 124
            y: 103
            width: 110
            height: 40
            text: "From Base64"

            onClicked: {
                hashCalculateManage.calculateFromBase64();
            }
        }

        MaterialButton {
            x: 8
            y: 149
            width: 110
            height: 40
            text: "MD4"

            onClicked: {
                hashCalculateManage.calculateMD4();
            }
        }

        MaterialButton {
            x: 124
            y: 149
            width: 110
            height: 40
            text: "MD5"

            onClicked: {
                hashCalculateManage.calculateMD5();
            }
        }

        MaterialButton {
            x: 8
            y: 195
            width: 110
            height: 40
            text: "Sha1"

            onClicked: {
                hashCalculateManage.calculateSha1();
            }
        }

        MaterialButton {
            x: 124
            y: 195
            width: 110
            height: 40
            text: "Sha224"

            onClicked: {
                hashCalculateManage.calculateSha224();
            }
        }

        MaterialButton {
            x: 8
            y: 241
            width: 110
            height: 40
            text: "Sha256"

            onClicked: {
                hashCalculateManage.calculateSha256();
            }
        }

        MaterialButton {
            x: 124
            y: 241
            width: 110
            height: 40
            text: "Sha384"

            onClicked: {
                hashCalculateManage.calculateSha384();
            }
        }

        MaterialButton {
            x: 8
            y: 287
            width: 110
            height: 40
            text: "Sha512"

            onClicked: {
                hashCalculateManage.calculateSha512();
            }
        }

        MaterialButton {
            x: 124
            y: 287
            width: 110
            height: 40
            text: "Sha3_224"

            onClicked: {
                hashCalculateManage.calculateSha3_224();
            }
        }

        MaterialButton {
            x: 8
            y: 333
            width: 110
            height: 40
            text: "Sha3_256"

            onClicked: {
                hashCalculateManage.calculateSha3_256();
            }
        }

        MaterialButton {
            x: 124
            y: 333
            width: 110
            height: 40
            text: "Sha3_384"

            onClicked: {
                hashCalculateManage.calculateSha3_384();
            }
        }

        MaterialButton {
            x: 8
            y: 379
            width: 110
            height: 40
            text: "Sha3_512"

            onClicked: {
                hashCalculateManage.calculateSha3_512();
            }
        }
    }
}
