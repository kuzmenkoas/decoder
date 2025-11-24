#include "ConfigFileParser.hh"

ConfigFileParser* ConfigFileParser::fCfgParser = 0;

// singleton pattern instance
ConfigFileParser* ConfigFileParser::Instance() {
    if (fCfgParser == 0) {
        fCfgParser = new ConfigFileParser;
    }
    return fCfgParser;
}

ConfigFileParser::ConfigFileParser() {
    // create an output struct
    outputConfig = new OutputConfig();
}

ConfigFileParser::~ConfigFileParser() {
}

void ConfigFileParser::SetArgc(int argc, char* argv[]) {
    fArgc = argc;
    fName[0] = argv[1];
    if (argc == 3) fName[1] = argv[2];
    DefineFileType();
    DefineOutputFileName();
}

void ConfigFileParser::DefineFileType() {
    if (fArgc != 3) {
        std::ifstream file = OpenFile();
        std::string CurStr;
        std::string keyPsd = "DataPSD";
        std::string keyWave = "DataWaveform";
        while(getline (file,CurStr)){
            if (CurStr.compare(0, keyPsd.size(), keyPsd) == 0) {fFileType = DecoderType::PSDType; break;}
            if (CurStr.compare(0, keyWave.size(), keyWave) == 0) {fFileType = DecoderType::WaveformType; break;}
        }
    } else fFileType = DecoderType::BothType;
}

void ConfigFileParser::DefineOutputFileName() {
    std::string name = fName[0];
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(name.find_first_of("_")+1);
    name = name.substr(0, name.find_first_of("."));
    fOutputFileName = name;
}

void ConfigFileParser::WaveformNumber() {
    if (!(fFileType == DecoderType::WaveformType)) {
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

void ConfigFileParser::Parse() {
    ReadOutput();
    if ((fFileType == DecoderType::BothType) || (fFileType == DecoderType::PSDType)) {
        // start a file parser for decode parameters
        ReadEncoder();
    }
    // start a file parser for reversing
    // if (((encoder.qShort || encoder.qLong || encoder.baseline) && fFileType == DecoderType::PSDType) || fFileType == DecoderType::WaveformType) Reverse();

    if (fFileType == DecoderType::WaveformType || fFileType == DecoderType::BothType) {
        ReadWaveformData();
        ReadWaveformConfig();
        WaveformNumber();
    }
}

std::ifstream ConfigFileParser::OpenFile() {
    std::ifstream file(fFileName);
    try {
        if (!file.is_open()) throw std::runtime_error("Cannot open config file " + fFileName);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
        abort();
    }
    return file;
}

void ConfigFileParser::ReadOutput(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("DataPSD") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr.substr(found+1);

                        if (CurStr == "RootNtuple") outputConfig->SetRootNtuple();
                        if (CurStr == "TxtNtuple") outputConfig->SetTxtNtuple();
                    }
                }
            }
        }
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      abort();
    }
}

void ConfigFileParser::ReadEncoder(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("DataWaveform") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr.substr(found+1);
                        
                        if (CurStr == "qShort") encoder.qShort = true;
                        if (CurStr == "qLong") encoder.qLong = true;
                        if (CurStr == "cfd_y1") encoder.cfd_y1 = true;
                        if (CurStr == "cfd_y2") encoder.cfd_y2 = true;
                        if (CurStr == "baseline") encoder.baseline = true;
                        if (CurStr == "height") encoder.height = true;
                        if (CurStr == "eventCounter") encoder.eventCounter = true;
                        if (CurStr == "eventCounterPSD") encoder.eventCounterPSD = true;
                        if (CurStr == "psdValue") encoder.psdValue = true;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      abort();
    }
}

void ConfigFileParser::ReadWaveformData(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("WaveformConfig") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr.substr(found+1);

                        if (CurStr == "qShort") encoderWaveform.qShort = true;
                        if (CurStr == "qLong") encoderWaveform.qLong = true;
                        if (CurStr == "baseline") encoderWaveform.baseline = true;
                        if (CurStr == "entries") encoderWaveform.entries = true;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      abort();
    }
}

void ConfigFileParser::ReadWaveformConfig(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("WaveformConfig") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr.substr(found+1);

                        std::string name = CurStr.substr(0, CurStr.find_first_of(" "));
                        std::string tmp = CurStr.substr(CurStr.find_first_of(" ")+1);
                        std::string value = tmp.substr(tmp.find_first_of(" ")+1);
                        
                        if (name == "baseline") fBaselinePoints = std::stoi(value);
                        if (name == "qShort") fShortPoints = std::stoi(value);
                        if (name == "qLong") fLongPoints = std::stoi(value);
                    }
                }
            }
        }
    } catch (const std::exception& e) {
      std::cerr << "Exception: " << e.what() << std::endl;
      abort();
    }
}