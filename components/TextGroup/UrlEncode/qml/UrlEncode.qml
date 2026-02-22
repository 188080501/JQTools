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

        MaterialTextField {
            id: textFieldForExclude
            x: 40
            y: 30
            width: 150
            placeholderText: "不编码字符"
            text: "/:?=&%"

            onTextChanged: {
                if ( urlEncode.changingFlag ) { return; }

                urlEncode.changingFlag = true;

                textFieldForTarget.text = urlEncodeManage.encode( textFieldForSource.text, textFieldForExclude.text );

                urlEncode.changingFlag = false;
            }
        }

        MaterialButton {
            x: 40
            y: 135
            width: 120
            text: "从剪贴板粘贴"

            onClicked: {
                textFieldForSource.text = urlEncodeManage.clipboardText();
                materialUI.showSnackbarMessage( "已从剪贴板粘贴URL" );
            }
        }

        MaterialTextField {
            id: textFieldForSource
            x: 40
            y: 180
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

        MaterialButton {
            x: 40
            y: 300
            width: 120
            text: "复制到剪贴板"

            onClicked: {
                urlEncodeManage.setClipboardText( textFieldForTarget.text );
                materialUI.showSnackbarMessage( "URL已经复制到了剪贴板" );
            }
        }

        MaterialTextField {
            id: textFieldForTarget
            x: 40
            y: 340
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
