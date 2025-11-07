# Description


# Requirements
* ROOT
* CMake && Make

# Install program
## Linux
```bash
mkdir build
cd build
cmake ..
make
```

## Windows
1. Install Visual Studio (https://visualstudio.microsoft.com/downloads/).
2. Install CMake (https://cmake.org/download/).
3. Compile project with cmake (use visual studio compiler) to build.
4. An executable file will be in build/Debug/decoder.exe .
5. Add path to executable file to environment variable PATH: 
* Win+R, call sysdm.cpl;
* Advanced->Environment variables->PATH->Edit->Add a path to decoder.exe .


# Usage
```bash
./decoder ${path to file}
```
# Example
If data file in directory decoder/data use:
```bash
./decoder ../data/file.bin
```
or
```bash
./build/decoder data/file.bin
```

# Configuration
After start program configure output:
```
Choose format to save
 (1) Root
 (2) Txt
 (3) Root and Txt
```
Write 1-3 to choose.

After, configure parameters to decode:
```
Choose saved parameters to decode (for multiple write as 123 - for qShort, qLong and cfd_y1):
 (1) qShort
 (2) qLong
 (3) cfd_y1
 (4) cfd_y2
 (5) baseline
 (6) height
 (7) eventCounter
 (8) eventCounterPSD
 (9) psdValue
```
Enter numbers of choosed parameters in a continuous line.
For example, 123 for qShort, qLong and cfd_y1; 157 for qShort, baseline and eventCounter.

# Output
Output files will be in a directory where program was started.
Root file writes as tree (decoder).
Csv uses space separate.
