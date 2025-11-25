#pragma once

#include "EncoderParameters.hh"
#include <iostream>
#include <TH1I.h>
#include <TCanvas.h>
#include "RootFile.hh"
#include "Waveform.hh"
#include "ConfigParserFactory.hh"

struct PlotConfig {
    int qShort = -1;
    int qLong = -1;
    int cfd_y1 = -1;
    int cfd_y2 = -1;
    int baseline = -1;
    int height = -1;
    int eventCounter = -1;
    int eventCounterPSD = -1;
    int psdValue = -1;
};

class Plotter {
public:
    static Plotter* Instance();

    void Write(Encoder event);
    void Write(WaveformSig aWave);
    void Plot();
private:
    Plotter();
    ~Plotter();

    static Plotter* fPlotter;
    void CreateHistograms();

    PlotConfig fPSD;
    PlotConfig fWaveform;
    std::vector<TH1*> hist;
};