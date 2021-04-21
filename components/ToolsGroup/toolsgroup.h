/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef TOOLSGROUP_TOOLSGROUP_H_
#define TOOLSGROUP_TOOLSGROUP_H_

// ToolsGroup lib import
#include <LinesStatistics>
#include <ScreenColorPicker>
#include <PngOptimize>
#ifdef TOOLSGROUP_JPGOPTIMIZE_ENABLE
#   include <JpgOptimize>
#endif
#include <LanFileTransport>
#include <QRCodeReader>
#include <BatchReplacement>

#ifdef TOOLSGROUP_JPGOPTIMIZE_ENABLE
#   define TOOLSGROUP_INITIALIZA \
    LINESSTATISTICS_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    JPGOPTIMIZE_INITIALIZA; \
    LANFILETRANSPORT_INITIALIZA; \
    QRCODEREADER_INITIALIZA; \
    BATCHREPLACEMENT_INITIALIZA;\
    SCREENCOLORPICKER_INITIALIZA;
#else
#   define TOOLSGROUP_INITIALIZA \
    LINESSTATISTICS_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    LANFILETRANSPORT_INITIALIZA; \
    QRCODEREADER_INITIALIZA; \
    BATCHREPLACEMENT_INITIALIZA;\
    SCREENCOLORPICKER_INITIALIZA;
#endif

#endif//TOOLSGROUP_TOOLSGROUP_H_
