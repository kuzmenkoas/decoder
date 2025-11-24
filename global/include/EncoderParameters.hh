#pragma once

#include <cstdint>
#include "TMath.h"

// describtion from excel file

// bool values of parameters to encode
struct EncoderParameters {
    Bool_t qShort = false;
    Bool_t qLong = false;
    Bool_t cfd_y1 = false;
    Bool_t cfd_y2 = false;
    Bool_t baseline = false;
    Bool_t height = false;
    Bool_t eventCounter = false;
    Bool_t eventCounterPSD = false;
    Bool_t psdValue = false;
    Bool_t reverse = false;
    Bool_t entries = false;
};

// sizes of parameters to encode
struct Encoder {
    int32_t qShort;
    int32_t qLong;
    int16_t cfd_y1;
    int16_t cfd_y2;
    int16_t baseline;
    int16_t height;
    uint32_t eventCounter;
    uint32_t eventCounterPSD;
    int16_t psdValue;
};