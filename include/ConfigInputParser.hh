#ifndef ConfigInputParser_hh
#define ConfigInputParser_hh 1

#include "OutputConfig.hh"

// Parser program configuration as console application\
// singleton class
class ConfigInputParser {
public:
    static ConfigInputParser* Instance();
    OutputConfig* GetOutputConfig() {return outputConfig;};
    EncoderParameters GetEncoderParameters() {return encoder;};

private:
    ConfigInputParser();
    ~ConfigInputParser();
    // read a format to save (root, txt)
    void SaveFormat();
    // read a parameters to encode
    void Parameters();
    // read reverse integral or not
    void Reverse();

    static ConfigInputParser* fCfgParser;
    // parser results
    OutputConfig* outputConfig = nullptr;
    EncoderParameters encoder;
};

#endif