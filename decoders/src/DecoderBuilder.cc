#include "DecoderBuilder.hh"

DecoderBuilder::DecoderBuilder(int bin, int argc, char* argv[]) {
    int i = 1;
    if (bin != argc) i++;
    if (bin == 3) {
        DecoderFactory::Instance()->BuildDecoder(argv[i], DecoderType::PSDType)->Touch();
        DecoderFactory::Instance()->BuildDecoder(argv[++i], DecoderType::WaveformType)->Touch();
    } else if (bin == 2) {
        DecoderFactory::Instance()->BuildDecoder(argv[i], ConfigParserFactory::Instance()->BuildParser()->GetFileType())->Touch();
    }
}

DecoderBuilder::~DecoderBuilder() {
}
