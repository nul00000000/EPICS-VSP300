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

        string name; //had to unconst this because = operator for vector fun

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

        double getSingle(string param);
        int getInt(string param);
        bool getBool(string param);
        vector<double> getSingles(string param);
        vector<int> getInts(string param);
        vector<bool> getBools(string param);
    private:
        map<string, double> singles;
        map<string, int> ints;
        map<string, bool> bools;
        map<string, vector<double>> singleArrays;
        map<string, vector<int>> intArrays;
        map<string, vector<bool>> boolArrays;
};