#include "WriteTxtWaveform.hh"

WriteTxtWaveform::WriteTxtWaveform() {
}

WriteTxtWaveform::~WriteTxtWaveform() {
}

void WriteTxtWaveform::Write(Waveform aWave) {
    fFile << aWave.id << " " << aWave.t << " " << aWave.wave << std::endl;
}

void WriteTxtWaveform::CreateFile() {
    fFile.open(file);
    fFile << "id_entry time wave" << std::endl;
}

void WriteTxtWaveform::CloseFile() {
    fFile.close();
}