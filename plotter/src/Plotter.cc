#include "Plotter.hh"

Plotter* Plotter::fPlotter = 0;

Plotter* Plotter::Instance() {
    if (fPlotter == 0) {
        fPlotter = new Plotter();
    }
    return fPlotter;
}

Plotter::Plotter() {
    CreateHistograms();
}

Plotter::~Plotter() {
}

void Plotter::Write(Encoder event) {
    if (fPSD.qShort != -1) hist[fPSD.qShort]->Fill(event.qShort);
    if (fPSD.qLong != -1) hist[fPSD.qShort]->Fill(event.qLong);
    if (fPSD.cfd_y1 != -1) hist[fPSD.qShort]->Fill(event.cfd_y1);
    if (fPSD.cfd_y2 != -1) hist[fPSD.qShort]->Fill(event.cfd_y2);
    if (fPSD.baseline != -1) hist[fPSD.qShort]->Fill(event.baseline);
    if (fPSD.height != -1) hist[fPSD.qShort]->Fill(event.height);
    if (fPSD.eventCounter != -1) hist[fPSD.qShort]->Fill(event.eventCounter);
    if (fPSD.eventCounterPSD != -1) hist[fPSD.qShort]->Fill(event.eventCounterPSD);
    if (fPSD.psdValue != -1) hist[fPSD.qShort]->Fill(event.psdValue);
}

void Plotter::Write(WaveformSig aWave) {
    int i = 0;
    if (fWaveform.qShort != -1) hist[fWaveform.qShort]->Fill(aWave.qShort);
    if (fWaveform.qLong != -1) hist[fWaveform.qShort]->Fill(aWave.qLong);
    if (fWaveform.baseline != -1) hist[fWaveform.qShort]->Fill(aWave.baseline);
}

void Plotter::CreateHistograms() {
    std::vector<PlotterHist> fHist = ConfigParserFactory::Instance()->BuildParser()->GetPlotterHist();

    for (int i = 0; i < fHist.size(); i++) {
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "qShort") fPSD.qShort = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "qLong") fPSD.qLong = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "cfd_y1") fPSD.cfd_y1 = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "cfd_y2") fPSD.cfd_y2 = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "baseline") fPSD.baseline = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "height") fPSD.height = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "eventCounter") fPSD.eventCounter = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "eventCounterPSD") fPSD.eventCounterPSD = i;
        if (fHist[i].decoder == "PSD" && fHist[i].parameter == "psdValue") fPSD.psdValue = i;

        if (fHist[i].decoder == "Waveform" && fHist[i].parameter == "qShort") fWaveform.qShort = i;
        if (fHist[i].decoder == "Waveform" && fHist[i].parameter == "qLong") fWaveform.qLong = i;
        if (fHist[i].decoder == "Waveform" && fHist[i].parameter == "baseline") fWaveform.baseline = i;

        hist.push_back(new TH1D(fHist[i].parameter+fHist[i].decoder, fHist[i].parameter+fHist[i].decoder, fHist[i].Nbins, fHist[i].min, fHist[i].max));
    }
}

void Plotter::Plot() {
    std::vector<PlotterHist> fHist = ConfigParserFactory::Instance()->BuildParser()->GetPlotterHist();
    for (int i = 0; i < fHist.size(); i++) {
        TString name = fHist[i].parameter+fHist[i].decoder;
        TCanvas* c = new TCanvas(name, "Canvas", 800, 600);
        hist[i]->Draw();
        hist[i]->Write(name);
        c->SaveAs(name+".png");
    }
}