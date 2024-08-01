#include "filemanager.h"

FileManager::FileManager() {
    setDirectory(DEFAULT_DIR, DEFAULT_HEX);
}

FileManager::FileManager(string directory, bool hex) {
    setDirectory(directory, hex);
}

FileManager::~FileManager() {
    fileStream.close();
}

void FileManager::setDirectory(string directory, bool hex) {
    ready = false;
    this->usingHex = hex;
    if(fileStream.is_open()) {
        fileStream.close();
    }
    size_t i = directory.find("//");
    if(i == string::npos) {
        this->directory = directory;
    } else {
        this->directory = directory.replace(i, 2, "/");
    }
}

void FileManager::setTechnique(string techniqueName) {
    if(fileStream.is_open()) {
        fileStream.close();
    }
    int num = 0;
    while(doesFileExist(directory + "/test_" + to_string(num) + "_" + techniqueName + (usingHex ? ".hex" : ".bin"))) {
        num++;
    }
    if(usingHex) {
        fileStream = ofstream(directory + "/test_" + to_string(num) + "_" + techniqueName + ".hex");
    } else {
        fileStream = ofstream(directory + "/test_" + to_string(num) + "_" + techniqueName + ".bin", ios::binary);
    }
    ready = true;
}

void FileManager::setTechnique(int techNum) {
    if(fileStream.is_open()) {
        fileStream.close();
    }
    int num = 0;
    while(doesFileExist(directory + "/test_" + to_string(num) + "_tech" + to_string(techNum) + (usingHex ? ".hex" : ".bin"))) {
        num++;
    }
    if(usingHex) {
        fileStream = ofstream(directory + "/test_" + to_string(num) + "_tech" + to_string(techNum) + ".hex");
    } else {
        fileStream = ofstream(directory + "/test_" + to_string(num) + "_tech" + to_string(techNum) + ".bin", ios::binary);
    }
    ready = true;
}

void FileManager::writeData(uint32_t* data, int numRows, int rowSize) {
    if(!ready) {
        printf("FileManager not ready, please set a technique\n");
        return;
    }
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