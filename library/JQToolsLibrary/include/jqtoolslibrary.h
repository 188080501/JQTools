/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef JQTOOLSLIBRARY_H_
#define JQTOOLSLIBRARY_H_

// C++ lib import
#include <functional>

// Qt lib import
#include <QByteArray>
#include <QObject>
#include <QPair>
#include <QPointer>
#include <QFileInfo>

class QQmlApplicationEngine;
class QDir;
class QFileInfo;

class AbstractTool: public QObject
{
    Q_OBJECT

public:
    static void foreachFileFromDirectory(
            const QDir &directory,
            const std::function< void(const QFileInfo &) > &each,
            const bool recursion = false
        );

    static void foreachDirectoryFromDirectory(
            const QDir &directory,
            const std::function< void(const QDir &) > &each,
            const bool recursion = false
        );

    static bool writeFile(
            const QFileInfo &targetFilePath,
            const QByteArray &data,
            const bool cover = true
        );

    static QPair< bool, QByteArray > readFile(const QFileInfo &filePath);

    static QString fileSizeString(const qint64 size);

public slots:
    QString jqToolsVersionString();

    QString clipboardText();

    void setClipboardText(const QString &string);
};

#endif//JQTOOLSLIBRARY_H_
