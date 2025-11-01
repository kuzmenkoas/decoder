#ifndef PlotterWaveform_hh
#define PlotterWaveform_hh 1

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
    TGraph* gr = nullptr;
};

#endif