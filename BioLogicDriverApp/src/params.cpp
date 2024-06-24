#include "params.h"

Params::Params(int numSingle, int numInt, int numBool, int numSingleArray, int numIntArray, int numBoolArray) {
    this->singles = new int[numSingle];
    this->ints = new int[numInt];
    this->bools = new int[numBool];
    this->singleArrays = new int[numSingleArray];
    this->intArrays = new int[numIntArray];
    this->boolArrays = new int[numBoolArray];

    this->singleValues = new double[numSingle];
    this->intValues = new int[numInt];
    this->boolValues = new bool[numBool];
    this->singleArrayValues = new double*[numSingleArray];
    this->intArrayValues = new int*[numIntArray];
    this->boolArrayValues = new bool*[numBoolArray];

    this->numSingle = numSingle;
    this->numInt = numInt;
    this->numBool = numBool;
    this->numSingleArray = numSingleArray;
    this->numIntArray = numIntArray;
    this->numBoolArray = numBoolArray;
}

Params::~Params() {
    delete[] singles;
    delete[] ints;
    delete[] bools;
    delete[] singleArrays;
    delete[] intArrays;
    delete[] boolArrays;

    delete[] singleValues;
    delete[] intValues;
    delete[] boolValues;
    
    for(int i = 0; i < numSingleArray; i++) {
        delete[] singleArrayValues[i];
    }
    delete[] singleArrayValues;

    for(int i = 0; i < numIntArray; i++) {
        delete[] intArrayValues[i];
    }
    delete[] intArrayValues;

    for(int i = 0; i < numBoolArray; i++) {
        delete[] boolArrayValues[i];
    }
    delete[] boolArrayValues;
}

void Params::createParams(asynPortDriver* driver) {
    char substitutions[40];
    for(int i = 0; i < numSingle; i++) {
        snprintf(substitutions, 40, "VSP_PSINGLE%d", i);
        driver->createParam(substitutions, asynParamFloat64, &singles[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/singleParam.template", substitutions);
    }

    for(int i = 0; i < numInt; i++) {
        snprintf(substitutions, 40, "VSP_PINT%d", i);
        driver->createParam(substitutions, asynParamInt32, &ints[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/intParam.template", substitutions);
    }

    for(int i = 0; i < numBool; i++) {
        snprintf(substitutions, 40, "VSP_PBOOL%d", i);
        driver->createParam(substitutions, asynParamInt32, &bools[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/boolParam.template", substitutions);
    }

    for(int i = 0; i < numSingleArray; i++) {
        snprintf(substitutions, 40, "VSP_PSINGLEARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &singleArrays[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/singleArrayParam.template", substitutions);
    }

    for(int i = 0; i < numIntArray; i++) {
        snprintf(substitutions, 40, "VSP_PINTARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &intArrays[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/intArrayParam.template", substitutions);
    }

    for(int i = 0; i < numBoolArray; i++) {
        snprintf(substitutions, 40, "VSP_PBOOLARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &boolArrays[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/boolArrayParam.template", substitutions);
    }
}