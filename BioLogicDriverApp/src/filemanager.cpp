#include "filemanager.h"

FileManager::FileManager(string directory) {
    int num = 0;
    while(doesFileExist(directory + "/test" + to_string(num) + ".dat")) {
        num++;
    }
    fileStream = ofstream(directory + "/test" + to_string(num) + ".dat");
}

FileManager::~FileManager() {
    fileStream.close();
}

void FileManager::setDirectory(string directory) {
    fileStream.close();
    int num = 0;
    while(doesFileExist(directory + "/test" + to_string(num) + ".dat")) {
        num++;
    }
    fileStream = ofstream(directory + "/test" + to_string(num) + ".dat");
}

void FileManager::writeData(uint8_t* data) {
    fileStream << data;
    fileStream.flush();
}

bool FileManager::doesFileExist(string filePath) {
    if (FILE *file = fopen(filePath.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}