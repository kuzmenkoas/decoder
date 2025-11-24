#pragma once

#include "OutputConfig.hh"
#include "DecoderType.hh"
#include "ConfigParser.hh"

// Parser program configuration as console application\
// singleton class
class ConfigInputParser : public ConfigParser {
public:
    static ConfigInputParser* Instance();
    void SetArgc(int argc, char* argv[]);
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};
    DecoderType GetFileType() {return fFileType;};
    void Parse();

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
    ConfigInputParser();
    ~ConfigInputParser();
    // read a format to save (root, txt)
    void SaveFormat();
    // read a parameters to encode
    void Parameters();
    // read reverse integral or not
    void Reverse();

    void DefineFileType();
    void DefineOutputFileName();

    void WaveformNumber();
    void BaselineNumber();
    void ShortNumber();
    void LongNumber();

    static ConfigInputParser* fCfgParser;
    std::string fName[2];
    std::string fOutputFileName;

    // parser results
    OutputConfig* outputConfig = nullptr;
    DecoderType fFileType;
    EncoderParameters encoder;
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