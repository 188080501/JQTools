import QtQuick 2.7
import JQControls 1.0
import BinarySearchAssistant 1.0

Item {
    id: binarySearchAssistant
    width: 620
    height: 540

    property string currentGuess: ""
    property bool canStartGame: false 
    property bool gameStarted: false 

    BinarySearchAssistantManage {
        id: binarySearchAssistantManage
        onGuessChanged: {
            binarySearchAssistant.currentGuess = binarySearchAssistantManage.guess();
        }
    }

    Column {
        anchors.centerIn: parent
        spacing: 10

        JQTextField {
            id: minField
            placeholderText: "最小值"
            validator: IntValidator {} // 确保输入的是整数
            onTextChanged: {
                // 更新canStartGame属性的值，检查最小值和最大值是否有效        
                var minVal = parseInt(minField.text);
                var maxVal = parseInt(maxField.text);
                canStartGame = minVal < maxVal;;
                if (!canStartGame) {
                    gameStarted = false;
                }
            }
        }

        JQTextField {
            id: maxField
            placeholderText: "最大值"
            validator: IntValidator {}
            onTextChanged: {
                var minVal = parseInt(minField.text);
                var maxVal = parseInt(maxField.text);
                canStartGame = minVal < maxVal;;
                if (!canStartGame) {
                    gameStarted = false;
                }
            }
        }

        Item {
            width: 1
            height: 10
        }

        JQButton {
            text: canStartGame ? (gameStarted ? "重新开始" : "开始游戏") : "最小值小于最大值才能开始"
            enabled: canStartGame
            onClicked: {
                if (canStartGame) {
                    gameStarted = true;
                    binarySearchAssistantManage.startNewGame(minField.text, maxField.text);
                }
            }
        }

        JQText {
            text: gameStarted ? "我的猜测是：" + binarySearchAssistant.currentGuess : ""
        }

        JQButton {
            text: "更高"
            enabled: gameStarted
            onClicked: binarySearchAssistantManage.targetIsHigher()
        }

        JQButton {
            text: "更低"
            enabled: gameStarted
            onClicked: binarySearchAssistantManage.targetIsLower()
        }
    }
}
