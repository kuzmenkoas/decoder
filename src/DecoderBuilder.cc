#include "DecoderBuilder.hh"

DecoderBuilder::DecoderBuilder(int argc, char* argv[]) {
    if (argc == 3) {
        DecoderFactory::Instance()->BuildDecoder(argv[1], DecoderType::PSD)->Touch();
        DecoderFactory::Instance()->BuildDecoder(argv[2], DecoderType::Waveform)->Touch();
    } else if (argc == 2) {
        DecoderFactory::Instance()->BuildDecoder(argv[1], DefineType())->Touch();
    }
}

DecoderBuilder::~DecoderBuilder() {
}

DecoderType DecoderBuilder::DefineType() {
    std::cout << "What file is it?" << std::endl;
    std::cout << " (1) PSD" << std::endl;
    std::cout << " (2) Waveform" << std::endl;

    DecoderType aType;
    int i = 0;
    std::cin >> i;
    if (i == 1) aType = DecoderType::PSD;
    if (i == 2) aType = DecoderType::Waveform;
    // no protection TODO
    return aType;
}