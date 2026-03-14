import QtQuick 2.15
import QtQuick.Controls 2.15
import "./"

JQTextField {
    id: jqHexTextFiled
    inputMethodHints: Qt.ImhNoPredictiveText
    maximumLength: ( maximumByteCount > 0 ) ? ( maximumByteCount * 3 - 1 ) : 32767

    property int maximumByteCount: 0
    property bool changingText: false

    validator: RegularExpressionValidator {
        regularExpression: /^[0-9a-fA-F ]*$/
    }

    onTextChanged: {
        if ( changingText )
        {
            return;
        }

        changingText = true;

        var cursorPosition = jqHexTextFiled.cursorPosition;
        var hexDigitsBeforeCursor = getHexDigitsCount( text, cursorPosition );
        var hexDigits = normalizeHexDigits( text );
        var formattedText = formatHexText( hexDigits );
        var newCursorPosition = getCursorPosition( hexDigitsBeforeCursor, formattedText.length );

        if ( formattedText !== text )
        {
            text = formattedText;
        }

        jqHexTextFiled.cursorPosition = Math.min( newCursorPosition, text.length );
        changingText = false;
    }

    function normalizeHexDigits(sourceText)
    {
        var hexDigits = sourceText.replace( /[^0-9a-fA-F]/g, "" ).toUpperCase();

        if ( maximumByteCount > 0 )
        {
            hexDigits = hexDigits.slice( 0, maximumByteCount * 2 );
        }

        return hexDigits;
    }

    function formatHexText(hexDigits)
    {
        var formattedText = "";

        for ( var i = 0; i < hexDigits.length; i += 2 )
        {
            if ( i > 0 )
            {
                formattedText += " ";
            }

            formattedText += hexDigits.substr( i, 2 );
        }

        return formattedText;
    }

    function getHexDigitsCount(sourceText, position)
    {
        var count = sourceText.slice( 0, position ).replace( /[^0-9a-fA-F]/g, "" ).length;

        if ( maximumByteCount > 0 )
        {
            count = Math.min( count, maximumByteCount * 2 );
        }

        return count;
    }

    function getCursorPosition(hexDigitCount, formattedLength)
    {
        if ( hexDigitCount <= 0 )
        {
            return 0;
        }

        var spaceCount = Math.floor( ( hexDigitCount - 1 ) / 2 );
        return Math.min( hexDigitCount + spaceCount, formattedLength );
    }
}

