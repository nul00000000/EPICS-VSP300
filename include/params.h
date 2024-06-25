#pragma once

#include "BioLogicDriver.hpp"
#include <dbAccessDefs.h>

using namespace std;

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

        int* singleArrayLengths;
        int* intArrayLengths;
        int* boolArrayLengths;

        Params(int numSingle, int numInt, int numBool, 
                int numSingleArray, int numIntArray, int numBoolArray,
                asynPortDriver* driver);
        ~Params();

        void createParams();
        void clearLabels();
        void setupParamsForTech(string tech);
    private:
        asynPortDriver* driver;

        int sIndex;
        int iIndex;
        int bIndex;
        int saIndex;
        int iaIndex;
        int baIndex;

        void addSLabel(string label);
        void addILabel(string label);
        void addBLabel(string label);
        void addSALabel(string label);
        void addIALabel(string label);
        void addBALabel(string label);
};