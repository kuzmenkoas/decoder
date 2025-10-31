#ifndef Writer_hh
#define Writer_hh 1

#include "EncoderParameters.hh"

// abstract class to different output types saving
// (interface)
class Writer {
public:
    Writer() {};
    ~Writer() {};

    // write an event to file
    virtual void Write(Encoder encoder, EncoderParameters par) {};
    // create output file (txt, root etc)
    virtual void CreateFile(EncoderParameters par) {};
    // close this file
    virtual void CloseFile() {};
private:
};

#endif