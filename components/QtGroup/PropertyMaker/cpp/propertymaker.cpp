/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "propertymaker.h"

// Qt lib import
#include <QFileDialog>
#include <QStandardPaths>

using namespace PropertyMaker;

Manage::Manage()
{
    propertyMaker_[ "READ" ] = []( const QString &type, const QString &name, const QString &value, const QString &, const bool &withSlot, const bool &withInline )->QString
    {
        return QString( "%1%2%3 %4() const\n{ return %5_; }\n" ).
                arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                arg( type ).
                arg( value ).
                arg( name );
    };

    propertyMaker_[ "WRITE" ] = []( const QString &type, const QString &name, const QString &value, const QString &notifyValue, const bool &withSlot, const bool &withInline )->QString
    {
        if ( type == "qreal" )
        {
            return QString( "%1%2void %3(const %4 &newValue)\n{ if ( qAbs( newValue - %5_ ) < 0.00001 ) { return; } %6_ = newValue;%7 }\n" ).
                    arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                    arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                    arg( value ).
                    arg( type ).
                    arg( name ).
                    arg( name ).
                    arg( ( notifyValue.isEmpty() ) ? ( "" ) : ( QString( " emit %1( %2_ );" ).arg( notifyValue ).arg( name ) ) );
        }
        else
        {
            return QString( "%1%2void %3(const %4 &newValue)\n{ if ( newValue == %5_ ) { return; } %6_ = newValue;%7 }\n" ).
                    arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                    arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                    arg( value ).
                    arg( type ).
                    arg( name ).
                    arg( name ).
                    arg( ( notifyValue.isEmpty() ) ? ( "" ) : ( QString( " emit %1( %2_ );" ).arg( notifyValue ).arg( name ) ) );
        }
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
        return QString( "%1%2void %3() \n{ if ( %4_ == %5() ) { return; } %6_ = %7();%8 }\n" ).
                arg( ( withSlot ) ? ( "public: Q_SLOT " ) : ( "" ) ).
                arg( ( withInline ) ? ( "inline " ) : ( "" ) ).
                arg( value ).
                arg( name ).
                arg( type ).
                arg( name ).
                arg( type ).
                arg( ( notifyValue.isEmpty() ) ? ( "" ) : ( QString( " emit %1( %2_ );" ).arg( notifyValue ).arg( name ) ) );
    };
}

QString Manage::make(const QString &source, const bool &withSlot, const bool &withInline)
{
    QString reply;
    bool flag = false;
    const auto &&lines = source.split( "\n" );

    reply += "// Property code start\n";

    for ( const auto &rawLine: lines )
    {
        auto line = rawLine;

        while ( line.startsWith( " " ) ) { line.remove( 0, 1 ); }
        if ( !line.startsWith( "Q_PROPERTY(" ) || !line.endsWith( ")" ) ) { continue; }

        while ( line.startsWith( "Q_PROPERTY( " ) ) { line.remove( 11, 1 ); }
        while ( line.endsWith( " )" ) ) { line.remove( line.size() - 2, 1 ); }

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

        if ( type == "qreal" )
        {
            reply += QString( "private: %1 %2_ = 0.0;\n" ).arg( type ).arg( name );
        }
        else if ( type == "int" )
        {
            reply += QString( "private: %1 %2_ = 0;\n" ).arg( type ).arg( name );
        }
        else if ( type == "bool" )
        {
            reply += QString( "private: %1 %2_ = false;\n" ).arg( type ).arg( name );
        }
        else
        {
            reply += QString( "private: %1 %2_;\n" ).arg( type ).arg( name );
        }

        for ( const auto &data: datas )
        {
            reply += propertyMaker_[ data.first ]( type, name, data.second, notifyValue, withSlot, withInline );
        }
    }

    reply += "private:\n// Property code end";

    return reply;
}
