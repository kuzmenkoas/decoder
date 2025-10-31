#ifndef ConfigParser_hh
#define ConfigParser_hh 1

#include <string>
#include <fstream>
#include <iostream>
#include "OutputConfig.hh"

// OLD FILE (IS NOT USED)
// Parser from config file
class ConfigParser {
public:
    static ConfigParser* Instance();
    void ParseFile(std::string fileName);
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};

private:
    ConfigParser();
    ~ConfigParser();
    static ConfigParser* fCfgParser;
    std::string fFileName;
    
    std::ifstream OpenFile();
    void ReadOutput(std::string key = "Output");
    void ReadEncoder(std::string key = "Data");
    OutputConfig* outputConfig = nullptr;
    EncoderParameters encoder;
};

#endif