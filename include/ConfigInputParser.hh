#ifndef ConfigInputParser_hh
#define ConfigInputParser_hh 1

#include "OutputConfig.hh"
#include "DecoderType.hh"

// Parser program configuration as console application\
// singleton class
class ConfigInputParser {
public:
    static ConfigInputParser* Instance();
    void SetArgc(int argc) {fArgc = argc; DefineFileType();};
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};
    DecoderType GetFileType() {return fFileType;};
    void StartParser();
    int GetWaveformNumber() {return fWavePoints;};
    int GetShortNumber() {return fShortPoints;};
    int GetLongNumber() {return fLongPoints;};
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

    void WaveformNumber();
    void ShortNumber();
    void LongNumber();

    static ConfigInputParser* fCfgParser;
    // parser results
    OutputConfig* outputConfig = nullptr;
    DecoderType fFileType;
    EncoderParameters encoder;
    int fArgc;
    int fWavePoints;
    int fShortPoints;
    int fLongPoints;
};

#endif