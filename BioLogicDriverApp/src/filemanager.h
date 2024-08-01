#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <epicsStdio.h>
#include <iomanip>

using namespace std;

#define DEFAULT_DIR string(getenv("USERPROFILE")) + "/Desktop/biologicdata"
#define DEFAULT_HEX false

class FileManager {
    public:
        FileManager();
        FileManager(string directory, bool hex);
        ~FileManager();

        void setDirectory(string directory, bool hex);
        void setTechnique(string techniqueName);
        void setTechnique(int techNum);

        void writeData(uint32_t* data, int numRows, int rowSize);
    private:
        bool usingHex;
        string directory;
        bool ready = false;

        ofstream fileStream;

        bool doesFileExist(string filePath);

        void writeDataRaw(uint32_t* data, int length);
        void writeDataHex(uint32_t* data, int numRows, int rowSize);
};