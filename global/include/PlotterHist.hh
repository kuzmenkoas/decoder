#pragma once

#include <string>

struct PlotterHist {
    std::string decoder;
    std::string parameter;
    int Nbins;
    int min;
    int max;
};