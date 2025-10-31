#ifndef WriteRootWaveform_hh
#define WriteRootWaveform_hh 1

#include "Writer.hh"
#include "TTree.h"
#include "RootFile.hh"
#include "Waveform.hh"

class WriteRootWaveform : public Writer {
public:
    WriteRootWaveform();
    ~WriteRootWaveform();

    void Write(Waveform aWave);
    void CreateFile();
    void CloseFile();
private:
    TTree* fTree;
    Waveform fWave;
};

#endif