#ifndef DecoderBuilder_hh
#define DecoderBuilder_hh 1

#include "DecoderFactory.hh"

class DecoderBuilder {
public:
    DecoderBuilder(int argc, char* argv[]);
    ~DecoderBuilder();
private:
    DecoderType DefineType();
};

#endif