#pragma once

#include "Writer.hh"
#include "TTree.h"
#include "RootFile.hh"
#include "Waveform.hh"

class WriteRootWaveformSig : public Writer {
public:
    WriteRootWaveformSig();
    ~WriteRootWaveformSig();

    void Write(WaveformSig aWave);
    void CreateFile();
    void CloseFile();
private:
    TTree* fTree;
    WaveformSig fWave;
};