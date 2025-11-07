#ifndef Waveform_hh
#define Waveform_hh 1

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

#endif