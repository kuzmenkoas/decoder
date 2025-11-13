#include "TString.h"
#include "TMath.h"
#include "RootFile.hh"
#include "DecoderBuilder.hh"

int main(int argc, char* argv[]) {
    // if input parameters less 2 (executable file and file to decode) close program
    // TODO
    // if (argc != 2 || argc != 3) return 1;

    ConfigInputParser::Instance()->SetArgc(argc, argv);
    ConfigInputParser::Instance()->StartParser();
    DecoderBuilder* aDecoder = new DecoderBuilder(argc, argv);
    
    // TODO (not good realization)
    RootFile::Instance()->CloseFile();
    
    return 0;
}