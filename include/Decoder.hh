#ifndef Decoder_hh
#define Decoder_hh 1

#include <iostream>
#include "TString.h"
#include "EncoderParameters.hh"
#include "Writer.hh"
#include "Plotter.hh"
#include "ConfigInputParser.hh"

// Class to decode from binary
class Decoder {
public:
    Decoder(TString file, EncoderParameters par);
    ~Decoder();

    // decode parameters from par
    void Decode();
    void Plot() {fPlotter->Plot();};
private:
    Int_t GetParametersNumber();
    TString fFileName;
    EncoderParameters fPar;
    Plotter* fPlotter = nullptr;
    Output outWriters;
    std::vector<Writer*> fWriterVector;
};

#endif