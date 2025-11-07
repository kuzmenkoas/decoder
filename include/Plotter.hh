#ifndef Plotter_hh
#define Plotter_hh 1

#include "EncoderParameters.hh"
#include <iostream>
#include <TH1I.h>
#include <TCanvas.h>
#include "RootFile.hh"

struct PlotParameters {
    Int_t Nbins;
    Double_t minVal;
    Double_t maxVal;
    TString name;
};

class Plotter {
public:
    Plotter(EncoderParameters par);
    ~Plotter();
    void Write(Encoder event);
    void Plot();
private:
    void ConfigPlotter();
    void ConfigParameter(TString par);
    void HeadParameter(TString par);
    void CreateHistograms();
    EncoderParameters fParPlot;
    EncoderParameters fPar;
    std::vector<TH1*> hist;
    std::vector<PlotParameters> pltPar;
};

#endif