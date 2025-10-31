#ifndef Decoder_hh
#define Decoder_hh 1

#include <iostream>
#include "TString.h"
#include "EncoderParameters.hh"
#include "Writer.hh"
#include "Plotter.hh"

// Class to decode from binary
class Decoder {
public:
    Decoder(TString file, EncoderParameters par);
    ~Decoder();

    void SetWriter(Writer* writer) {fWriter = writer;};
    // decode parameters from par
    void Decode();
    void Plot() {fPlotter->Plot();};
private:
    Int_t GetParametersNumber();
    TString fFileName;
    EncoderParameters fPar;
    Writer* fWriter = nullptr;
    Plotter* fPlotter = nullptr;
};

#endif