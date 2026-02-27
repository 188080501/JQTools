/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#include "filehashcalculate.h"

// Qt lib import
#include <QCryptographicHash>
#include <QFile>
#include <QFileInfo>

using namespace FileHashCalculate;

namespace
{

bool calculateFileHash(
        const QString &filePath,
        QString &md5Value,
        QString &sha1Value,
        QString &sha256Value
    )
{
    QFile file( filePath );
    if ( !file.open( QIODevice::ReadOnly ) )
    {
        return false;
    }

    QCryptographicHash md5Hasher( QCryptographicHash::Md5 );
    QCryptographicHash sha1Hasher( QCryptographicHash::Sha1 );
    QCryptographicHash sha256Hasher( QCryptographicHash::Sha256 );

    while ( true )
    {
        const auto data = file.read( 32 * 1024 * 1024 );

        if ( data.isEmpty() )
        {
            if ( file.atEnd() ) { break; }

            return false;
        }

        md5Hasher.addData( data );
        sha1Hasher.addData( data );
        sha256Hasher.addData( data );
    }

    md5Value = md5Hasher.result().toHex();
    sha1Value = sha1Hasher.result().toHex();
    sha256Value = sha256Hasher.result().toHex();

    return true;
}

}

void Manage::chooseFile()
{
    const auto selectedFilePath = AbstractTool::getOpenFileName(
                QStringLiteral( "e9e36414-dd8b-45b7-9f02-58ef674da646" ),
                QStringLiteral( "\u8BF7\u9009\u62E9\u9700\u8981\u8BA1\u7B97\u54C8\u5E0C\u503C\u7684\u6587\u4EF6" ),
                QStringLiteral( "All Files (*)" )
            );

    if ( selectedFilePath.isEmpty() ) { return; }

    filePath_ = selectedFilePath;
    md5Value_.clear();
    sha1Value_.clear();
    sha256Value_.clear();

    emit filePathChanged();
    emit md5ValueChanged();
    emit sha1ValueChanged();
    emit sha256ValueChanged();
}

QString Manage::calculate()
{
    const auto clearHashValues = [this]()
    {
        md5Value_.clear();
        sha1Value_.clear();
        sha256Value_.clear();

        emit md5ValueChanged();
        emit sha1ValueChanged();
        emit sha256ValueChanged();
    };

    if ( filePath_.isEmpty() )
    {
        clearHashValues();
        return "empty file path";
    }

    if ( !QFileInfo( filePath_ ).isFile() )
    {
        clearHashValues();
        return "file not exist";
    }

    QString md5Value;
    QString sha1Value;
    QString sha256Value;

    if ( !calculateFileHash( filePath_, md5Value, sha1Value, sha256Value ) )
    {
        clearHashValues();
        return "calculate hash error";
    }

    md5Value_ = md5Value;
    sha1Value_ = sha1Value;
    sha256Value_ = sha256Value;

    emit md5ValueChanged();
    emit sha1ValueChanged();
    emit sha256ValueChanged();

    return "OK";
}

void Manage::clear()
{
    filePath_.clear();
    md5Value_.clear();
    sha1Value_.clear();
    sha256Value_.clear();

    emit filePathChanged();
    emit md5ValueChanged();
    emit sha1ValueChanged();
    emit sha256ValueChanged();
}

void Manage::copyMd5()
{
    if ( md5Value_.isEmpty() ) { return; }

    this->setClipboardText( md5Value_ );
}

void Manage::copySha1()
{
    if ( sha1Value_.isEmpty() ) { return; }

    this->setClipboardText( sha1Value_ );
}

void Manage::copySha256()
{
    if ( sha256Value_.isEmpty() ) { return; }

    this->setClipboardText( sha256Value_ );
}
