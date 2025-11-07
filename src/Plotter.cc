#include "Plotter.hh"

Plotter::Plotter(EncoderParameters par) : fPar(par) {
    ConfigPlotter();
    CreateHistograms();
}

Plotter::~Plotter() {
}

void Plotter::ConfigPlotter() {
    std::cout << "Choose parameter to plot (multiply input, example: 123 for 3 parameters to plot)" << std::endl;
    int i = 0;
    std::cout << " (" << i++ << ") exit" << std::endl;
    if (fPar.qShort) std::cout << " (" << i++ << ") qShort" << std::endl;
    if (fPar.qLong) std::cout << " (" << i++ << ") qLong" << std::endl;
    if (fPar.cfd_y1) std::cout << " (" << i++ << ") cfd_y1" << std::endl;
    if (fPar.cfd_y2) std::cout << " (" << i++ << ") cfd_y2" << std::endl;
    if (fPar.baseline) std::cout << " (" << i++ << ") baseline" << std::endl;
    if (fPar.height) std::cout << " (" << i++ << ") height" << std::endl;
    if (fPar.eventCounter) std::cout << " (" << i++ << ") eventCounter" << std::endl;
    // if (fPar.eventCounterPSD) std::cout << " (" << i++ << ") eventCounterPSD" << std::endl;
    // if (fPar.psdValue) std::cout << " (" << ++i << ") psdValue" << std::endl;
    if ((fPar.qShort) && (fPar.baseline)) std::cout << " (" << i++ << ") qShortBaseline" << std::endl;
    if ((fPar.qLong) && (fPar.baseline)) std::cout << " (" << i++ << ") qLongBaseline" << std::endl;
    
    std::string val;
    std::cin >> val;
    for (int k = 0; k < val.length(); k++) {
        std::string tmp(1, val[k]);
        int f = 0;
        if (tmp == std::to_string(f++)) break;
        if (fPar.qShort) if (tmp == std::to_string(f++)) {fParPlot.qShort = true; ConfigParameter("qShort");}
        if (fPar.qLong) if (tmp == std::to_string(f++)) {fParPlot.qLong = true; ConfigParameter("qLong");}
        if (fPar.cfd_y1) if (tmp == std::to_string(f++)) {fParPlot.cfd_y1 = true; ConfigParameter("cfd_y1");}
        if (fPar.cfd_y2) if (tmp == std::to_string(f++)) {fParPlot.cfd_y2 = true; ConfigParameter("cfd_y2");}
        if (fPar.baseline) if (tmp == std::to_string(f++)) {fParPlot.baseline = true; ConfigParameter("baseline");}
        if (fPar.height) if (tmp == std::to_string(f++)) {fParPlot.height = true; ConfigParameter("height");}
        if (fPar.eventCounter) if (tmp == std::to_string(f++)) {fParPlot.eventCounter = true; ConfigParameter("eventCounter");}
        // if (fPar.eventCounterPSD) if (tmp == std::to_string(f++)) {fParPlot.eventCounterPSD = true; ConfigParameter("eventCounterPSD");}
        // if (fPar.psdValue) if (tmp == std::to_string(f++)) {fParPlot.psdValue = true; ConfigParameter("psdValue");}
        if ((fPar.qShort) && (fPar.baseline)) if (tmp == std::to_string(f++)) {fParPlot.qShortBaseline = true; ConfigParameter("qShBase");}
        if ((fPar.qLong) && (fPar.baseline)) if (tmp == std::to_string(f++)) {fParPlot.qLongBaseline = true; ConfigParameter("qLgBase");}
    }
}

void Plotter::HeadParameter(TString par) {
    std::cout << "Configure a plot for parameter " + par << std::endl;
}

void Plotter::ConfigParameter(TString par) {
    PlotParameters tmpPar;
    //HeadParameter(par);
    std::cout << "Configure a plot for parameter " + par << std::endl;
    // name.push_back(par);
    tmpPar.name = par;

    std::cout << "Enter number of bins" << std::endl;
    int tmpNbins;
    std::cin >> tmpNbins;
    // Nbins.push_back(tmpNbins);
    tmpPar.Nbins = tmpNbins;

    std::cout << "Enter min value of histogram" << std::endl;
    double tmpMin;
    std::cin >> tmpMin;
    // minVal.push_back(tmpMin);
    tmpPar.minVal = tmpMin;

    std::cout << "Enter max value of histogram" << std::endl;
    double tmpMax;
    std::cin >> tmpMax;
    // maxVal.push_back(tmpMax);
    tmpPar.maxVal = tmpMax;
    pltPar.push_back(tmpPar);
}

void Plotter::Write(Encoder event) {
    int i = 0;
    if (fParPlot.qShort) hist[i++]->Fill(event.qShort);
    if (fParPlot.qLong) hist[i++]->Fill(event.qLong);
    if (fParPlot.cfd_y1) hist[i++]->Fill(event.cfd_y1);
    if (fParPlot.cfd_y2) hist[i++]->Fill(event.cfd_y2);
    if (fParPlot.baseline) hist[i++]->Fill(event.baseline);
    if (fParPlot.height) hist[i++]->Fill(event.height);
    if (fParPlot.eventCounter) hist[i++]->Fill(event.eventCounter);
    // if (fParPlot.eventCounterPSD) hist[i++]->Fill(event.eventCounterPSD);
    // if (fParPlot.psdValue) hist[i++]->Fill(event.psdValue);
    if (fParPlot.qShortBaseline) hist[i++]->Fill(event.qShortBaseline);
    if (fParPlot.qLongBaseline) hist[i++]->Fill(event.qLongBaseline);
}

void Plotter::CreateHistograms() {
    int i = 0;
    if (fParPlot.qShort) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.qLong) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.cfd_y1) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.cfd_y2) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.baseline) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.height) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.eventCounter) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    // if (fParPlot.eventCounterPSD) {
    //     PlotParameters tmp = pltPar[i++];
    //     hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    // }
    // if (fParPlot.psdValue) {
    //     PlotParameters tmp = pltPar[i++];
    //     hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    // }
    if (fParPlot.qShortBaseline) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
    if (fParPlot.qLongBaseline) {
        PlotParameters tmp = pltPar[i++];
        hist.push_back(new TH1D(tmp.name, tmp.name, tmp.Nbins, tmp.minVal, tmp.maxVal));
    }
}

void Plotter::Plot() {
    for (int i = 0; i < pltPar.size(); i++) {
        PlotParameters tmp = pltPar[i];
        TCanvas* c = new TCanvas(tmp.name, "Canvas", 800, 600);
        hist[i]->Draw();
        hist[i]->Write(tmp.name);
        c->SaveAs(tmp.name+".png");
    }
}