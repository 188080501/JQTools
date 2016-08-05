#include "HashCalculate.h"

// Qt lib import
#include <QFileDialog>
#include <QStandardPaths>
#include <QCryptographicHash>

using namespace HashCalculate;

void Manage::setSource(const QString &string)
{
    source_ = string;
    emit sourceChanged();
}

void Manage::resetSource()
{
    source_.clear();
    emit sourceChanged();
}

void Manage::resetTarget()
{
    target_.clear();
    emit targetChanged();
}

void Manage::pause()
{
    source_ = this->clipboardText();
    emit sourceChanged();
}

void Manage::clear()
{
    source_.clear();
    target_.clear();
    emit sourceChanged();
    emit targetChanged();
}

void Manage::copy()
{
    this->setClipboardText( target_ );
}

void Manage::cut()
{
    source_ = target_;
    target_.clear();
    emit sourceChanged();
    emit targetChanged();
}

void Manage::calculateToBase64()
{
    target_ = source_.toUtf8().toBase64();
    emit targetChanged();
}

void Manage::calculateFromBase64()
{
    target_ = QByteArray::fromBase64( source_.toUtf8() );
    emit targetChanged();
}

void Manage::calculateMD4()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Md4 ).toHex();
    emit targetChanged();
}

void Manage::calculateMD5()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Md5 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha1()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha1 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha224()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha224 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha256()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha256 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha384()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha384 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha512()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha512 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha3_224()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha3_224 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha3_256()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha3_256 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha3_384()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha3_384 ).toHex();
    emit targetChanged();
}

void Manage::calculateSha3_512()
{
    target_ = QCryptographicHash::hash( source_.toUtf8(), QCryptographicHash::Sha3_512 ).toHex();
    emit targetChanged();
}
