/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

import QtQuick 2.7
import JQControls 1.0
import UrlEncode 1.0

Item {
    id: urlEncode
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    UrlEncodeManage {
        id: urlEncodeManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        JQText {
            x: 40
            y: 70
            text: "不编码字符"

            JQTextField {
                id: textFieldForExclude
                anchors.left: parent.right
                anchors.leftMargin: 12
                anchors.verticalCenter: parent.verticalCenter
                width: 150
                text: "/:?=&%"

                onTextChanged: {
                    if ( urlEncode.changingFlag ) { return; }

                    urlEncode.changingFlag = true;

                    textFieldForTarget.text = urlEncodeManage.encode( textFieldForSource.text, textFieldForExclude.text );

                    urlEncode.changingFlag = false;
                }
            }
        }

        JQButton {
            x: 40
            y: 155
            width: 120
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForSource.text = urlEncodeManage.clipboardText();
                JQGlobal.showMessage( "已从剪贴板粘贴URL" );
            }
        }

        JQTextField {
            id: textFieldForSource
            x: 40
            y: 205
            width: 540
            placeholderText: "源URL"
            text: "https://www.google.com/search?q=中文"

            onTextChanged: {
                if ( urlEncode.changingFlag ) { return; }

                urlEncode.changingFlag = true;

                textFieldForTarget.text = urlEncodeManage.encode( textFieldForSource.text, textFieldForExclude.text );

                urlEncode.changingFlag = false;
            }
        }

        JQButton {
            x: 40
            y: 320
            width: 120
            text: "复制到剪贴板"

            onClicked: {
                urlEncodeManage.setClipboardText( textFieldForTarget.text );
                JQGlobal.showMessage( "URL已经复制到了剪贴板" );
            }
        }

        JQTextField {
            id: textFieldForTarget
            x: 40
            y: 365
            width: 540
            placeholderText: "编码URL"
            text: "https://www.google.com/search?q=%E4%B8%AD%E6%96%87"

            onTextChanged: {
                if ( urlEncode.changingFlag ) { return; }

                urlEncode.changingFlag = true;

                textFieldForSource.text = urlEncodeManage.decode( textFieldForTarget.text );

                urlEncode.changingFlag = false;
            }
        }
    }
}
