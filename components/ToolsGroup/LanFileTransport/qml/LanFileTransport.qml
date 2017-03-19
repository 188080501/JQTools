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
import LanFileTransport 1.0

Item {
    id: lanFileTransport
    width: 620
    height: 540

    property bool changingFlag: true

    Component.onCompleted: {
        changingFlag = false;
    }

    LanFileTransportManage {
        id: lanFileTransportManage
    }

    PathView {
        id: pathView
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -10
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 140
        width: 400
        height: 400

        delegate: Item {
            id: item
            width: 128
            height: 128
            visible: nodeMarkSummary !== "invisibleItem"

            MaterialProgressCircle {
                id: progressCircleForSend
                anchors.centerIn: parent
                width: 110
                height: 110
                indeterminate: false
                showPercentage: false
                circleColor: "#2196f3"

                Behavior on value { PropertyAnimation { duration: 200 } }

                Connections {
                    target: lanFileTransportManage

                    onSending: {
                        if ( currentHostAddress !== hostAddress ) { return; }

                        progressCircleForSend.value = sendPercentage;
                    }

                    onSendFinish: {
                        if ( currentHostAddress !== hostAddress ) { return; }

                        progressCircleForSend.value = 1;

                        materialUI.showSnackbarMessage( "发送完成" );
                    }
                }
            }

            MaterialActionButton {
                anchors.centerIn: parent
                width: 100
                height: 100
                text: hostName + "\n"
                backgroundColor: "#ffffff"
                scale: 1.5
                opacity: 0

                onClicked: {
                    materialUI.showSnackbarMessage( "远端节点标记：" + nodeMarkSummary );
                }

                Component.onCompleted: {
                    scale = 1;
                    opacity = 1;
                }

                Behavior on scale { PropertyAnimation { duration: 1000; easing.type: Easing.OutElastic } }
                Behavior on opacity { PropertyAnimation { duration: 300 } }

                MaterialLabel {
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 11
                    color: "#a1a1a1"
                    text: "\n" + hostAddress
                }
            }

            DropArea {
                anchors.fill: parent
                enabled: ( progressCircleForSend.value === 0 ) || ( progressCircleForSend.value === 1 )

                onDropped: {
                    if( !drop.hasUrls ) { return; }

                    var filePaths = [ ];

                    for( var index = 0; index < drop.urls.length; ++index )
                    {
                        var url = drop.urls[ index ].toString();

                        if ( url.indexOf( "file://" ) !== 0 ) { return; }

                        if ( Qt.platform.os === "windows" )
                        {
                            filePaths.push( url.substr( 8 ) );
                        }
                        else
                        {
                            filePaths.push( url.substr( 7 ) );
                        }
                    }

                    var transportResult = lanFileTransportManage.transport( hostAddress, filePaths );
                    switch ( transportResult )
                    {
                        case "cancel": materialUI.showSnackbarMessage( "用户取消操作" ); break;
                        case "packFail": materialUI.showSnackbarMessage( "打包失败" ); break;
                        case "OK": materialUI.showSnackbarMessage( "发送中" ); break;
                    }
                }
            }
        }

        path: Path {
            startX: ( pathView.width / 2 ) * 0.3
            startY: ( pathView.width / 2 ) * 1.2

            PathArc {
                x: ( pathView.width / 2 ) * 1.8
                y: ( pathView.width / 2 ) * 1.2
                radiusX: ( pathView.width / 2 )
                radiusY: ( pathView.width / 2 )
                useLargeArc: true
            }
        }

        model: ListModel {
            id: listModel

            ListElement {
                nodeMarkSummary: "invisibleItem"
                hostName: "invisibleItem"
                hostAddress: "invisibleItem"
            }
        }

        function refresh() {
            var lanNodes = lanFileTransportManage.lanNodes();
            var waitForCreate = [ ];
            var alreadyCreated = [ ];

            for ( var index in lanNodes )
            {
                var lanNode = lanNodes[ index ];
                var flag = false;

                for ( var index2 = 1; index2 < listModel.count; ++index2 )
                {
                    if ( listModel.get( index2 ).nodeMarkSummary !== lanNode[ "nodeMarkSummary" ] ) { continue; }

                    alreadyCreated.push( lanNode[ "nodeMarkSummary" ] );
                    flag = true;

                    break;
                }

                if ( !flag )
                {
                    waitForCreate.push( lanNode );
                }
            }

            for ( var index3 = 1; index3 < listModel.count; )
            {
                if ( alreadyCreated.indexOf( listModel.get( index3 ).nodeMarkSummary ) === -1 )
                {
                    listModel.remove( index3 );

                    index3 = 1;
                }
                else
                {
                    ++index3;
                }
            }

            for ( var index4 = 0; index4 < waitForCreate.length; ++index4 )
            {
                listModel.append( waitForCreate[ index4 ] );
            }
        }

        Component.onCompleted: {
            refresh();
        }

        Connections {
            target: lanFileTransportManage

            onLanNodeChanged: {
                pathView.refresh();
            }
        }
    }

    MaterialActionButton {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 40
        width: 128
        height: 128
        text: lanFileTransportManage.localHostName() + "\n"

        onClicked: {
            materialUI.showSnackbarMessage( "当前节点标记：" + lanFileTransportManage.localNodeMarkSummary() );
            lanFileTransportManage.sendOnlinePing();
        }

        MaterialLabel {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 11
            color: "#ffffff"
            text: "\n" + lanFileTransportManage.localHostAddress()
        }
    }

    MaterialLabel {
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        text: "拖动文件到节点圆圈处即可传输文件"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignRight
        color: "#a1a1a1"
    }

    MaterialLabel {
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 45
        text: "保存路径：" + lanFileTransportManage.savePath();
        color: "#a1a1a1"
    }

    MaterialSwitch {
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15

        onCheckedChanged: {
            lanFileTransportManage.setShowSelf( checked );
        }

        MaterialLabel {
            anchors.left: parent.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "显示自身"
            color: "#a1a1a1"
        }
    }
}
