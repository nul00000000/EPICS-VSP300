/**
 * Channel struct for the BioLogicDriver EPICS driver
 *
 * Author: Adam Schultzer
 *
 * Copyright (c) : Brookhaven National Laboratory, 2024
 *
 */

#pragma once

#include <string>
#include "filemanager.h"

using namespace std;

/**
 * Keeps track of various PV handles for a channel, as well as
 * per-channel data like file management 
 */
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