/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "cppfilemaker.h"

// Qt lib import
#include <QStandardPaths>

// JQLibrary import
#include "JQFile.h"

using namespace CppFileMaker;

QString Manage::make(
        const QString &macroProtectsPrefix,
        const QString &className,
        const bool &qmlExpand
    )
{
    const auto &&desktopPath = QStandardPaths::writableLocation( QStandardPaths::DesktopLocation );

    QString sourceFilePath1;
    QString sourceFilePath2;
    QString sourceFilePath3;
    QString sourceFilePath4;
    QString targetFilePath1;
    QString targetFilePath2;
    QString targetFilePath3;
    QString targetFilePath4;

    if ( qmlExpand )
    {
        sourceFilePath1 = ":/CppFileMakerFiles/template/QmlTemplate";
        sourceFilePath2 = ":/CppFileMakerFiles/template/qmltemplate.h";
        sourceFilePath3 = ":/CppFileMakerFiles/template/qmltemplate.inc";
        sourceFilePath4 = ":/CppFileMakerFiles/template/qmltemplate.cpp";
    }
    else
    {
        sourceFilePath1 = ":/CppFileMakerFiles/template/CppTemplate";
        sourceFilePath2 = ":/CppFileMakerFiles/template/cpptemplate.h";
        sourceFilePath3 = ":/CppFileMakerFiles/template/cpptemplate.inc";
        sourceFilePath4 = ":/CppFileMakerFiles/template/cpptemplate.cpp";
    }

    targetFilePath1 = QString( "%1/%2" ).arg( desktopPath, className );
    targetFilePath2 = QString( "%1/%2.h" ).arg( desktopPath, className.toLower() );
    targetFilePath3 = QString( "%1/%2.inc" ).arg( desktopPath, className.toLower() );
    targetFilePath4 = QString( "%1/%2.cpp" ).arg( desktopPath, className.toLower() );

    JQFile::writeFile( targetFilePath1, QByteArray::fromHex( "efbbbf" ) + this->getTemplateData( sourceFilePath1, macroProtectsPrefix, className ).toUtf8() );
    JQFile::writeFile( targetFilePath2, QByteArray::fromHex( "efbbbf" ) + this->getTemplateData( sourceFilePath2, macroProtectsPrefix, className ).toUtf8() );
    JQFile::writeFile( targetFilePath3, QByteArray::fromHex( "efbbbf" ) + this->getTemplateData( sourceFilePath3, macroProtectsPrefix, className ).toUtf8() );
    JQFile::writeFile( targetFilePath4, QByteArray::fromHex( "efbbbf" ) + this->getTemplateData( sourceFilePath4, macroProtectsPrefix, className ).toUtf8() );

    return "OK";
}

QString Manage::getTemplateData(
        const QString &templateFilePath,
        const QString &macroProtectsPrefix,
        const QString &className
    )
{
    auto readFileReply = JQFile::readFile( templateFilePath );
    if ( !readFileReply.first ) { return { }; }

    readFileReply.second = readFileReply.second.replace( "%classname%", className.toUtf8().toLower() );
    readFileReply.second = readFileReply.second.replace( "%ClassName%", className.toUtf8() );
    readFileReply.second = readFileReply.second.replace( "%CLASSNAME%", className.toUtf8().toUpper() );
    readFileReply.second = readFileReply.second.replace( "%MACROPROTECTSPREFIX%", macroProtectsPrefix.toUtf8().toUpper() );

    return readFileReply.second;
}
