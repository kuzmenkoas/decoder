#include "DecoderPSD.hh"
#include <fstream>

DecoderPSD::DecoderPSD(TString file) : fFileName(file), fPar(ConfigInputParser::Instance()->GetEncoderParameters()) {
    fPlotter = new Plotter(fPar);
    outWriters = ConfigInputParser::Instance()->GetOutputConfig()->GetOutput();
    if (outWriters.RootNtuple) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::RootNtuple));
    if (outWriters.TxtNtuple) fWriterVector.push_back(WriterFactory::Instance()->BuildWriter(WriterType::TxtNtuple));
}

DecoderPSD::~DecoderPSD() {
}

void DecoderPSD::Touch() {
    // decode and write as ntuple to root or txt or both
    Decode();
    // starts configuration of histograms if need and saves to root and png
    Plot();
}

// estimates parameters to encode
// need to understand how much unused bytes in raw
Int_t DecoderPSD::GetParametersNumber() {
    Int_t i = 0;
    if (fPar.qShort) i++;
    if (fPar.qLong) i++;
    if (fPar.cfd_y1) i++;
    if (fPar.cfd_y2) i++;
    if (fPar.baseline) i++;
    if (fPar.height) i++;
    if (fPar.eventCounter) i++;
    if (fPar.eventCounterPSD) i++;
    if (fPar.psdValue) i++;
    return i;
}

void DecoderPSD::Decode() {
    std::ifstream file(fFileName, std::ios::binary | std::ios::ate);
    file.seekg(0, std::ios::beg);
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CreateFile(fPar);
    }

    int reverseCoefficient = 1;
    if (fPar.reverse) reverseCoefficient = -1;

    int aShortPoint = ConfigInputParser::Instance()->GetShortNumber();
    int aLongPoint = ConfigInputParser::Instance()->GetLongNumber();
    while (true) {
        Encoder event;
        // Unused bytes (read and forget)
        const int id = 2+2*GetParametersNumber();
        char* tmp = new char[id];
        file.read(tmp, id);
        // Read a parameter to value (struct)
        // if saved parameter order has changes - change it there also 
        if (fPar.qShort) {
            file.read(reinterpret_cast<char*>(&event.qShort), sizeof(event.qShort));
            event.qShort *= reverseCoefficient;
        }
        if (fPar.qLong) {
            file.read(reinterpret_cast<char*>(&event.qLong), sizeof(event.qLong));
            event.qLong *= reverseCoefficient;
        }
        if (fPar.cfd_y1) file.read(reinterpret_cast<char*>(&event.cfd_y1), sizeof(event.cfd_y1));
        if (fPar.cfd_y2) file.read(reinterpret_cast<char*>(&event.cfd_y2), sizeof(event.cfd_y2));
        if (fPar.baseline) {
            file.read(reinterpret_cast<char*>(&event.baseline), sizeof(event.baseline));
            event.baseline *= reverseCoefficient;
        }
        if (fPar.height) file.read(reinterpret_cast<char*>(&event.height), sizeof(event.height));
        if (fPar.eventCounter) file.read(reinterpret_cast<char*>(&event.eventCounter), sizeof(event.eventCounter));
        if (fPar.eventCounterPSD) file.read(reinterpret_cast<char*>(&event.eventCounterPSD), sizeof(event.eventCounterPSD));
        if (fPar.psdValue) file.read(reinterpret_cast<char*>(&event.psdValue), sizeof(event.psdValue));
        if (fPar.qShort && fPar.baseline) event.qShortBaseline = event.qShort-aShortPoint*event.baseline;
        if (fPar.qLong && fPar.baseline) event.qLongBaseline = event.qLong-aLongPoint*event.baseline;
        if (file.eof()) break;

        // send to writer event
        for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
            (*it)->Write(event, fPar);
        }
        fPlotter->Write(event);
    }
    file.close();
    for (std::vector<Writer*>::iterator it = fWriterVector.begin(); it != fWriterVector.end(); it++) {
        (*it)->CloseFile();
    }
}