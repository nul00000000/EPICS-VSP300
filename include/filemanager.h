#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileManager {
    public:
        FileManager(string directory);
        ~FileManager();

        void setDirectory(string directory);
        void writeData(uint8_t* data);
    private:
        ofstream fileStream;

        bool doesFileExist(string filePath);
};