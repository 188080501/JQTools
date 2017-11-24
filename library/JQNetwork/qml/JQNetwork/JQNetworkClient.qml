import QtQuick 2.8
import JQNetworkClientForQml 1.0

JQNetworkClientForQml {
    id: jqNetworkClientForQml

    function onSendSucceed( callback, received ) {
        callback( received );
    }

    function onSendFail( callback ) {
        callback();
    }
}
