import QtQuick 2.5
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/MaterialUI/Interface/"
import RgbStringTransform 1.0

Item {
    id: rgbStringTransform
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    RgbStringTransformManage {
        id: rgbStringTransformManage
    }

    Item {
        anchors.centerIn: parent
        width: 620
        height: 540

        MaterialTextField {
            id: textFieldForHexString
            x: 195
            y: 231
            placeholderText: "颜色"
            width: 100
            text: "#ffffff"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFiedForRed.text = rgbStringTransformManage.getRed( textFieldForHexString.text );
                textFiedForGreen.text = rgbStringTransformManage.getGreen( textFieldForHexString.text );
                textFiedForBlue.text = rgbStringTransformManage.getBlue( textFieldForHexString.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForRed
            x: 346
            y: 169
            placeholderText: "红(R)"
            width: 80
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForGreen
            x: 346
            y: 293
            placeholderText: "绿(G)"
            width: 80
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }

        MaterialTextField {
            id: textFiedForBlue
            x: 346
            y: 231
            placeholderText: "蓝(B)"
            width: 80
            text: "255"

            onTextChanged: {
                if ( rgbStringTransform.changingFlag ) { return; }

                rgbStringTransform.changingFlag = true;

                textFieldForHexString.text = rgbStringTransformManage.getHexString( textFiedForRed.text, textFiedForGreen.text, textFiedForBlue.text );

                rgbStringTransform.changingFlag = false;
            }
        }
    }
}
