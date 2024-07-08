import QtQuick 2.7
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import BinarySearchAssistant 1.0

Item {
    id: binarySearchAssistant
    width: 620
    height: 540

    property string guess: ""
    property bool canStartGame: false 
    property bool startRecord: false 

    BinarySearchAssistantManage {
        id: binarySearchAssistantManage
        onGuessChanged: {
            binarySearchAssistant.guess = binarySearchAssistantManage.guess();
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        MaterialTextField {
            id: minField
            placeholderText: "最小值"
            validator: IntValidator {} // 确保输入的是整数
            onTextChanged: {
                // 更新canStartGame属性的值，检查最小值和最大值是否有效        
                var minVal = parseInt(minField.text);
                var maxVal = parseInt(maxField.text);
                canStartGame = minVal < maxVal;;
                if (!canStartGame) {
                    startRecord = false;
                }
            }
        }

        MaterialTextField {
            id: maxField
            placeholderText: "最大值"
            validator: IntValidator {}
            onTextChanged: {
                var minVal = parseInt(minField.text);
                var maxVal = parseInt(maxField.text);
                canStartGame = minVal < maxVal;;
                if (!canStartGame) {
                    startRecord = false;
                }
            }
        }

        Item {
            width: 1
            height: 10
        }

        MaterialButton {
            text: canStartGame ? (startRecord ? "开始新记录" : "开始记录") : "最小值小于最大值才能开始"
            enabled: canStartGame
            onClicked: {
                if (canStartGame) {
                    startRecord = true;
                    binarySearchAssistantManage.startNewGame(minField.text, maxField.text);
                }
            }
        }

        MaterialLabel {
            text: startRecord ? "我的猜测是：" + binarySearchAssistant.guess : ""
        }

        MaterialButton {
            text: "更高"
            enabled: startRecord
            onClicked: binarySearchAssistantManage.guessHigher()
        }

        MaterialButton {
            text: "更低"
            enabled: startRecord
            onClicked: binarySearchAssistantManage.guessLower()
        }
    }
}
