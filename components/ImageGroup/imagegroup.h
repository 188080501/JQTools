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
#include <WebPMaker>
#include <PngWarningRemover>
#include <PngOptimize>
#ifdef IMAGEGROUP_JPGOPTIMIZE_ENABLE
#   include <JpgOptimize>
#endif

#ifdef IMAGEGROUP_JPGOPTIMIZE_ENABLE
#   define IMAGEGROUP_INITIALIZA \
    ICONMAKER_INITIALIZA; \
    FONTTOPNG_INITIALIZA; \
    WEBPMAKER_INITIALIZA; \
    PNGWARNINGREMOVER_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    JPGOPTIMIZE_INITIALIZA;
#else
#   define IMAGEGROUP_INITIALIZA \
    ICONMAKER_INITIALIZA; \
    FONTTOPNG_INITIALIZA; \
    WEBPMAKER_INITIALIZA; \
    PNGWARNINGREMOVER_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA;
#endif

#endif//IMAGEGROUP_IMAGEGROUP_H_
