#include "WriteRootNtuple.hh"

WriteRootNtuple::WriteRootNtuple() {
}

WriteRootNtuple::~WriteRootNtuple() {
    delete fTree;
    // delete fFile;
}

// write an event to file
void WriteRootNtuple::Write(Encoder encoder, EncoderParameters par) {
    event = encoder;
    fTree->Fill();
}

// create a root file with Tree decoder and add branches (used parameters)
void WriteRootNtuple::CreateFile(EncoderParameters par) {
    TFile* fFile = RootFile::Instance()->GetFile();
    fTree = new TTree("decoder", "decoder");

    if (par.qShort) fTree->Branch("qShort", &event.qShort);
    if (par.qLong) fTree->Branch("qLong", &event.qLong);
    if (par.cfd_y1) fTree->Branch("cfd_y1", &event.cfd_y1);
    if (par.cfd_y2) fTree->Branch("cfd_y2", &event.cfd_y2);
    if (par.baseline) fTree->Branch("baseline", &event.baseline);
    if (par.height) fTree->Branch("height", &event.height);
    if (par.eventCounter) fTree->Branch("eventCounter", &event.eventCounter);
    if (par.eventCounterPSD) fTree->Branch("eventCounterPSD", &event.eventCounterPSD);
    if (par.psdValue) fTree->Branch("psdValue", &event.psdValue);
    // if (par.qShort && par.baseline) fTree->Branch("qShortBaseline", &event.qShortBaseline);
    // if (par.qLong && par.baseline) fTree->Branch("qLongBaseline", &event.qLongBaseline);
}

// close file
void WriteRootNtuple::CloseFile() {
    TFile* fFile = RootFile::Instance()->GetFile();
    fTree->Write();
}