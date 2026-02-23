/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef IMAGEGROUP_IMAGEGROUP_H_
#define IMAGEGROUP_IMAGEGROUP_H_

// ImageGroup lib import
#include <IconMaker>
#include <FontToPng>
#include <PngWarningRemover>
#include <WebPMaker>
#include <PngOptimize>
#include <JpgOptimize>

#define IMAGEGROUP_INITIALIZA \
    ICONMAKER_INITIALIZA; \
    FONTTOPNG_INITIALIZA; \
    PNGWARNINGREMOVER_INITIALIZA; \
    WEBPMAKER_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    JPGOPTIMIZE_INITIALIZA;

#endif//IMAGEGROUP_IMAGEGROUP_H_
