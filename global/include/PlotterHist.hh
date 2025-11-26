#pragma once

#include <string>
#include "TString.h"

struct PlotterHist {
    std::string decoder;
    std::string parameter;
    int Nbins;
    double min;
    double max;
};