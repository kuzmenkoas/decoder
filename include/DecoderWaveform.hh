#ifndef DecoderWaveform_hh
#define DecoderWaveform_hh 1

#include "Decoder.hh"
#include "TString.h"
#include <fstream>
#include "WriterFactory.hh"
// #include "Waveform.hh"

class DecoderWaveform : public Decoder {
public:
    DecoderWaveform(TString file);
    ~DecoderWaveform();

    void Touch();
    void Decode();
private:
    TString fFileName;
};

#endif