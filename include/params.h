#pragma once

#include "BioLogicDriver.hpp"
#include <dbAccessDefs.h>

class Params {
    public:
        int* singles;
        int* ints;
        int* bools;
        int* singleArrays;
        int* intArrays;
        int* boolArrays;

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