#pragma once

#include "Writer.hh"
#include <fstream>
#include "Waveform.hh"

class WriteTxtWaveform : public Writer {
public:
    WriteTxtWaveform();
    ~WriteTxtWaveform();

    void Write(Waveform aWave);
    void CreateFile();
    void CloseFile();
private:
    Waveform event;
    std::ofstream fFile;
    std::string file = "waveform.txt";
};