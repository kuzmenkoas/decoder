#pragma once

#include "TFile.h"
#include "ConfigParserFactory.hh"

class RootFile {
public:
    static RootFile* Instance();
    TFile* GetFile() {return fFile;};
    void CloseFile() {fFile->Close();};
private:
    static RootFile* fRootFile;
    RootFile();
    ~RootFile();
    TFile* fFile = nullptr;
};