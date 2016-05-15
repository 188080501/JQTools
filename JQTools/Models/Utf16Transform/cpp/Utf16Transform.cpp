#include "Utf16Transform.h"

// Qt lib import
#include <QImage>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QApplication>
#include <QClipboard>

// JQToolsLibrary import
#include "JQToolsLibrary.hpp"

using namespace Utf16Transform;

Manage::Manage()
{ }

Manage::~Manage()
{ }

QString Manage::toUtf16(const QString &string)
{
    QString source = string;
    QString target;

    for ( auto c: source )
    {
        if ( c.unicode() > 0xff )
        {
            target += "\\u";
            target += QString::number( c.unicode(), 16 ).toUpper().rightJustified( 4, '0' );
        }
        else
        {
            target += c;
        }
    }

    return target;
}

QString Manage::fromUtf16(const QString &string)
{
    QString source = string;
    QString target;

    while ( !source.isEmpty() )
    {
        if ( ( source.size() >= 6 ) && source.startsWith( "\\u" ))
        {
            target += QChar( ushort( source.mid( 2, 4 ).toUShort( 0, 16 ) ) );
            source.remove( 0, 6 );
        }
        else
        {
            target += source.at( 0 );
            source.remove( 0, 1 );
        }
    }

    return target;
}

QString Manage::clipboardText()
{
    return qApp->clipboard()->text();
}

void Manage::setClipboardText(const QString &string)
{
    qApp->clipboard()->setText( string );
}
