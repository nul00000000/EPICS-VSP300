#pragma once

#include <string>
#include "filemanager.h"

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

    FileManager dataOut;
    bool savingData;
    int lastTechIndex;
};