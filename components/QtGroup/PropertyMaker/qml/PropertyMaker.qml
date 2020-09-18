/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import PropertyMaker 1.0

Item {
    id: propertyMaker
    width: 620
    height: 540

    function make() {
        var result = propertyMakerManage.make(
                    sourceCodeTextField.text,
                    withThreadSafeCheckBox.checked,
                    classNameTextField.text
                );
        statementCodeTextField.text = result[ "statementCode" ];
        accomplishCodeTextField.text = result[ "accomplishCode" ];
        return true;
    }

    PropertyMakerManage {
        id: propertyMakerManage

        Component.onCompleted: propertyMaker.make();
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        topPadding: 10
        spacing: 10

        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            MaterialCheckBox {
                id: withThreadSafeCheckBox
                anchors.verticalCenter: parent.verticalCenter
                text: "线程安全"
                checked: false
            }

            MaterialTextField {
                id: classNameTextField
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: -22
                width: 200
                placeholderText: "类名"
                text: "MyClass"
            }

            MaterialButton {
                anchors.verticalCenter: parent.verticalCenter
                text: "生成代码"

                onClicked: {
                    if ( !propertyMaker.make() )
                    {
                        materialUI.showSnackbarMessage( "生成失败" );
                        return;
                    }

                    materialUI.showSnackbarMessage( "生成成功" );
                }
            }
        }

        MaterialLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Q_PROPERTY代码"
        }

        RectangularGlow {
            width: parent.width
            height: ( propertyMaker.height - 150 ) / 3 - 5
            glowRadius: 6
            spread: 0.22
            color: "#20000000"

            Rectangle {
                anchors.fill: parent
                color: "#ffffff"
            }

            Flickable {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                contentWidth: sourceCodeTextField.paintedWidth
                contentHeight: sourceCodeTextField.paintedHeight
                clip: true

                TextEdit {
                    id: sourceCodeTextField
                    width: parent.width
                    height: parent.height
                    selectByMouse: true
                    selectionColor: "#2799f3"
                    text:
"Q_PROPERTY( QString name READ name WRITE setName NOTIFY nameChanged )
Q_PROPERTY( int age READ age WRITE setAge )"
                }
            }

            MouseArea {
                anchors.fill: parent
                visible: !sourceCodeTextField.focus

                onClicked: {
                    sourceCodeTextField.focus = true;
                }
            }
        }

        MaterialLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            text: "生成的代码"
        }

        RectangularGlow {
            width: parent.width
            height: ( propertyMaker.height - 150 ) / 3 - 5
            glowRadius: 6
            spread: 0.22
            color: "#20000000"

            Rectangle {
                anchors.fill: parent
                color: "#ffffff"
            }

            Flickable {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                contentWidth: statementCodeTextField.paintedWidth
                contentHeight: statementCodeTextField.paintedHeight
                clip: true

                TextEdit {
                    id: statementCodeTextField
                    width: parent.width
                    height: parent.height
                    selectByMouse: true
                    selectionColor: "#2799f3"
                }
            }

            MouseArea {
                anchors.fill: parent
                visible: !statementCodeTextField.focus

                onClicked: {
                    statementCodeTextField.focus = true;
                }
            }
        }

        RectangularGlow {
            width: parent.width
            height: ( propertyMaker.height - 150 ) / 3 - 5
            glowRadius: 6
            spread: 0.22
            color: "#20000000"

            Rectangle {
                anchors.fill: parent
                color: "#ffffff"
            }

            Flickable {
                x: 5
                y: 5
                width: parent.width - 10
                height: parent.height - 10
                contentWidth: accomplishCodeTextField.paintedWidth
                contentHeight: accomplishCodeTextField.paintedHeight
                clip: true

                TextEdit {
                    id: accomplishCodeTextField
                    width: parent.width
                    height: parent.height
                    selectByMouse: true
                    selectionColor: "#2799f3"
                }
            }

            MouseArea {
                anchors.fill: parent
                visible: !accomplishCodeTextField.focus

                onClicked: {
                    accomplishCodeTextField.focus = true;
                }
            }
        }
    }
}
