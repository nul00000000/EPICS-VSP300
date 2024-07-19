#include <iostream>
#include <fstream>
#include <string>

#include <epicsStdio.h>
#include <iomanip>

using namespace std;

class FileManager {
    public:
        FileManager(string directory, bool hex);
        ~FileManager();

        void setDirectory(string directory, bool hex);
        void writeData(uint32_t* data, int numRows, int rowSize);

        void writeDataDebug(uint8_t* data);
    private:
        bool usingHex;

        ofstream fileStream;

        bool doesFileExist(string filePath);

        void writeDataRaw(uint32_t* data, int length);
        void writeDataHex(uint32_t* data, int numRows, int rowSize);
};