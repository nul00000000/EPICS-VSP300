/**
 * File manager for the BioLogicDriver EPICS driver
 *
 * Author: Adam Schultzer
 *
 * Copyright (c) : Brookhaven National Laboratory, 2024
 *
 */

#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <epicsStdio.h>
#include <iomanip>

using namespace std;

#define DEFAULT_DIR string(getenv("USERPROFILE")) + "/Desktop/biologicdata"
#define DEFAULT_HEX false

/**
 * Manages the creation and writing of file of saved data
 */
class FileManager {
    public:
        /**
         * Creates a default FileManager instance, using DEFAULT_DIR as the directory
         * and DEFAULT_HEX as the option for saving as hex files
         */
        FileManager();
        /**
         * Create a FileManager instance in the specified directory and saves in the
         * specified format. Equivalent to calling setDirectory(), as that is what
         * this constructor does.
         * 
         * @param directory: Directory to save files
         * @param hex: true to save as hex file, false to save as a binary
         */
        FileManager(string directory, bool hex);
        /**
         * Closes resources used by this FileManager
         */
        ~FileManager();

        /**
         * Sets current directory that files will be saved to, as well as what format
         * to saves files here as.
         * 
         * @param directory Directory to save files
         * @param hex true to save as hex file, false to save as a binary
         */
        void setDirectory(string directory, bool hex);
        /**
         * Sets the current technique that should be used to save data. In order to properly separate
         * the data of differing formats, this function closes the previously written to file and creates
         * a new one with the technique name
         * 
         * @param techniqueName Name of new technique to save data for
         */
        void setTechnique(string techniqueName);
        /**
         * Sets the current technique that should be used to save data. In order to properly separate
         * the data of differing formats, this function closes the previously written to file and creates
         * a new one with the technique number
         * 
         * @param techniqueNum Number of new technique to save data for
         */
        void setTechnique(int techNum);

        /**
         * Writes data from an array of integers to the current directory and file, using either
         * the hex or raw format depending on settings
         */
        void writeData(uint32_t* data, int numRows, int rowSize);
    private:
        /**
         * True if saving in hex format, false if saving in raw format
         */
        bool usingHex;
        /**
         * Directory where files will be saved
         */
        string directory;
        /**
         * Whether the directory and hex settings have been properly set up
         */
        bool ready = false;

        /**
         * File stream to save data to
         */
        ofstream fileStream;

        /**
         * Tests if the file exists in order to not overwrite existing files
         * 
         * @param filePath Path of file to check
         * 
         * @return true if the file exists, false if it does not
         */
        bool doesFileExist(string filePath);


        /**
         * Writes raw data
         * 
         * @param data Data to write
         * @param length length of data to write
         */
        void writeDataRaw(uint32_t* data, int length);
        /**
         * Writes hex data
         * 
         * @param data Data to write
         * @param numRows Number of rows of data
         * @param rowSize Size of rows in the data
         */
        void writeDataHex(uint32_t* data, int numRows, int rowSize);
};