#include "ConfigParserFactory.hh"

ConfigParserFactory* ConfigParserFactory::fParserFactory = 0;

ConfigParserFactory* ConfigParserFactory::Instance() {
    if (fParserFactory == 0) {
        fParserFactory = new ConfigParserFactory();
    }
    return fParserFactory;
}

ConfigParserFactory::ConfigParserFactory() {
}

ConfigParserFactory::~ConfigParserFactory() {
    delete fParserFactory;
}

void ConfigParserFactory::SetFileName(std::string name) {
    fName = name;
}

ConfigParser* ConfigParserFactory::BuildParser() {
    ConfigParser* aParser = nullptr;
    if (fName == "") aParser = ConfigInputParser::Instance();
    // else 
    return aParser;
}