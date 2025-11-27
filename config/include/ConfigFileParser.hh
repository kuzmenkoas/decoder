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
    std::string GetFileName() {return fFileName;};
    void Parse();
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};
    EncoderParameters GetEncoderParametersWaveform() {return encoderWaveform;};
    DecoderType GetFileType() {return fFileType;};
    
    std::string GetOutputFileName() {return fOutputFileName;};
    int GetEvents() {return fEvents;};
    int GetWaveformNumber() {return fWavePoints;};
    int GetBaselineNumber() {return fBaselinePoints;};
    int GetShortNumber() {return fShortPoints;};
    int GetLongNumber() {return fLongPoints;};

    std::vector<PlotterHist> GetPlotterHist() {return fHist;};
    bool IsPlotterHist() {return isPlotterHist;};
    bool IsPlotterWaveform() {return isPlotterWaveform;};
private:
    ConfigFileParser();
    ~ConfigFileParser();

    void Reverse();
    void WaveformNumberRead();

    void DefineFileType();
    void DefineOutputFileName();

    static ConfigFileParser* fCfgParser;
    std::string fName[2];
    std::string fFileName;
    std::string fOutputFileName;
    
    std::ifstream OpenFile();
    void ReadOutput(std::string key = "Output");
    void ReadEncoder(std::string key = "DataPSD");
    void ReadWaveformData(std::string key = "DataWaveform");
    void ReadWaveformConfig(std::string key = "WaveformConfig");
    void ReadPlotterConfig(std::string key = "Histogram");
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

    std::vector<PlotterHist> fHist;
    bool isPlotterHist = false;
    bool isPlotterWaveform = false;
};