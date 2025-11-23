#pragma once

#include <stdio.h>

struct Waveform {
    int id;
    int t;
    int16_t wave;
};

struct WaveformSig {
    int baseline;
    int qShort;
    int qLong;
};