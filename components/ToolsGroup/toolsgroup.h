/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __TOOLSGROUP_TOOLSGROUP_H__
#define __TOOLSGROUP_TOOLSGROUP_H__

// ToolsGroup lib import
#include <LinesStatistics>
#include <PngOptimize>
#ifdef TOOLSGROUP_JPGOPTIMIZE_ENABLE
#   include <JpgOptimize>
#endif
#include <LanFileTransport>
#include <QRCodeReader>

#ifdef TOOLSGROUP_JPGOPTIMIZE_ENABLE
#   define TOOLSGROUP_INITIALIZA \
    LINESSTATISTICS_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    JPGOPTIMIZE_INITIALIZA; \
    LANFILETRANSPORT_INITIALIZA; \
    QRCODEREADER_INITIALIZA;
#else
#   define TOOLSGROUP_INITIALIZA \
    LINESSTATISTICS_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    LANFILETRANSPORT_INITIALIZA; \
    QRCODEREADER_INITIALIZA;
#endif

#endif//__TOOLSGROUP_TOOLSGROUP_H__
