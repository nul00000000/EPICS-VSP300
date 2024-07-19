#include "filemanager.h"

FileManager::FileManager(string directory, bool hex) {
    this->usingHex = hex;
    int num = 0;
    while(doesFileExist(directory + "/test" + to_string(num) + (hex ? ".hex" : ".bin"))) {
        num++;
    }
    if(hex) {
        fileStream = ofstream(directory + "/test" + to_string(num) + ".hex");
    } else {
        fileStream = ofstream(directory + "/test" + to_string(num) + ".bin", ios::binary);
    }
}

FileManager::~FileManager() {
    fileStream.close();
}

void FileManager::setDirectory(string directory, bool hex) {
    this->usingHex = hex;
    fileStream.close();
    int num = 0;
    while(doesFileExist(directory + "/test" + to_string(num) + (hex ? ".hex" : ".bin"))) {
        num++;
    }
    if(hex) {
        fileStream = ofstream(directory + "/test" + to_string(num) + ".hex");
    } else {
        fileStream = ofstream(directory + "/test" + to_string(num) + ".bin", ios::binary);
    }
}

void FileManager::writeData(uint32_t* data, int numRows, int rowSize) {
    if(usingHex) {
        writeDataHex(data, numRows, rowSize);
    } else {
        writeDataRaw(data, numRows * rowSize);
    }
    fileStream.flush();
}

void FileManager::writeDataHex(uint32_t* data, int numRows, int rowSize) {
    fileStream << internal << setfill('0') << hex;
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < rowSize; j++) {
            fileStream << setw(8) << data[i * rowSize + j] << " ";
        }
        fileStream << "\n";
    }
}

void FileManager::writeDataRaw(uint32_t* data, int length) {
    fileStream.write(reinterpret_cast<const char *>(data), length * sizeof(uint32_t));
}

bool FileManager::doesFileExist(string filePath) {
    if (FILE *file = fopen(filePath.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void FileManager::writeDataDebug(uint8_t* data) {
    printf("[DEBUG] %s", data);
}