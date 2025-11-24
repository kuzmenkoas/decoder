#pragma once

#include "Decoder.hh"
#include "TString.h"
#include <fstream>
#include "WriterFactory.hh"
#include "PlotterWaveform.hh"
#include "ConfigInputParser.hh"
#include "ConfigParserFactory.hh"
#include <vector>
#include "Plotter.hh"

class DecoderWaveform : public Decoder {
public:
    DecoderWaveform(TString file);
    ~DecoderWaveform();

    void Touch();
    void Decode();
    void Plot() {fPlotter->Plot();};
private:
    TString fFileName;
    std::vector<Writer*> fWriterVector;
    Plotter* fPlotter = nullptr;
    EncoderParameters fPar;
};