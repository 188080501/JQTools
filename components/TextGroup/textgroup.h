/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef TEXTGROUP_TEXTGROUP_H_
#define TEXTGROUP_TEXTGROUP_H_

// TextGroup lib import
#include <Utf16Transform>
#include <RgbStringTransform>
#include <CaseTransform>
#include <RandomPassword>
#include <RandomUuid>
#include <UrlEncode>
#include <JsonFormat>
#include <StringSort>

#define TEXTGROUP_INITIALIZA \
    UTF16TRANSFORM_INITIALIZA; \
    RGBSTRINGTRANSFORM_INITIALIZA; \
    CASETRANSFORM_INITIALIZA; \
    RANDOMPASSWORD_INITIALIZA; \
    RANDOMUUID_INITIALIZA; \
    URLENCODE_INITIALIZA; \
    JSONFORMAT_INITIALIZA; \
    STRINGSORT_INITIALIZA;

#endif//TEXTGROUP_TEXTGROUP_H_
