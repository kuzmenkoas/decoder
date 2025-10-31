#include <iostream>
#include "Decoder.hh"
#include "TString.h"
#include "TMath.h"
#include "WriterFactory.hh"
#include "EncoderParameters.hh"
#include "ConfigParser.hh"
#include "ConfigInputParser.hh"
#include "RootFile.hh"

int main(int argc, char* argv[]) {
    // if input parameters less 2 (executable file and file to decode) close program
    if (argc != 2) return 1;

    // Get parameters that should be encode
    ConfigInputParser* cfg = ConfigInputParser::Instance();
    EncoderParameters par = cfg->GetEncoderParameters();

    // send which file to encode
    TString file = argv[1];
    Decoder* aDecoder = new Decoder(file, par);

    // check how to save result and start decode
    Output out = cfg->GetOutputConfig()->GetOutput();
    if (out.RootNtuple) {
        Writer* aWriter = WriterFactory::Instance()->BuildWriter(WriterType::RootNtuple);
        aDecoder->SetWriter(aWriter);
        aDecoder->Decode();
    }
    if (out.TxtNtuple) {
        Writer* aWriter = WriterFactory::Instance()->BuildWriter(WriterType::TxtNtuple);
        aDecoder->SetWriter(aWriter);
        aDecoder->Decode();
    }
    aDecoder->Plot();
    RootFile::Instance()->CloseFile();
    
    return 0;
}