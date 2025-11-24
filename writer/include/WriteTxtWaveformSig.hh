#pragma once

#include "Writer.hh"
#include <fstream>
#include "Waveform.hh"
#include "ConfigParserFactory.hh"

class WriteTxtWaveformSig : public Writer {
public:
    WriteTxtWaveformSig();
    ~WriteTxtWaveformSig();

    void Write(WaveformSig aWave);
    void CreateFile();
    void CloseFile();
private:
    WaveformSig event;
    std::ofstream fFile;
    std::string file = "waveformSig.txt";
};