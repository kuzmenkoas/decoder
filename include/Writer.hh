#pragma once

#include "EncoderParameters.hh"
#include "Waveform.hh"
// abstract class to different output types saving
// (interface)
class Writer {
public:
    Writer() {};
    ~Writer() {};

    // write an event to file
    virtual void Write(Encoder encoder, EncoderParameters par) {};
    virtual void Write(Waveform aWave) {};
    virtual void Write(WaveformSig aWave) {};
    // create output file (txt, root etc)
    virtual void CreateFile(EncoderParameters par) {};
    virtual void CreateFile() {};
    // close this file
    virtual void CloseFile() {};
private:
};