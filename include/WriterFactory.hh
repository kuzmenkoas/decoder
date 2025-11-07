#ifndef WriterFactory_hh
#define WriterFactory_hh 1

#include "Writer.hh"
#include "WriteRootNtuple.hh"
#include "WriteTxtNtuple.hh"
#include "WriteRootWaveform.hh"
#include "WriteTxtWaveform.hh"

enum WriterType {
    RootNtuple,
    TxtNtuple,
    RootWaveform,
    TxtWaveform
};

// a factory pattern + singleton pattern
class WriterFactory {
public:
    static WriterFactory* Instance();
    // create an writer object (inheritance from interface Writer)
    Writer* BuildWriter(WriterType aType);
private:
    static WriterFactory* fWriterFactory;
    WriterFactory();
    ~WriterFactory();
};

#endif