#include "PropertyMaker.h"

// Qt lib import
#include <QFileDialog>
#include <QStandardPaths>

using namespace PropertyMaker;

Manage::Manage()
{
    propertyMaker_[ "READ" ] = []( const QString &type, const QString &name, const QString &value, const QString &, const bool &withSlot, const bool &withInline )->QString
    {
        return QString( "%1%2%3 %4() const\n{ return %5; }\n" ).
                arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                arg( type ).
                arg( value ).
                arg( name );
    };

    propertyMaker_[ "WRITE" ] = []( const QString &type, const QString &name, const QString &value, const QString &notifyValue, const bool &withSlot, const bool &withInline )->QString
    {
        return QString( "%1%2void %3(const %4 &newValue)\n{ if ( newValue == %5 ) { return; } %6 = newValue;%7 }\n" ).
                arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                arg( value ).
                arg( type ).
                arg( name ).
                arg( name ).
                arg( ( notifyValue.isEmpty() ) ? ( "" ) : ( QString( " emit %1( %2 );" ).arg( notifyValue ).arg( name ) ) );
    };

    propertyMaker_[ "NOTIFY" ] = []( const QString &type, const QString &name, const QString &value, const QString &, const bool &, const bool & )->QString
    {
        return QString( "Q_SIGNAL void %1(const %2 %3);\n" ).
                arg( value ).
                arg( type ).
                arg( name );
    };

    propertyMaker_[ "RESET" ] = []( const QString &type, const QString &name, const QString &value, const QString &notifyValue, const bool &withSlot, const bool &withInline )->QString
    {
        return QString( "%1%2void %3() \n{ if ( %4 == %5() ) { return; } %6 = %7();%8 }\n" ).
                arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                arg( value ).
                arg( name ).
                arg( type ).
                arg( name ).
                arg( type ).
                arg( ( notifyValue.isEmpty() ) ? ( "" ) : ( QString( " emit %1( %2 );" ).arg( notifyValue ).arg( name ) ) );
    };
}

QString Manage::make(const QString &source, const bool &withSlot, const bool &withInline)
{
    QString reply;
    bool flag = false;
    const auto &&lines = source.split( "\n" );

    reply += "// Property code start\n";

    for ( const auto &line_: lines )
    {
        auto line = line_;

        while ( line.startsWith( " " ) ) { line.remove( 0, 1 ); }
        if ( !line.startsWith( "Q_PROPERTY(" ) || !line.endsWith( ")" ) ) { continue; }

        line.remove( 0, 11 );
        line.remove( line.size() - 1, 1 );

        const auto &&elements = line.split( " " );
        if ( elements.size() % 2 ) { continue; }

        QString type;
        QString name;
        QString notifyValue;
        QList< QPair< QString, QString > > datas;

        for ( auto index = 0; index < elements.size(); index += 2 )
        {
            if ( index )
            {
                const auto &key = elements[ index ];
                const auto &value = elements[ index + 1 ];

                if ( !propertyMaker_.contains( key ) ) { continue; }

                if ( key == "NOTIFY" )
                {
                    notifyValue = value;
                }

                datas.push_back( { key, value } );
            }
            else
            {
                type = elements[ 0 ];
                name = elements[ 1 ];
            }
        }

        if ( type.isEmpty() || name.isEmpty() ) { continue; }

        if ( flag )
        {
            reply += "\n";
        }
        else
        {
            flag = true;
        }

        reply += QString( "private: %1 %2;\n" ).arg( type ).arg( name );

        for ( const auto &data: datas )
        {
            reply += propertyMaker_[ data.first ]( type, name, data.second, notifyValue, withSlot, withInline );
        }
    }

    reply += "private:\n// Property code end";

    return reply;
}
