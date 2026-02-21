/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef GROUP_QRCODEGROUP_BARCODEMAKER_CPP_BARCODEGENERATOR_H_
#define GROUP_QRCODEGROUP_BARCODEMAKER_CPP_BARCODEGENERATOR_H_

// Qt lib import
#include <QImage>
#include <QString>

class BarcodeGenerator
{
public:
    static qint64 makeNumber(const qint64 rawNumber);

    static QImage makeBarcode(const qint64 number);

private:
    static void paintByteA(QImage &image, const int number, const int pos);

    static void paintByteB(QImage &image, const int number, const int pos);

    static void paintByteC(QImage &image, const int number, const int pos);

    static void paintLines(QImage &image, const QString &key, const int pos, const int len = 100);

    static void paintLine(QImage &image, const bool black, const int pos, const int len = 100);
};

#endif//GROUP_QRCODEGROUP_BARCODEMAKER_CPP_BARCODEGENERATOR_H_
