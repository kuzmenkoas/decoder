#include "WriteRootWaveformSig.hh"
#include <iostream>
#include "ConfigParserFactory.hh"

WriteRootWaveformSig::WriteRootWaveformSig() {
}

WriteRootWaveformSig::~WriteRootWaveformSig() {
    delete fTree;
}

void WriteRootWaveformSig::Write(WaveformSig aWave) {
    fWave = aWave;
    fTree->Fill();
}

void WriteRootWaveformSig::CreateFile() {
    EncoderParameters fPar = ConfigParserFactory::Instance()->BuildParser()->GetEncoderParametersWaveform();
    RootFile* fRootFile = RootFile::Instance();
    TFile* fFile = fRootFile->GetFile();
    fTree = new TTree("signal", "signal");

    if (fPar.qShort) fTree->Branch("qShort", &fWave.qShort);
    if (fPar.qLong) fTree->Branch("qLong", &fWave.qLong);
    if (fPar.baseline) fTree->Branch("baseline", &fWave.baseline);
}

void WriteRootWaveformSig::CloseFile() {
    TFile* fFile = RootFile::Instance()->GetFile();
    fTree->Write();
}