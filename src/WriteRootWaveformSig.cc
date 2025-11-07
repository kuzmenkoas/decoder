#include "WriteRootWaveformSig.hh"

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
    RootFile* fRootFile = RootFile::Instance();
    TFile* fFile = fRootFile->GetFile();
    fTree = new TTree("signal", "signal");

    fTree->Branch("baseline", &fWave.baseline);
    fTree->Branch("qShort", &fWave.qShort);
    fTree->Branch("qLong", &fWave.qLong);
}

void WriteRootWaveformSig::CloseFile() {
    TFile* fFile = RootFile::Instance()->GetFile();
    fTree->Write();
}