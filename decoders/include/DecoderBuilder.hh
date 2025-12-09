#pragma once

#include "DecoderFactory.hh"
#include "ConfigInputParser.hh"
#include "ConfigParserFactory.hh"

class DecoderBuilder {
public:
    DecoderBuilder(int bin, int argc, char* argv[]);
    ~DecoderBuilder();
private:
};