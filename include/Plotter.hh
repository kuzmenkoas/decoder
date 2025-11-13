#ifndef Plotter_hh
#define Plotter_hh 1

#include "EncoderParameters.hh"
#include <iostream>
#include <TH1I.h>
#include <TCanvas.h>
#include "RootFile.hh"
#include "Waveform.hh"

struct PlotParameters {
    Int_t Nbins;
    Double_t minVal;
    Double_t maxVal;
    TString name;
};

class Plotter {
public:
    Plotter(EncoderParameters par);
    Plotter(TString id);
    ~Plotter();
    void Write(Encoder event);
    void Write(WaveformSig aWave);
    void Plot();
private:
    void ConfigPlotter();
    void ConfigPlotter(TString id);
    void ConfigParameter(TString par);
    void CreateHistograms();
    EncoderParameters fParPlot;
    EncoderParameters fPar;
    std::vector<TH1*> hist;
    std::vector<PlotParameters> pltPar;

    TString fId = "";
};

#endif