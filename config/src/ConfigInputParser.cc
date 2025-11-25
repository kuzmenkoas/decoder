#include "ConfigInputParser.hh"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>

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

ConfigInputParser::~ConfigInputParser() {
}

void ConfigInputParser::SetArgc(int argc, char* argv[]) {
    fArgc = argc;
    if (argc == 3) {
        fName[0] = argv[1];
        fName[1] = argv[2];
    }
    DefineFileType();
    DefineOutputFileName();
}

void ConfigInputParser::Parse() {
    // create a configuration struct for output format
    outputConfig = new OutputConfig();

    // start a console user input for output format
    SaveFormat();
    
    if ((fFileType == DecoderType::BothType) || (fFileType == DecoderType::PSDType)) {
        // start a console user input for decode parameters
        Parameters();
    }
    // start a console user input for reversing
    if (((encoder.qShort || encoder.qLong || encoder.baseline) && fFileType == DecoderType::PSDType) || fFileType == DecoderType::WaveformType) Reverse();

    if (fFileType == DecoderType::WaveformType || fFileType == DecoderType::BothType) {
        BaselineNumber();
        ShortNumber();
        LongNumber();
        WaveformNumber();
    }
    Plots();
}

// no protection from user input
void ConfigInputParser::SaveFormat() {
    std::cout << "\n\n\nChoose format to save" << std::endl;
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
    std::cout << "\n\n\nWhat is encode in binary PSD file.\n";
    std::cout << "Choose everything that is stored in bin file\n";
    std::cout<< "(decoder will not be able to work correctly if this parameters will be incorrect)!\n";
    std::cout << "For multiple write as 123 - for qShort, qLong and cfd_y1.\n If in binary file stored all parameters choose 0 (ALL):\n";
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
    std::cout << "\n\n\nReverse integral?" << std::endl;
    std::cout << " (1) Yes" << std::endl;
    std::cout << " (2) Not" << std::endl;
    int val;
    std::cin >> val;
    if (val == 1) encoder.reverse = true;
}

void ConfigInputParser::DefineFileType() {
    if (fArgc != 3) {
        std::cout << "\n\n\nWhat file is it?" << std::endl;
        std::cout << " (1) PSD" << std::endl;
        std::cout << " (2) Waveform" << std::endl;

        int i = 0;
        std::cin >> i;
        if (i == 1) fFileType = DecoderType::PSDType;
        if (i == 2) fFileType = DecoderType::WaveformType;
    } else fFileType = DecoderType::BothType;
}

void ConfigInputParser::DefineOutputFileName() {
    std::string name = fName[0];
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(0, name.find_first_of("."));
    fOutputFileName = name;
}

void ConfigInputParser::WaveformNumber() {
    if (!(fFileType == DecoderType::WaveformType)) {
        // std::ifstream filePSD(fName[0], std::ios::binary | std::ios::ate);
        // std::ifstream fileWave(fName[1], std::ios::binary | std::ios::ate);
        int bytes = 0;
        int i = 0;
        Encoder size;
        if (encoder.qShort) {bytes += sizeof(size.qShort); i++;}
        if (encoder.qLong) {bytes += sizeof(size.qLong); i++;}
        if (encoder.cfd_y1) {bytes += sizeof(size.cfd_y1); i++;}
        if (encoder.cfd_y2) {bytes += sizeof(size.cfd_y2); i++;}
        if (encoder.baseline) {bytes += sizeof(size.baseline); i++;}
        if (encoder.height) {bytes += sizeof(size.height); i++;}
        if (encoder.eventCounter) {bytes += sizeof(size.eventCounter); i++;}
        if (encoder.eventCounterPSD) {bytes += sizeof(size.eventCounterPSD); i++;}
        if (encoder.psdValue) {bytes += sizeof(size.psdValue); i++;}
        bytes += 2+2*i;
        fEvents = std::filesystem::file_size(fName[0])/bytes;
        fWavePoints = std::filesystem::file_size(fName[1])/(fEvents*2);
    } else {
        std::cout << "\n\n\nThe number of waveform points?" << std::endl;
        std::cin >> fWavePoints;
    }
}

void ConfigInputParser::ShortNumber() {
    std::cout << "\n\n\nThe number of qShort points?" << std::endl;
    std::cin >> fShortPoints;
}

void ConfigInputParser::LongNumber() {
    std::cout << "\n\n\nThe number of qLong points?" << std::endl;
    std::cin >> fLongPoints;
}

void ConfigInputParser::BaselineNumber() {
    std::cout << "\n\n\nThe number of baseline points?" << std::endl;
    std::cin >> fBaselinePoints;
}

void ConfigInputParser::Plots() {
    if (fFileType == DecoderType::PSDType || fFileType == DecoderType::BothType) {
        std::cout << "\n\n\nChoose parameter to plot (multiply input, example: 123 for 3 parameters to plot)" << std::endl;
        int i = 0;
        std::cout << " (" << i++ << ") exit" << std::endl;
        if (encoder.qShort) std::cout << " (" << i++ << ") qShort" << std::endl;
        if (encoder.qLong) std::cout << " (" << i++ << ") qLong" << std::endl;
        if (encoder.cfd_y1) std::cout << " (" << i++ << ") cfd_y1" << std::endl;
        if (encoder.cfd_y2) std::cout << " (" << i++ << ") cfd_y2" << std::endl;
        if (encoder.baseline) std::cout << " (" << i++ << ") baseline" << std::endl;
        if (encoder.height) std::cout << " (" << i++ << ") height" << std::endl;
        if (encoder.eventCounter) std::cout << " (" << i++ << ") eventCounter" << std::endl;
        if (encoder.eventCounterPSD) std::cout << " (" << i++ << ") eventCounterPSD" << std::endl;
        if (encoder.psdValue) std::cout << " (" << ++i << ") psdValue" << std::endl;

        std::string val;
        std::cin >> val;
        for (int k = 0; k < val.length(); k++) {
            std::string tmp(1, val[k]);
            int f = 0;
            if (tmp == std::to_string(f++)) break;
            if (encoder.qShort) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "qShort");
            if (encoder.qLong) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "qLong");
            if (encoder.cfd_y1) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "cfd_y1");
            if (encoder.cfd_y2) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "cfd_y2");
            if (encoder.baseline) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "baseline");
            if (encoder.height) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "height");
            if (encoder.eventCounter) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "eventCounter");
            if (encoder.eventCounterPSD) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "eventCounterPSD");
            if (encoder.psdValue) if (tmp == std::to_string(f++)) ConfigParameter("PSD", "psdValue");
        }
    }
}

void ConfigInputParser::ConfigParameter(TString decoder, TString par) {
    PlotterHist tmpPar;
    tmpPar.decoder = decoder;
    std::cout << "\n\n\nConfigure a plot from " + decoder + " data for parameter " + par << std::endl;
    tmpPar.parameter = par;

    std::cout << "\nEnter number of bins" << std::endl;
    int tmpNbins;
    std::cin >> tmpNbins;
    tmpPar.Nbins = tmpNbins;

    std::cout << "\nEnter min value of histogram" << std::endl;
    double tmpMin;
    std::cin >> tmpMin;
    tmpPar.min = tmpMin;

    std::cout << "\nEnter max value of histogram" << std::endl;
    double tmpMax;
    std::cin >> tmpMax;
    tmpPar.max = tmpMax;
    fHist.push_back(tmpPar);
}