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

    Column {
        anchors.centerIn: parent
        width: 540
        spacing: 18

        Row {
            spacing: 12

            JQText {
                text: "不编码字符"
                anchors.verticalCenter: parent.verticalCenter
            }

            JQTextField {
                id: textFieldForExclude
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
            width: 140
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForSource.text = urlEncodeManage.clipboardText();
                JQGlobal.showMessage( "已从剪贴板粘贴URL" );
            }
        }

        JQTextField {
            id: textFieldForSource
            width: parent.width
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
            width: 140
            text: "复制到剪贴板"

            onClicked: {
                urlEncodeManage.setClipboardText( textFieldForTarget.text );
                JQGlobal.showMessage( "URL已经复制到了剪贴板" );
            }
        }

        JQTextField {
            id: textFieldForTarget
            width: parent.width
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
