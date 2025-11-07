#include "WriteRootWaveform.hh"
#include <iostream>

WriteRootWaveform::WriteRootWaveform() {
}

WriteRootWaveform::~WriteRootWaveform() {
    delete fTree;
}

void WriteRootWaveform::Write(Waveform aWave) {
    fWave = aWave;
    fTree->Fill();
}

void WriteRootWaveform::CreateFile() {
    RootFile* fRootFile = RootFile::Instance();
    TFile* fFile = fRootFile->GetFile();
    fTree = new TTree("waveformnt", "waveformnt");

    fTree->Branch("id", &fWave.id);
    fTree->Branch("t", &fWave.t);
    fTree->Branch("wave", &fWave.wave);
}

void WriteRootWaveform::CloseFile() {
    TFile* fFile = RootFile::Instance()->GetFile();
    // TODO
    fTree->Write();
}