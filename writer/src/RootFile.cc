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
    TString fFileName = ConfigParserFactory::Instance()->BuildParser()->GetOutputFileName() + ".root";
    fFile = new TFile(fFileName, "RECREATE");
}

RootFile::~RootFile() {
}