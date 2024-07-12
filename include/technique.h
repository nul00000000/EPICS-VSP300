#pragma once

#include <map>
#include <vector>
#include <string>
#include <BLStructs.h>
#include <BLFunctions.h>

using namespace std;

class Technique {
    public:
        Technique(string name);
        ~Technique();

        const string name;

        void addParam(string name, double value);
        void addParam(string name, int value);
        void addParam(string name, bool value);

        void addParamArray(string name, vector<double> value);
        void addParamArray(string name, vector<int> value);
        void addParamArray(string name, vector<bool> value);

        void addParamArrayValue(string name, double value);
        void addParamArrayValue(string name, int value);
        void addParamArrayValue(string name, bool value);

        TEccParams_t getEccParams();
    private:
        map<string, double> singles;
        map<string, int> ints;
        map<string, bool> bools;
        map<string, vector<double>> singleArrays;
        map<string, vector<int>> intArrays;
        map<string, vector<bool>> boolArrays;
};