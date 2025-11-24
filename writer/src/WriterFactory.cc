#include "WriterFactory.hh"

WriterFactory* WriterFactory::fWriterFactory = 0;

WriterFactory* WriterFactory::Instance() {
    if (fWriterFactory == 0) {
        fWriterFactory = new WriterFactory;
    }
    return fWriterFactory;
}

WriterFactory::WriterFactory() {
}

WriterFactory::~WriterFactory() {
    delete fWriterFactory;
}

Writer* WriterFactory::BuildWriter(WriterType aType) {
    Writer* aWriter = nullptr;

    switch (aType) {
    case WriterType::RootNtuple:
        aWriter = new WriteRootNtuple();
        break;
    case WriterType::TxtNtuple:
        aWriter = new WriteTxtNtuple();
        break;
    case WriterType::RootWaveform:
        aWriter = new WriteRootWaveform();
        break;
    case WriterType::TxtWaveform:
        aWriter = new WriteTxtWaveform();
        break;
    case WriterType::RootWaveformSig:
        aWriter = new WriteRootWaveformSig();
        break;
    case WriterType::TxtWaveformSig:
        aWriter = new WriteTxtWaveformSig();
        break;
    }
    return aWriter;
}