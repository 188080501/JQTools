pragma Singleton
import QtQuick 2.15
import JQControls 1.0

QtObject {
    id: jqGlobal

    property var window: null
    property var viewer

    readonly property color okColor: "#4CAF50"
    readonly property color ngColor: "#F44336"

    function showMessage( message ) {
        if ( !window )
        {
            print( "showMessage: window is null" );
            return;
        }

        snakeBarComponent.createObject( window, { text: message } );
    }

    function createObject( url, properties ) {
        var component = Qt.createComponent( url );

        if ( component.status !== Component.Ready )
        {
            print( "createObjectAndOpen: create component error:", url ,component.errorString() );
            return null;
        }

        var result;

        if ( properties )
        {
            result = component.createObject( JQGlobal.window, properties );
        }
        else
        {
            result = component.createObject( JQGlobal.window );
        }

        if ( !result )
        {
            print( "createObject: create object error:", url );
            return null;
        }

        return result;
    }

    function createObjectAndOpen( url, properties ) {
        var component = Qt.createComponent( url );

        if ( component.status !== Component.Ready )
        {
            print( "createObjectAndOpen: create component error:", url ,component.errorString() );
            return null;
        }

        var result;

        if ( properties )
        {
            result = component.createObject( JQGlobal.window, properties );
        }
        else
        {
            result = component.createObject( JQGlobal.window );
        }

        if ( !result )
        {
            print( "createObjectAndOpen: create object error:", url );
            return null;
        }

        result.open();
        return result;
    }

    property var snakeBarComponent: Component {

        JQSnakeBar { }
    }
}

