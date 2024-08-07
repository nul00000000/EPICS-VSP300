/**
 * Technique object to store parameters
 *
 * Author: Adam Schultzer
 *
 * Copyright (c) : Brookhaven National Laboratory, 2024
 *
 */

#pragma once

#include <map>
#include <vector>
#include <string>
#include <BLStructs.h>
#include <BLFunctions.h>

using namespace std;

/**
 * Technique class for containing an instance of parameter data
 */
class Technique {
    public:
        /**
         * Creates a new technique object
         * 
         * @param name Name of techique
         */
        Technique(string name);
        /**
         * Closes all resources
         */
        ~Technique();

        /**
         * Name of technique
         */
        string name; //had to unconst this because = operator for vector fun

        // Add parameters to technique

        void addParam(string name, double value);
        void addParam(string name, int value);
        void addParam(string name, bool value);

        void addParamArray(string name, vector<double> value);
        void addParamArray(string name, vector<int> value);
        void addParamArray(string name, vector<bool> value);

        void addParamArrayValue(string name, double value);
        void addParamArrayValue(string name, int value);
        void addParamArrayValue(string name, bool value);

        /**
         * Get TEccParams_t object to upload to device
         */
        TEccParams_t getEccParams();

        // Get values of parameters

        double getSingle(string param);
        int getInt(string param);
        bool getBool(string param);
        vector<double> getSingles(string param);
        vector<int> getInts(string param);
        vector<bool> getBools(string param);
    private:
        // mappings from parameter names to values

        map<string, double> singles;
        map<string, int> ints;
        map<string, bool> bools;
        map<string, vector<double>> singleArrays;
        map<string, vector<int>> intArrays;
        map<string, vector<bool>> boolArrays;
};