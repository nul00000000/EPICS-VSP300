#pragma once

#include <string>

using namespace std;

struct Channel {
    int id;
    int ewe;
    int ece;
    int I;

    int technique;

    int running;
    int file;
    int saveData;

    string filePath;
    bool savingData;
};