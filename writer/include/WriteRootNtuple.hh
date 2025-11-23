#pragma once

#include "Writer.hh"
#include "TTree.h"
#include "TFile.h"
#include <iostream>
#include "RootFile.hh"

// class to save output as root file in tree
class WriteRootNtuple : public Writer {
public:
    WriteRootNtuple();
    ~WriteRootNtuple();

    // write an event to file
    void Write(Encoder encoder, EncoderParameters par);
    // create output file root
    void CreateFile(EncoderParameters par);
    // close this file
    void CloseFile();
private:
    // TFile* fFile = nullptr;
    Encoder event;
    TTree* fTree;

    // output file name
    TString file = "output.root";
};