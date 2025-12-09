# Description
Decoder for Digitizer version 1.1.1 output (PSD and Waveform). Reads binary files, saves results in root and txt formats.
Open source: [GitHub](https://github.com/kuzmenkoas/decoder.git).
Can be installed for Linux and Windows.

# Requirements
* ROOT
* cmake && make
* C++17

# Installation guide
## Linux
```bash
git clone https://github.com/kuzmenkoas/decoder.git
cd decoder
mkdir build
cd build
cmake ..
make
```

## Windows
1. Install Visual Studio (https://visualstudio.microsoft.com/downloads/).
2. Install CMake (https://cmake.org/download/).
3. Compile project with cmake (use visual studio compiler) to build.
4. Compile project with Visual Studio (a button decoder.exe). 
<!-- 5. An executable file will be in out/build/decoder.exe. -->
6. Add path to executable file to environment variable PATH: 
* Win+R, call sysdm.cpl;
* Advanced->Environment variables->PATH->Edit->Add a path to decoder.exe.


# Usage
Note: if use application on Windows with integrated Environment variable, you can start it as decoder.exe from any directory in cmd/powershell.
If you use application in Linux use ./decoder instead of decoder.exe.

There are two ways to start an application. You need to give a program either one or two pathes:

```powershell
decoder.exe ${path to bin file PSD or Waveform}
```

```powershell
decoder.exe ${path to bin file PSD} ${path to bin file Waveform}
```
Note: first file is PSD and second Waveform strictly!

# Example
For program with console configuration use.
If data files are filePSD.bin and fileWaveform.bin in directory data use:
* To start decoder for PSD file only
```powershell
decoder.exe data/filePSD.bin
```
* To start decoder for Waveform file only
```powershell
decoder.exe data/fileWaveform.bin
```
* To start decoder for both files
```powershell
decoder.exe data/filePSD.bin data/fileWaveform.bin
```

For program with file configuration use.
If data files are filePSD.bin and fileWaveform.bin in directory data use:
* To start decoder for PSD file only
```powershell
decoder.exe cfg/psd.cfg data/filePSD.bin
```
* To start decoder for Waveform file only
```powershell
decoder.exe cfg/waveform.cfg data/fileWaveform.bin
```
* To start decoder for both files
```powershell
decoder.exe cfg/psdWaveform.cfg data/filePSD.bin data/fileWaveform.bin
```

# Configuration
## Input Parser
After start of program, there will be different cmd input modules start (depend on input data). They are needable for configuration of progrma (parameters that application does not know). Let's see all of them.

**1. Format of input file**
If you'll give 1 binary file for an application, you'll get a question:
```
What file is it?
 (1) PSD
 (2) Waveform
```
Enter either 1 for PSD or 2 for Waveform. That's depends on decoder alghorithm.

**2. Format save of output file**
Next question that is independent from input files is:
```
Choose format to save
 (1) Root
 (2) Txt
 (3) Root and Txt
```

**3. What is encode in PSD binary file**
This text will appear if there will be PSD file input.
```
What is encode in binary PSD file.
Choose everything that is stored in bin file 
(decoder will not be able to work correctly if this parameters will be incorrect)!
For multiple write as 123 - for qShort, qLong and cfd_y1. 
If in binary file stored all parameters choose 0 (ALL):
 (1) qShort
 (2) qLong
 (3) cfd_y1
 (4) cfd_y2
 (5) baseline
 (6) height
 (7) eventCounter
 (8) eventCounterPSD
 (9) psdValue
 (0) ALL
```
Enter numbers of choosed parameters in a continuous line.
For example, 123 for qShort, qLong and cfd_y1; 157 for qShort, baseline and eventCounter.
If saved parameters in binary file are all possible, you can enter only 0.

**4. Either signal negative or not**
This question will appear if:
1. PSD input file stores qShort, qLong or baseline.
2. Waveform input file for any case.
3. If there are waveform and psd input files for any cases.
```
Reverse integral?
 (1) Yes
 (2) Not
```
If you'll enter 1. The result of baseline, qShort and qLong will be reversed (multiply by -1).

**5. Waveform**
Will appear if there is a binary file with Waveform data. Needed to get integral of signal.
```
The number of baseline points?
```

```
The number of qShort points?
```

```
The number of qLong points?
```
For all of them it is need to enter an integer value.
Waveform for one event has certain length (wave length). 
Baseline points is needable to define baseline (first points of wave from 0 to baseline points used to estimate mean value of signal (baseline)).
After that, from baseline points to qShort points are needable to calculate an integral in that interval.
The last one, from baseline points to qLong points -- to calculate qLong integral.

This question will appear if there will be only one input file (waveform binary file).
```
The number of waveform points?
```
You need to enter an integer value.
Note: waveform points must be the same as wave length in digitizer application. Otherwise, the result of decoder will be incorrect.

**6. Plots parameters**
This configuration will start independently from input files.
This modules configure a histogram plot (additional to ntuple data in csv or/and root). Needs to increase number of bins or/and fit.
This text will appear to configure plot data from PSD input file (if there are not psd file, this text will not appear).
```
Choose parameter to plot (multiply input, example: 123 for 3 parameters to plot)
 (0) exit
 (1) qShort
 (2) qLong
 (3) cfd_y1
 (4) cfd_y2
 (5) baseline
 (6) height
 (7) eventCounter
```

This text will appear after configuration psd file (if exists) to configure plot data from waveform input file (if there are not waveform file, this text will not appear).
```
Choose parameter to plot (multiply input, example: 123 for 3 parameters to plot) for Sig
 (0) exit
 (1) qShort
 (2) qLong
 (3) baseline
```

Enter all numbers that's need to histogram plot inextricably. Enter 0 to close without plot.

Plot configuration.
For each input parameter of plot will appear next input requests. 
There will be a hint to uderstand which parameter configuration starts. For example, for qShort will appear:
```
Configure a plot for parameter qShort
```

This configure the number of histogram bins.
```
Enter number of bins
```

This configure the minimum value of parameter in histogram (minimum limit).
```
Enter min value of histogram
```

This configure the maximum value of parameter in histogram (maximum limit).
```
Enter max value of histogram
```
Note: all input values must be integer!

## File Parser
It is possible to give program a .cfg file as argument, which will contain a configuration data (the same as from input parser).

The configuration file structure is:
```
Output
Reverse
DataPSD
DataWaveform
WaveformConfig
Histogram
```

For any binary file type (PSD or Waveform) it is required to have field Output. Not necessary: Reverse, Histogram.

For PSD binary file type must have field DataPSD.
For Waveform binary file tyoe two fields are necessary: DataWaveform and WaveformConfig.

The Output field configurates the output format (txt or root): RootNtuple and TxtNtuple.
Looks like:
```
Output
+ RootNtuple
+ TxtNtuple
```
As a result, there will be output data in txt and root format files.
If you need to save results only in root format (should remember that saving in txt format is time consume):
```
Output
+ RootNtuple
```

It is possible to reverse (multiply the result by -1) values of baseline, qShort and qLong (integrals). It is done using the parameter Reverse:
```
Reverse true
```
or
```
Reverse false
```
If the value is true - program will multiply this parameters by -1 (for both PSD and Waveform), if the value is false - program will fo nothing.

In field DataPSD it is necessary to indicate all variables, that were encoded in binary file (if this field filled incorrect the result of decoding will be incoccect).
All possible variables a shown below:
```
DataPSD
+ qShort
+ qLong
+ cfd_y1
+ cfd_y2
+ baseline
+ height
+ eventCounter
+ eventCounterPSD
+ psdValue
```

In DataWaveform field indicates, which variables are necessary to get from program. There are 4 variables:
```
DataWaveform
+ qShort
+ qLong
+ baseline
+ entries
```

There is a new variable entries that saves values from waveform in separate ntuple as values by each event. There are values id (number of event), t (time moment when the value of signal was get), wave (the value of signal).

Next, in field WaveformConfig indicates values that necessary for decoding: starting point for baseline, qShort and qLong (as in Digitizer program, it is not necessary to them be equel with values in Digitizer) and wave length (wavelength).
```
WaveformConfig
+ baseline 100
+ qShort 120
+ qLong 380
+ wavelength 1000
```
In this case, the wavelength value must be the same as the one used in the measurements, and it does not need to be specified if the program receives two input binary files - PSD and Waveform.

To configure histograms, you must specify the file type, parameter, number of bins, minimum value, and maximum value. In that order!

Example:
```
Histogram
+ PSD qShort 1000 -20000 200000
+ Waveform qShort 1000 -20000 200000
```

Example of configuration file for PSD and Waveform:
```
Output
+ RootNtuple
+ TxtNtuple

Reverse false

DataPSD
+ qShort
+ qLong
+ cfd_y1
+ cfd_y2
+ baseline
+ height
+ eventCounter
+ eventCounterPSD
+ psdValue

DataWaveform
+ qShort
+ qLong
+ baseline
+ entries

WaveformConfig
+ baseline 100
+ qShort 120
+ qLong 380

Histogram
+ PSD qShort 1000 -20000 200000
+ Waveform qShort 1000 -20000 200000
```

Example of configuration file for only PSD input file:
```
Output
+ RootNtuple
+ TxtNtuple

Reverse false

DataPSD
+ qShort
+ qLong
+ cfd_y1
+ cfd_y2
+ baseline
+ height
+ eventCounter
+ eventCounterPSD
+ psdValue

Histogram
+ PSD qShort 1000 -20000 200000
```

Example of configuration file for only Waveform input file:
```
Output
+ RootNtuple

Reverse false

DataWaveform
+ qShort
+ qLong
+ baseline
+ entries

WaveformConfig
+ baseline 100
+ qShort 120
+ qLong 380
+ wavelength 1000

Histogram
+ Waveform qShort 1000 -20000 200000
```

# Output
Output files will be in a directory where program was started.
Root file writes as tree (decoder).
Csv uses space separate.

# How it works?
## PSD
PSD binary files stores information as:
First 2 bytes + 2*amount of stored parameters is rabbish data.
Next bytes depends on parameters and follow a queue:
* qShort - 4 bytes
* qLong - 4 bytes
* cfd_y1 - 2 bytes
* cfd_y2 - 2 bytes
* baseline - 2 bytes
* height - 2 bytes
* eventCounter - 4 bytes
* eventCounterPSD - 4 bytes
* psdValue - 2 bytes

Note: a digitizer application allows to change this order but decoder use only this order!

For PSD binary file there are not additional processing in decoder.

## Waveform
Waveform stores data as 2 bytes*wave length for one event signal. That's why wave length is important to correctly decode binary file.
If there are two input files (PSD and waveform) wave length defines by algorithm: from PSD file defines the amount of events (by known size of PSD file and known used bytes to stored parameters), know number of event the wave length will be:
wave length = size(waveform file) / 2 bytes / amount of events

**baseline** defines as mean value of signal in first baseline points (user input).
**qShort** defines as integral of signal from baseline points to qShort points (user input) minus baseline multiply by qShort points.
**qLong** defines as integral of signal from baseline points to qLong points (user input) minus baseline multiply by qLong points.
