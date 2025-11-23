#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "OutputConfig.hh"
#include "ConfigParser.hh"

// OLD FILE (IS NOT USED)
// Parser from config file
class ConfigFileParser{
public:
    static ConfigFileParser* Instance();
    void ParseFile(std::string fileName);
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};

private:
    ConfigFileParser();
    ~ConfigFileParser();
    static ConfigFileParser* fCfgParser;
    std::string fFileName;
    
    std::ifstream OpenFile();
    void ReadOutput(std::string key = "Output");
    void ReadEncoder(std::string key = "Data");
    OutputConfig* outputConfig = nullptr;
    EncoderParameters encoder;
};