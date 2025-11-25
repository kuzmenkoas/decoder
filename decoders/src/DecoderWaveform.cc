#include "DecoderWaveform.hh"

DecoderWaveform::DecoderWaveform(TString file) : fFileName(file), fPar(ConfigParserFactory::Instance()->BuildParser()->GetEncoderParametersWaveform()) {
    outWriters = ConfigParserFactory::Instance()->BuildParser()->GetOutputConfig()->GetOutput();
    int kk = 0;
    if (outWriters.RootNtuple) {
        fPlotter = Plotter::Instance();
        fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::RootWaveformSig));        
        if (fPar.entries) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::RootWaveform));
    }
    if (outWriters.TxtNtuple) {
        fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::TxtWaveformSig));
        if (fPar.entries) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::TxtWaveform));
    }
}

DecoderWaveform::~DecoderWaveform() {
}

void DecoderWaveform::Touch() {
    Decode();
    Output outWriters = ConfigParserFactory::Instance()->BuildParser()->GetOutputConfig()->GetOutput();
    // if (outWriters.RootNtuple) {
    //     Plot();
    // }
}

void DecoderWaveform::Decode() {
    std::ifstream file(fFileName, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::beg);

    PlotterWaveform* aPlt = new PlotterWaveform();
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CreateFile();
    }

    // EncoderParameters fPar = ConfigParserFactory::Instance()->BuildParser()->GetEncoderParameters();
    int reverseCoefficient = 1;
    if (fPar.reverse) reverseCoefficient = -1;

    int t = 0;
    int i = 0;
    int fWavePoint = ConfigParserFactory::Instance()->BuildParser()->GetWaveformNumber();
    int fBaselinePoint = ConfigParserFactory::Instance()->BuildParser()->GetBaselineNumber();
    int fShortPoint = ConfigParserFactory::Instance()->BuildParser()->GetShortNumber();
    int fLongPoint = ConfigParserFactory::Instance()->BuildParser()->GetLongNumber();
    
    int iID = 0;
    int iBase = 0;
    int baseline = 0;
    int qShort = 0;
    int qLong = 0;
    outWriters = ConfigParserFactory::Instance()->BuildParser()->GetOutputConfig()->GetOutput();
    while (true) {
        Waveform aWave;
        file.read(reinterpret_cast<char*>(&aWave.wave), sizeof(aWave.wave));
        aWave.id = i;
        aWave.t = t++;
        if (t >= fWavePoint) {
            t = 0;
            i++;
        }
        if (file.eof()) break;

        for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
            (*it)->Write(aWave);
        }
        aPlt->Write(aWave);
        // csv gonna be too long and unreadable

        // algorithm to get a signal from waveform
        if (outWriters.RootNtuple) {
            if (aWave.id == iID) {
                if (aWave.t < fBaselinePoint) {
                    baseline += aWave.wave;
                    iBase++;
                } else {
                    if (aWave.t < fBaselinePoint+fShortPoint) {
                        qShort += aWave.wave;
                        qLong += aWave.wave;
                    } else if (aWave.t < fBaselinePoint+fLongPoint) {
                        qLong += aWave.wave;
                    } else {
                        baseline /= iBase;
                        qShort -= fShortPoint*baseline;
                        qLong -= fLongPoint*baseline;
                        WaveformSig aWaveSig;
                        aWaveSig.baseline = reverseCoefficient*baseline;
                        aWaveSig.qShort = reverseCoefficient*qShort;
                        aWaveSig.qLong = reverseCoefficient*qLong;
                        
                        fWriterVector[0]->Write(aWaveSig);

                        if (outWriters.TxtNtuple && outWriters.RootNtuple && fPar.entries) {
                            fWriterVector[2]->Write(aWaveSig);
                        }
                        else if ((outWriters.TxtNtuple && outWriters.RootNtuple) && !fPar.entries) {
                            fWriterVector[1]->Write(aWaveSig);
                        }
                        fPlotter->Write(aWaveSig);
                        baseline = 0;
                        iBase = 0;
                        qShort = 0;
                        qLong = 0;

                        iID++;
                        continue;
                    }
                }
            }
        }
    }
    file.close();
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CloseFile();
    }
    aPlt->Plot();
}