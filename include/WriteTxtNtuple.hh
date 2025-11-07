#ifndef WriteTxtNtuple_hh
#define WriteTxtNtuple_hh 1

#include "Writer.hh"
#include <fstream>

// class to save output as txt file with space separates
class WriteTxtNtuple : public Writer {
public:
    WriteTxtNtuple();
    ~WriteTxtNtuple();

    // write an event to file
    void Write(Encoder encoder, EncoderParameters par);
    // create output file txt
    void CreateFile(EncoderParameters par);
    // close this file
    void CloseFile();
private:
    Encoder event;
    std::ofstream fFile;

    // output file name
    std::string file = "output.txt";
};

#endif