/*
    This file is part of JQTools

    Project introduce: https://github.com/188080501/JQTools

    Copyright: Jason

    Contact email: Jason@JasonServer.com

    GitHub: https://github.com/188080501/
*/

#ifndef CALCULATEGROUP_CALCULATEGROUP_H_
#define CALCULATEGROUP_CALCULATEGROUP_H_

// CalculateGroup lib import
#include <HashCalculate>
#include <FileHashCalculate>
#include <TimestampTransform>
#include <BinarySearchAssistant>
#include <RsaKeyGenerate>
#include <RsaCrypt>

#define CALCULATEGROUP_INITIALIZA \
    HASHCALCULATE_INITIALIZA; \
    FILEHASHCALCULATE_INITIALIZA; \
    TIMESTAMPTRANSFORM_INITIALIZA;\
    BINARYSEARCHASSISTANT_INITIALIZA; \
    RSAKEYGENERATE_INITIALIZA; \
    RSACRYPT_INITIALIZA;

#endif//CALCULATEGROUP_CALCULATEGROUP_H_
