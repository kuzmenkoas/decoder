#pragma once

#include <string>
#include "OutputConfig.hh"
#include "DecoderType.hh"
#include "EncoderParameters.hh"

#include <iostream>
class ConfigParser {
public:
    ConfigParser() {};
    ~ConfigParser() {};

    virtual void SetArgc(int argc, char* argv[]) {};

    virtual void Parse() {};
    virtual void SetFileName(std::string name) {};

    virtual OutputConfig* GetOutputConfig() {return new OutputConfig();};
    virtual EncoderParameters GetEncoderParameters() {return EncoderParameters{};};
    virtual EncoderParameters GetEncoderParametersWaveform() {return EncoderParameters{};};
    virtual DecoderType GetFileType() {return DecoderType{};};

    virtual std::string GetOutputFileName() {return "";};
    virtual int GetEvents() {return 0;};
    virtual int GetWaveformNumber() {return 0;};
    virtual int GetBaselineNumber() {return 0;};
    virtual int GetShortNumber() {return 0;};
    virtual int GetLongNumber() {return 0;};
private:
};