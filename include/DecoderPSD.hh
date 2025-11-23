#pragma once

#include <iostream>
#include "TString.h"
#include "EncoderParameters.hh"
#include "Writer.hh"
#include "Plotter.hh"
#include "ConfigInputParser.hh"
#include "ConfigParserFactory.hh"
#include "Decoder.hh"

// Class to decode from binary
class DecoderPSD : public Decoder {
public:
    DecoderPSD(TString file);
    ~DecoderPSD();

    void Touch();

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