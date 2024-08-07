/**
 * Technique parameter handler
 *
 * Author: Adam Schultzer
 *
 * Copyright (c) : Brookhaven National Laboratory, 2024
 *
 */

#pragma once

#include <BLStructs.h>
#include <asynPortDriver.h>
#include <dbAccessDefs.h>
#include "technique.h"

using namespace std;

class Params {
    public:
        // PV handles for parameter values and labels

        int* singles;
        int* singleLabels;
        int* ints;
        int* intLabels;
        int* bools;
        int* boolLabels;
        int* singleArrays;
        int* singleArrayLabels;
        int* intArrays;
        int* intArrayLabels;
        int* boolArrays;
        int* boolArrayLabels;

        // Current values of parameters

        double* singleValues;
        int* intValues;
        bool* boolValues;
        double** singleArrayValues;
        int** intArrayValues;
        bool** boolArrayValues;

        // Number of each type of parameter

        int numSingle;
        int numInt;
        int numBool;
        int numSingleArray;
        int numIntArray;
        int numBoolArray;

        // Lengths of paramter arrays

        int* singleArrayLengths;
        int* intArrayLengths;
        int* boolArrayLengths;

        /**
         * Whether the parameter manager is ready to be used
         */
        bool ready;

        /**
         * Creates parameter handler
         * 
         * @param numSingle Number of single parameters
         * @param numInt Number of integer parameters
         * @param numBool Number of bool parameters
         * @param numSingleArray Number of single array parameters
         * @param numIntArray Number of integer array parameters
         * @param numBoolArray Number of bool array parameters
         * @param driver Pointer to asyn driver using this param manager
         */
        Params(int numSingle, int numInt, int numBool, 
                int numSingleArray, int numIntArray, int numBoolArray,
                asynPortDriver* driver);

        /**
         * Closes all resources
         */
        ~Params();

        /**
         * Creates PVs for all parameters
         */
        void createParams();
        /**
         * Updates value of a given non-array parameter
         * 
         * @param function PV handle for given parameter
         * @param value Value as provided by asyn callbacks
         */
        void updateValue(int function, void* value);
        /**
         * Updates value of a given array parameter
         * 
         * @param function PV handle for given parameter
         * @param values Values in the format of a string as provided by asyn callbacks
         */
        void updateArrayValue(int function, string values);
        /**
         * Clears all labels to prepare for a new technique
         */
        void clearLabels();
        /**
         * Sets of parameter labels for a given technique
         * 
         * @param tech Technique to prepare for
         */
        void setupParamsForTech(string tech);
        /**
         * Build a Technique object from current parameter values
         * 
         * @param name Name of technique
         * 
         * @return New Technique object that can be built into EC-Lab params object
         */
        Technique buildTechnique(string name);
    private:
        /**
         * Asyn driver to interact with
         */
        asynPortDriver* driver;

        // Internal index for setting up parameters

        int sIndex;
        int iIndex;
        int bIndex;
        int saIndex;
        int iaIndex;
        int baIndex;

        // Current names of parameters

        string* singleNames;
        string* intNames;
        string* boolNames;
        string* singleArrayNames;
        string* intArrayNames;
        string* boolArrayNames;

        // Internal functions for adding parameters

        void addSLabel(string label);
        void addILabel(string label);
        void addBLabel(string label);
        void addSALabel(string label);
        void addIALabel(string label);
        void addBALabel(string label);
};