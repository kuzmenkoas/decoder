#include "ConfigParser.hh"

ConfigParser* ConfigParser::fCfgParser = 0;

// singleton pattern instance
ConfigParser* ConfigParser::Instance() {
    if (fCfgParser == 0) {
        fCfgParser = new ConfigParser;
    }
    return fCfgParser;
}

ConfigParser::ConfigParser() {
    // create an output struct
    outputConfig = new OutputConfig();
}

ConfigParser::~ConfigParser() {
}

void ConfigParser::ParseFile(std::string fileName) {
    fFileName = fileName;
    ReadOutput();
    ReadEncoder();
}

std::ifstream ConfigParser::OpenFile() {
    std::ifstream file(fFileName);
    try {
        if (!file.is_open()) throw std::runtime_error("Cannot open config file " + fFileName);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << '\n';
    }
    return file;
}

void ConfigParser::ReadOutput(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("Data") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr = CurStr.substr(found+1);

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

void ConfigParser::ReadEncoder(std::string key) {
    std::ifstream file = OpenFile();
    std::string CurStr;
    try {
        while(getline (file,CurStr)){
            if (CurStr.compare(0, key.size(), key) == 0) {
                while (getline (file, CurStr) && CurStr.compare("Data") !=0) {
                    if (CurStr.c_str()[0]=='+') {
                        size_t found = CurStr.find_first_of(" ");
                        CurStr = CurStr = CurStr.substr(found+1);
                        
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