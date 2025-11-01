#include "WriteTxtWaveform.hh"

WriteTxtWaveform::WriteTxtWaveform() {
}

WriteTxtWaveform::~WriteTxtWaveform() {
}

void WriteTxtWaveform::Write(Waveform aWave) {
    fFile << aWave.i << " " << fFile.wave << std::endl;
}

void WriteTxtWaveform::CreateFile() {
    fFile.open(file);
    fFile << "entry" << " " << "wave" << std::endl;
}

void WriteTxtWaveform::CloseFile() {
    fFile.close();
}