#include <iostream>
#include "Decoder.hh"
#include "TString.h"
#include "TMath.h"
#include "ConfigInputParser.hh"
#include "RootFile.hh"

int main(int argc, char* argv[]) {
    // if input parameters less 2 (executable file and file to decode) close program
    if (argc != 2) return 1;

    Decoder* aDecoder = new Decoder(argv[1], // file name of file to decode
        ConfigInputParser::Instance()->GetEncoderParameters()); // says what is in file to decode (which parameters)

    // check how to save result and start decode
    Output out = ConfigInputParser::Instance()->GetOutputConfig()->GetOutput();
    aDecoder->Decode(); // decode and write as ntuple to root or txt or both
    aDecoder->Plot(); // starts configuration of histograms if need and saves to root and png

    // TODO (not good realization)
    RootFile::Instance()->CloseFile();
    
    return 0;
}