#pragma once

#include "RootFile.hh"
#include <TCanvas.h>
#include <TGraph.h>
#include "Waveform.hh"

class PlotterWaveform {
public:
    PlotterWaveform();
    ~PlotterWaveform();
    void Write(Waveform aWave);
    void Plot();
private:
    std::vector<double> fWaveVector;
};