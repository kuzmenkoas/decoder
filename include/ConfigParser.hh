#pragma once

#include <string>
#include "OutputConfig.hh"
#include "DecoderType.hh"

class ConfigParser {
public:
    ConfigParser() {};
    ~ConfigParser() {};

    virtual void SetArgc(int argc, char* argv[]) {};

    virtual void Parse() {};
    virtual void Parse(std::string fileName) {};

    virtual OutputConfig* GetOutputConfig() {};
    virtual EncoderParameters GetEncoderParameters() {};
    virtual DecoderType GetFileType() {};

    virtual int GetEvents() {return 0;};
    virtual int GetWaveformNumber() {return 0;};
    virtual int GetBaselineNumber() {return 0;};
    virtual int GetShortNumber() {return 0;};
    virtual int GetLongNumber() {return 0;};
private:
};