#ifndef DecoderFactory_hh
#define DecoderFactory_hh 1

#include "Decoder.hh"
#include "DecoderPSD.hh"
#include "DecoderWaveform.hh"

enum DecoderType {
    PSD,
    Waveform
};

class DecoderFactory {
public:
    static DecoderFactory* Instance();
    Decoder* BuildDecoder(TString file, DecoderType aType);
private:
    DecoderFactory();
    ~DecoderFactory();
    static DecoderFactory* fDecoderFactory;
};

#endif