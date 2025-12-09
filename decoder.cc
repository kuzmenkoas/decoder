#include "TString.h"
#include "TMath.h"
#include "RootFile.hh"
#include "DecoderBuilder.hh"
#include "ConfigParserFactory.hh"
#include "Plotter.hh"

int main(int argc, char* argv[]) {
    int binCounter = 1;
    for (int i = 0; i < argc; i++) {
        std::string tmp = argv[i];
        size_t dotPos = tmp.rfind('.');
        tmp = tmp.substr(dotPos);
        if (tmp == ".bin") binCounter++;
        if (tmp == ".cfg") ConfigParserFactory::Instance()->SetFileName(argv[i]);
    }

    ConfigParserFactory::Instance()->BuildParser()->SetArgc(binCounter, argv);
    ConfigParserFactory::Instance()->BuildParser()->Parse();
    
    DecoderBuilder* aDecoder = new DecoderBuilder(binCounter, argc, argv);
    Plotter::Instance()->Plot();
    // TODO (not good realization) smart ptr to solve
    RootFile::Instance()->CloseFile();
    
    return 0;
}