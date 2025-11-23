#include "DecoderFactory.hh"

DecoderFactory* DecoderFactory::fDecoderFactory = 0;

DecoderFactory* DecoderFactory::Instance() {
    if (fDecoderFactory == 0) {
        fDecoderFactory = new DecoderFactory();
    }
    return fDecoderFactory;
}

DecoderFactory::DecoderFactory() {
}

DecoderFactory::~DecoderFactory() {
    delete fDecoderFactory;
}

Decoder* DecoderFactory::BuildDecoder(TString file, DecoderType aType) {
    Decoder* aDecoder = nullptr;
    switch (aType) {
    case DecoderType::PSDType:
        aDecoder = new DecoderPSD(file);
        break;
    case DecoderType::WaveformType:
        aDecoder = new DecoderWaveform(file);
        break;
    }
    return aDecoder;
}