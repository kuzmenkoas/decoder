#include "PlotterWaveform.hh"
#include <iostream>
#include "ConfigInputParser.hh"
#include "ConfigParserFactory.hh"

PlotterWaveform::PlotterWaveform() {
    for (int i = 0; i < ConfigParserFactory::Instance()->BuildParser()->GetWaveformNumber(); i++) {
        fWaveVector.push_back(0);
    }
}

PlotterWaveform::~PlotterWaveform() {
}

// to avoid storing too much data in RAM estimates mean
// ex. 8000 entries of signal for 1 event + get 1M entries
// will get 2 bytes * 8000 * 1000000 = 15 GB
void PlotterWaveform::Write(Waveform aWave) {
    fWaveVector[aWave.t] += aWave.wave;
}

void PlotterWaveform::Plot() {
    TGraph* gr = new TGraph();
    for (int i = 0; i < fWaveVector.size(); i++) gr->SetPoint(i, i, fWaveVector[i]/ConfigParserFactory::Instance()->BuildParser()->GetEvents());
    TCanvas* c = new TCanvas("waveform", "Canvas", 800, 600);
    gr->Draw("AL");
    gr->Write("waveform");
    c->SaveAs("waveform.png");
}