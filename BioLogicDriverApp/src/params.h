#pragma once

#include "BioLogicDriver.hpp"
#include <dbAccessDefs.h>

class Params {
    public:
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

        double* singleValues;
        int* intValues;
        bool* boolValues;
        double** singleArrayValues;
        int** intArrayValues;
        bool** boolArrayValues;

        int numSingle;
        int numInt;
        int numBool;
        int numSingleArray;
        int numIntArray;
        int numBoolArray;

        Params(int numSingle, int numInt, int numBool, int numSingleArray, int numIntArray, int numBoolArray);
        ~Params();

        void createParams(asynPortDriver* driver);
};