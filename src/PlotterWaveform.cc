#include "PlotterWaveform.hh"
#include <iostream>
#include "ConfigInputParser.hh"

PlotterWaveform::PlotterWaveform() {
}

PlotterWaveform::~PlotterWaveform() {
}

// to avoid storing too much data in RAM estimates mean
// ex. 8000 entries of signal for 1 event + get 1M entries
// will get 2 bytes * 8000 * 1000000 = 15 GB
void PlotterWaveform::Write(Waveform aWave) {
    if (!fWave.try_emplace(aWave.t, aWave.wave).second) {
        for (auto& [t, wave] : fWave)
            if (t == aWave.t) wave += aWave.wave;
    }
}

void PlotterWaveform::Plot() {
    TGraph* gr = new TGraph();
    for (auto& [t, wave] : fWave) gr->SetPoint(t, t, wave/ConfigInputParser::Instance()->GetEvents());
    TCanvas* c = new TCanvas("waveform", "Canvas", 800, 600);
    gr->Draw("AL");
    gr->Write("waveform");
    c->SaveAs("waveform.png");
}