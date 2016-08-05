#ifndef __TEXTGROUP_TEXTGROUP_H__
#define __TEXTGROUP_TEXTGROUP_H__

// TextGroup lib import
#include "Utf16Transform.h"
#include "RgbStringTransform.h"
#include "CaseTransform.h"
#include "RandomPassword.h"
#include "UrlEncode.h"
#include "JsonFormat.h"

#define TEXTGROUP_INITIALIZA \
    UTF16TRANSFORM_INITIALIZA; \
    RGBSTRINGTRANSFORM_INITIALIZA; \
    CASETRANSFORM_INITIALIZA; \
    RANDOMPASSWORD_INITIALIZA; \
    URLENCODE_INITIALIZA; \
    JSONFORMAT_INITIALIZA;

#endif//__TEXTGROUP_TEXTGROUP_H__
