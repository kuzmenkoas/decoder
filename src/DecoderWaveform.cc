#include "DecoderWaveform.hh"

DecoderWaveform::DecoderWaveform(TString file) : fFileName(file) {
}

DecoderWaveform::~DecoderWaveform() {
}

void DecoderWaveform::Touch() {
    Decode();
}

void DecoderWaveform::Decode() {
    std::ifstream file(fFileName, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::beg);

    Writer* aWriter = WriterFactory::Instance()->BuildWriter(WriterType::RootWaveform);
    PlotterWaveform* aPlt = new PlotterWaveform();
    aWriter->CreateFile();

    int i = 0;
    while (true) {
        Waveform aWave;
        file.read(reinterpret_cast<char*>(&aWave.wave), sizeof(aWave.wave));
        aWave.i = i++;
        if (file.eof()) break;
        aWriter->Write(aWave);
        aPlt->Write(aWave);
        // csv gonna be too long and unreadable
    }
    file.close();
    aWriter->CloseFile();
    aPlt->Plot();
}