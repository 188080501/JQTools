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
    propertyMaker_[ "READ" ] = [](const QString &type, const QString &functionName, const QString &valueName, const QString &, const bool &withThreadSafe, const QString &className)->QPair< QString, QString >
    {
        QString statementTemplate =
                "public: Q_SLOT inline %TYPE% %FUNCTION_NAME%() const;\n";

        QString accomplishCode =
                "inline %TYPE% %CLASS_NAME%::%FUNCTION_NAME%() const\n"
                "{ %MUTEX_LOCK%%COPY_BUFFER%%MUTEX_UNLOCK%return %BUFFER_NAME%; }\n";

        statementTemplate.replace( "%TYPE%", type );
        statementTemplate.replace( "%FUNCTION_NAME%", functionName );
        statementTemplate.replace( "%VALUE_NAME%", valueName );
        statementTemplate.replace( "%CLASS_NAME%", className );

        accomplishCode.replace( "%COPY_BUFFER%", ( withThreadSafe ) ? ( "const auto result = %VALUE_NAME%_; " ) : ( "" ) );
        accomplishCode.replace( "%BUFFER_NAME%", ( withThreadSafe ) ? ( "result" ) : ( "%VALUE_NAME%_" ) );

        accomplishCode.replace( "%TYPE%", type );
        accomplishCode.replace( "%FUNCTION_NAME%", functionName );
        accomplishCode.replace( "%VALUE_NAME%", valueName );
        accomplishCode.replace( "%CLASS_NAME%", className );

        accomplishCode.replace( "%MUTEX_LOCK%", ( withThreadSafe ) ? ( "mutex_.lock(); " ) : ( "" ) );
        accomplishCode.replace( "%MUTEX_UNLOCK%", ( withThreadSafe ) ? ( "mutex_.unlock(); " ) : ( "" ) );

        return { statementTemplate, accomplishCode };
    };

    propertyMaker_[ "WRITE" ] = [](const QString &type, const QString &functionName, const QString &valueName, const QString &notifyFunctionName, const bool &withThreadSafe, const QString &className)->QPair< QString, QString >
    {
        QString statementTemplate =
                "public: Q_SLOT inline void %FUNCTION_NAME%(const %TYPE% &newValue);\n";

        QString accomplishCode =
                "inline void %CLASS_NAME%::%FUNCTION_NAME%(const %TYPE% &newValue)\n"
                "{ %MUTEX_LOCK%if ( %EQUALITY_JUDGMENT% ) { %MUTEX_UNLOCK%return; } %VALUE_NAME%_ = newValue; %COPY_BUFFER%%MUTEX_UNLOCK%emit %NOTIFY_FUNCTION_NAME%( %BUFFER_NAME% ); }\n";

        statementTemplate.replace( "%TYPE%", type );
        statementTemplate.replace( "%FUNCTION_NAME%", functionName );
        statementTemplate.replace( "%VALUE_NAME%", valueName );
        statementTemplate.replace( "%CLASS_NAME%", className );

        accomplishCode.replace( "%EQUALITY_JUDGMENT%", ( type == "qreal" ) ? ( "qAbs( newValue - %VALUE_NAME%_ ) < 0.000001" ) : ( "newValue == %VALUE_NAME%_" ) );
        accomplishCode.replace( "%COPY_BUFFER%", ( withThreadSafe ) ? ( "const auto result = %VALUE_NAME%_; " ) : ( "" ) );
        accomplishCode.replace( "%BUFFER_NAME%", ( withThreadSafe ) ? ( "result" ) : ( "%VALUE_NAME%_" ) );

        accomplishCode.replace( "%TYPE%", type );
        accomplishCode.replace( "%FUNCTION_NAME%", functionName );
        accomplishCode.replace( "%VALUE_NAME%", valueName );
        accomplishCode.replace( "%CLASS_NAME%", className );
        accomplishCode.replace( "%NOTIFY_FUNCTION_NAME%", notifyFunctionName );

        accomplishCode.replace( "%MUTEX_LOCK%", ( withThreadSafe ) ? ( "mutex_.lock(); " ) : ( "" ) );
        accomplishCode.replace( "%MUTEX_UNLOCK%", ( withThreadSafe ) ? ( "mutex_.unlock(); " ) : ( "" ) );

        return { statementTemplate, accomplishCode };
    };

    propertyMaker_[ "NOTIFY" ] = []( const QString &type, const QString &functionName, const QString &valueName, const QString &, const bool &, const QString &className)->QPair< QString, QString >
    {
        QString statementTemplate =
                "Q_SIGNAL void %FUNCTION_NAME%(const %TYPE% %VALUE_NAME%);\n";

        statementTemplate.replace( "%TYPE%", type );
        statementTemplate.replace( "%FUNCTION_NAME%", functionName );
        statementTemplate.replace( "%VALUE_NAME%", valueName );
        statementTemplate.replace( "%CLASS_NAME%", className );

        return { statementTemplate, { } };
    };
}

QVariantMap Manage::make(const QString &source, const bool &withThreadSafe, const QString &className)
{
    QString statementCode;
    QString accomplishCode;

    bool flag = false;
    const auto &&lines = source.split( "\n" );

    statementCode += "// Property statement code start\n";
    accomplishCode += "// Property accomplish code start\n";

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
        QString valueName;
        QString notifyFunctionName;
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
                    notifyFunctionName = value;
                }

                datas.push_back( { key, value } );
            }
            else
            {
                type = elements[ 0 ];
                valueName = elements[ 1 ];
            }
        }

        if ( type.isEmpty() || valueName.isEmpty() ) { continue; }

        if ( flag )
        {
            statementCode += "\n";
            accomplishCode += "\n";
        }
        else
        {
            flag = true;
        }

        if ( type == "qreal" )
        {
            statementCode += QString( "private: %1 %2_ = 0.0;\n" ).arg( type ).arg( valueName );
        }
        else if ( type == "int" )
        {
            statementCode += QString( "private: %1 %2_ = 0;\n" ).arg( type ).arg( valueName );
        }
        else if ( type == "bool" )
        {
            statementCode += QString( "private: %1 %2_ = false;\n" ).arg( type ).arg( valueName );
        }
        else
        {
            statementCode += QString( "private: %1 %2_;\n" ).arg( type ).arg( valueName );
        }

        for ( const auto &data: datas )
        {
            auto pair = propertyMaker_[ data.first ]( type, data.second, valueName, notifyFunctionName, withThreadSafe, className );

            statementCode += pair.first;
            accomplishCode += pair.second;
        }
    }

    while ( statementCode.contains( "\n\n\n" ) )
    {
        statementCode.replace( "\n\n\n", "\n\n" );
    }

    while ( accomplishCode.contains( "\n\n\n" ) )
    {
        accomplishCode.replace( "\n\n\n", "\n\n" );
    }

    statementCode += "private:\n// Property statement code end";
    accomplishCode += "// Property accomplish code end";

    return {
        { "statementCode", statementCode },
        { "accomplishCode", accomplishCode },
    };
}
