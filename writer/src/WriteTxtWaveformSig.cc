#include "WriteTxtWaveformSig.hh"

WriteTxtWaveformSig::WriteTxtWaveformSig() {
}

WriteTxtWaveformSig::~WriteTxtWaveformSig() {
}

void WriteTxtWaveformSig::Write(WaveformSig aWave) {
    fFile << aWave.qShort << " ";
    fFile << aWave.qLong << " ";
    fFile << aWave.baseline << " ";
    fFile << std::endl;
}

void WriteTxtWaveformSig::CreateFile() {
    fFile.open(file);
    fFile << "qShort ";
    fFile << "qLong ";
    fFile << "baseline "; 
    fFile << std::endl;
}

void WriteTxtWaveformSig::CloseFile() {
    fFile.close();
}