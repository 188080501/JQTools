/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef __TEXTGROUP_TEXTGROUP_H__
#define __TEXTGROUP_TEXTGROUP_H__

// TextGroup lib import
#include <Utf16Transform>
#include <RgbStringTransform>
#include <CaseTransform>
#include <RandomPassword>
#include <UrlEncode>
#include <JsonFormat>

#define TEXTGROUP_INITIALIZA \
    UTF16TRANSFORM_INITIALIZA; \
    RGBSTRINGTRANSFORM_INITIALIZA; \
    CASETRANSFORM_INITIALIZA; \
    RANDOMPASSWORD_INITIALIZA; \
    URLENCODE_INITIALIZA; \
    JSONFORMAT_INITIALIZA;

#endif//__TEXTGROUP_TEXTGROUP_H__
