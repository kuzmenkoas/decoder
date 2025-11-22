#pragma once

#include "WriterFactory.hh"

// types of output
struct Output {
    bool RootNtuple = false;
    bool TxtNtuple = false;
};

// class stores which output types use to save a result
class OutputConfig {
public:
    OutputConfig() {};
    ~OutputConfig() {};

    void SetRootNtuple() {output.RootNtuple = true;};
    void SetTxtNtuple() {output.TxtNtuple = true;};
    
    // struct contains types of output (bool)
    Output GetOutput() {return output;};
private:
    Output output;
};