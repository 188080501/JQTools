/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef MAKEGROUP_MAKEGROUP_H_
#define MAKEGROUP_MAKEGROUP_H_

// MakeGroup lib import
#include <IconMaker>
#include <FontToPng>
#include <QRCodeMaker>
#include <BarcodeMaker>
#include <WebPMaker>

#define MAKEGROUP_INITIALIZA \
    ICONMAKER_INITIALIZA; \
    FONTTOPNG_INITIALIZA; \
    QRCODEMAKER_INITIALIZA; \
    BARCODEMAKER_INITIALIZA; \
    WEBPMAKER_INITIALIZA;

#endif//MAKEGROUP_MAKEGROUP_H_
