#include "PlotterWaveform.hh"

PlotterWaveform::PlotterWaveform() {
    gr = new TGraph();
}

PlotterWaveform::~PlotterWaveform() {
}

void PlotterWaveform::Write(Waveform aWave) {
    if ((aWave.id > 4120) && (aWave.id < 4122)) gr->SetPoint(aWave.t, aWave.t, aWave.wave);
}

void PlotterWaveform::Plot() {
    TCanvas* c = new TCanvas("waveform", "Canvas", 800, 600);
    gr->Draw("AL");
    gr->Write("waveform");
    c->SaveAs("waveform.png");
}