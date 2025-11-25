#pragma once

#include <string>
#include "TString.h"

struct PlotterHist {
    TString decoder;
    TString parameter;
    int Nbins;
    double min;
    double max;
};