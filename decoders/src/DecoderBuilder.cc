#include "DecoderBuilder.hh"

DecoderBuilder::DecoderBuilder(int argc, char* argv[]) {
    if (argc == 3) {
        DecoderFactory::Instance()->BuildDecoder(argv[1], DecoderType::PSDType)->Touch();
        DecoderFactory::Instance()->BuildDecoder(argv[2], DecoderType::WaveformType)->Touch();
    } else if (argc == 2) {
        DecoderFactory::Instance()->BuildDecoder(argv[1], ConfigParserFactory::Instance()->BuildParser()->GetFileType())->Touch();
    }
}

DecoderBuilder::~DecoderBuilder() {
}
