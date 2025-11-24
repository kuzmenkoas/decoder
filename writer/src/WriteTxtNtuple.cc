#include "WriteTxtNtuple.hh"

WriteTxtNtuple::WriteTxtNtuple() {
}

WriteTxtNtuple::~WriteTxtNtuple() {
}

// write an event to file
void WriteTxtNtuple::Write(Encoder encoder, EncoderParameters par) {
    if (par.qShort) fFile << encoder.qShort << " ";
    if (par.qLong) fFile << encoder.qLong << " ";
    if (par.cfd_y1) fFile << encoder.cfd_y1 << " ";
    if (par.cfd_y2) fFile << encoder.cfd_y2 << " ";
    if (par.baseline) fFile << encoder.baseline << " ";
    if (par.height) fFile << encoder.height << " ";
    if (par.eventCounter) fFile << encoder.eventCounter << " ";
    if (par.eventCounterPSD) fFile << encoder.eventCounterPSD << " ";
    if (par.psdValue) fFile << encoder.psdValue << " ";
    fFile << std::endl;
}

// create a txt file and write a title (used parameters to encode)
void WriteTxtNtuple::CreateFile(EncoderParameters par) {
    fFile.open(file);

    if (par.qShort) fFile << "qShort" << " ";
    if (par.qLong) fFile << "qLong" << " ";
    if (par.cfd_y1) fFile << "cfd_y1" << " ";
    if (par.cfd_y2) fFile << "cfd_y2" << " ";
    if (par.baseline) fFile << "baseline" << " ";
    if (par.height) fFile << "height" << " ";
    if (par.eventCounter) fFile << "eventCounter" << " ";
    if (par.eventCounterPSD) fFile << "eventCounterPSD" << " ";
    if (par.psdValue) fFile << "psdValue" << " ";    
    fFile << std::endl;
}

// close file
void WriteTxtNtuple::CloseFile() {
    fFile.close();
}