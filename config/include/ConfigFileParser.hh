#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include "OutputConfig.hh"
#include "ConfigParser.hh"
#include <filesystem>

// Parser from config file
class ConfigFileParser : public ConfigParser{
public:
    static ConfigFileParser* Instance();
    void SetArgc(int argc, char* argv[]);
    void SetFileName(std::string name) {fFileName = name;};
    void Parse();
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};

    int GetEvents() {return fEvents;};
    int GetWaveformNumber() {return fWavePoints;};
    int GetBaselineNumber() {return fBaselinePoints;};
    int GetShortNumber() {return fShortPoints;};
    int GetLongNumber() {return fLongPoints;};

private:
    ConfigFileParser();
    ~ConfigFileParser();

    void DefineFileType();

    static ConfigFileParser* fCfgParser;
    std::string fName[2];
    std::string fFileName;
    
    std::ifstream OpenFile();
    void ReadOutput(std::string key = "Output");
    void ReadEncoder(std::string key = "DataPSD");
    void ReadWaveformData(std::string key = "DataWaveform");
    void ReadWaveformConfig(std::string key = "WaveformConfig");
    void WaveformNumber();
    OutputConfig* outputConfig = nullptr;
    EncoderParameters encoder;
    EncoderParameters encoderWaveform;
    DecoderType fFileType;

    int fArgc;
    char* fArgv;

    int fEvents;
    int fWavePoints;
    int fBaselinePoints;
    int fShortPoints;
    int fLongPoints;
};