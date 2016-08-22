#ifndef __JQToolsLibrary_h__
#define __JQToolsLibrary_h__

// Qt lib import
#include <QObject>

#define JQTOOLS_VERSIONSTRING "16.8.22"

class AbstractTool: public QObject
{
    Q_OBJECT

public slots:
    QString jqToolsVersionString();

    QString clipboardText();

    void setClipboardText(const QString &string);
};

#endif//__JQToolsLibrary_h__
