#include "ConfigInputParser.hh"
#include <iostream>
#include <string>

ConfigInputParser* ConfigInputParser::fCfgParser = 0;

// singleton pattern instance
ConfigInputParser* ConfigInputParser::Instance() {
    if (fCfgParser == 0) {
        fCfgParser = new ConfigInputParser;
    }
    return fCfgParser;
}

ConfigInputParser::ConfigInputParser() {
}

void ConfigInputParser::StartParser() {
    // create a configuration struct for output format
    outputConfig = new OutputConfig();

    // start a console user input for output format
    SaveFormat();
    
    if ((fFileType == DecoderType::BothType) || (fFileType == DecoderType::PSDType)) {
        // start a console user input for decode parameters
        Parameters();

        // start a console user input for reversing
        if ((encoder.qShort || encoder.qLong) && encoder.baseline) Reverse();
    }

    if (fFileType == DecoderType::WaveformType || fFileType == DecoderType::BothType) WaveformNumber();
}

ConfigInputParser::~ConfigInputParser() {
}

// no protection from user input
void ConfigInputParser::SaveFormat() {
    std::cout << "Choose format to save" << std::endl;
    std::cout << " (1) Root" << std::endl;
    std::cout << " (2) Txt" << std::endl;
    std::cout << " (3) Root and Txt" << std::endl;
    int i = 0;
    std::cin >> i;
    if ((i == 1) || (i == 3)) outputConfig->SetRootNtuple();
    if ((i == 2) || (i == 3)) outputConfig->SetTxtNtuple();
    if ((i < 1) || (i > 3)) std::cerr << "No such as save format!";
}

// no protection from user input
void ConfigInputParser::Parameters() {
    std::cout << "Choose saved parameters to decode (for multiple write as 123 - for qShort, qLong and cfd_y1):" << std::endl;
    std::cout << " (1) qShort" << std::endl;
    std::cout << " (2) qLong" << std::endl;
    std::cout << " (3) cfd_y1" << std::endl;
    std::cout << " (4) cfd_y2" << std::endl;
    std::cout << " (5) baseline" << std::endl;
    std::cout << " (6) height" << std::endl;
    std::cout << " (7) eventCounter" << std::endl;
    std::cout << " (8) eventCounterPSD" << std::endl;
    std::cout << " (9) psdValue" << std::endl;
    std::cout << " (0) ALL" << std::endl;
    std::string i;
    std::cin >> i;
    for (int k = 0; k < i.length(); k++) {
        char tmp = i[k];
        if (tmp == '1' || tmp == '0') encoder.qShort = true;
        if (tmp == '2' || tmp == '0') encoder.qLong = true;
        if (tmp == '3' || tmp == '0') encoder.cfd_y1 = true;
        if (tmp == '4' || tmp == '0') encoder.cfd_y2 = true;
        if (tmp == '5' || tmp == '0') encoder.baseline = true;
        if (tmp == '6' || tmp == '0') encoder.height = true;
        if (tmp == '7' || tmp == '0') encoder.eventCounter = true;
        if (tmp == '8' || tmp == '0') encoder.eventCounterPSD = true;
        if (tmp == '9' || tmp == '0') encoder.psdValue = true;
    }
}

void ConfigInputParser::Reverse() {
    std::cout << "Reverse integral?" << std::endl;
    std::cout << " (1) Yes" << std::endl;
    std::cout << " (2) Not" << std::endl;
    int val;
    std::cin >> val;
    if (val == 1) encoder.reverse = true;
}

void ConfigInputParser::DefineFileType() {
    if (fArgc != 3) {
        std::cout << "What file is it?" << std::endl;
        std::cout << " (1) PSD" << std::endl;
        std::cout << " (2) Waveform" << std::endl;

        int i = 0;
        std::cin >> i;
        if (i == 1) fFileType = DecoderType::PSDType;
        if (i == 2) fFileType = DecoderType::WaveformType;
    } else fFileType = DecoderType::BothType;
}

void ConfigInputParser::WaveformNumber() {
    std::cout << "The number of waveform points?" << std::endl;
    std::cin >> fWavePoints;
}

void ConfigInputParser::ShortNumber() {
    std::cout << "The number of qShort points?" << std::endl;
    std::cin >> fShortPoints;
}

void ConfigInputParser::LongNumber() {
    std::cout << "The number of qLong points?" << std::endl;
    std::cin >> fLongPoints;
}