#include "DecoderWaveform.hh"

DecoderWaveform::DecoderWaveform(TString file) : fFileName(file) {
    Output outWriters = ConfigInputParser::Instance()->GetOutputConfig()->GetOutput();
    if (outWriters.RootNtuple) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::RootWaveform));
    if (outWriters.TxtNtuple) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::TxtWaveform));
}

DecoderWaveform::~DecoderWaveform() {
}

void DecoderWaveform::Touch() {
    Decode();
}

void DecoderWaveform::Decode() {
    std::ifstream file(fFileName, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::beg);

    // Writer* aWriter = WriterFactory::Instance()->BuildWriter(WriterType::RootWaveform);
    PlotterWaveform* aPlt = new PlotterWaveform();
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CreateFile();
    }
    // aWriter->CreateFile();

    int i = 0;
    while (true) {
        Waveform aWave;
        file.read(reinterpret_cast<char*>(&aWave.wave), sizeof(aWave.wave));
        aWave.i = i++;
        if (file.eof()) break;
        // aWriter->Write(aWave);
        for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
            (*it)->Write(aWave);
        }
        aPlt->Write(aWave);
        // csv gonna be too long and unreadable
    }
    file.close();
    // aWriter->CloseFile();
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CloseFile();
    }
    aPlt->Plot();
}