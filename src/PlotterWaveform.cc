#include "PlotterWaveform.hh"

PlotterWaveform::PlotterWaveform() {
    gr = new TGraph();
}

PlotterWaveform::~PlotterWaveform() {
}

void PlotterWaveform::Write(Waveform aWave) {
    if (aWave.i < 2000) gr->SetPoint(aWave.i, aWave.i, aWave.wave);
}

void PlotterWaveform::Plot() {
    TCanvas* c = new TCanvas("waveform", "Canvas", 800, 600);
    gr->Draw("AL");
    gr->Write("waveform");
    c->SaveAs("waveform.png");
}