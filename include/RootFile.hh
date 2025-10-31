#ifndef RootFile_hh
#define RootFile_hh 1

#include "TFile.h"

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

#endif