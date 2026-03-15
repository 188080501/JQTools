/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef QRCODEGROUP_QRCODEGROUP_H_
#define QRCODEGROUP_QRCODEGROUP_H_

// QRCodeGroup lib import
#ifndef Q_OS_WASM
#include <QRCodeMaker>
#include <BarcodeMaker>
#include <QRCodeReader>
#endif

#ifdef Q_OS_WASM
#define QRCODEGROUP_INITIALIZA
#else
#define QRCODEGROUP_INITIALIZA \
    QRCODEMAKER_INITIALIZA; \
    BARCODEMAKER_INITIALIZA; \
    QRCODEREADER_INITIALIZA;
#endif

#endif//QRCODEGROUP_QRCODEGROUP_H_
