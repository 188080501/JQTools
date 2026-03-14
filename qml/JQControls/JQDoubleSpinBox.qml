import QtQuick 2.15
import JQControls 1.0

JQSpinBox {
    id: jqDoubleSpinBox
    decimals: 1

    validator: DoubleValidator {
        bottom: Math.min( jqDoubleSpinBox.from, jqDoubleSpinBox.to )
        top:  Math.max( jqDoubleSpinBox.from, jqDoubleSpinBox.to )
        decimals: jqDoubleSpinBox.decimals
        notation: DoubleValidator.StandardNotation
    }

    textFromValue: function(value, locale) {
        return Number( value / decimalFactor ).toLocaleString( locale, 'f', jqDoubleSpinBox.decimals )
    }

    valueFromText: function(text, locale) {
        try
        {
            return Math.round( Number.fromLocaleString( locale, text ) * decimalFactor )
        }
        catch (error)
        {
            return 0;
        }
    }
}

