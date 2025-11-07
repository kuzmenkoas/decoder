#include "RootFile.hh"
#include <iostream>

RootFile* RootFile::fRootFile = 0;

RootFile* RootFile::Instance() {
    if (fRootFile == 0) {
        fRootFile = new RootFile;
    }
    return fRootFile;
}

RootFile::RootFile() {
    fFile = new TFile("output.root", "RECREATE");
}

RootFile::~RootFile() {
}