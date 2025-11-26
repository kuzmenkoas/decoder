#include "RootFile.hh"
#include "TString.h"

RootFile* RootFile::fRootFile = 0;

RootFile* RootFile::Instance() {
    if (fRootFile == 0) {
        fRootFile = new RootFile;
    }
    return fRootFile;
}

RootFile::RootFile() {
    std::string tmp = ConfigParserFactory::Instance()->BuildParser()->GetOutputFileName() + ".root";
    TString fFileName(tmp.c_str());
    fFile = new TFile(fFileName, "RECREATE");
}

RootFile::~RootFile() {
}