#pragma once

#include "ConfigInputParser.hh"
#include "ConfigFileParser.hh"
#include "ConfigParser.hh"
#include <string>

class ConfigParserFactory {
public:
    static ConfigParserFactory* Instance();
    void SetFileName(std::string name);
    ConfigParser* BuildParser();
private:
    ConfigParserFactory();
    ~ConfigParserFactory();
    static ConfigParserFactory* fParserFactory;
    std::string fName = "";
};