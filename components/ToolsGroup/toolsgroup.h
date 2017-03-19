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
#include <JpgOptimize>
#include <LanFileTransport>

#define TOOLSGROUP_INITIALIZA \
    LINESSTATISTICS_INITIALIZA; \
    PNGOPTIMIZE_INITIALIZA; \
    JPGOPTIMIZE_INITIALIZA; \
    LANFILETRANSPORT_INITIALIZA;

#endif//__TOOLSGROUP_TOOLSGROUP_H__
