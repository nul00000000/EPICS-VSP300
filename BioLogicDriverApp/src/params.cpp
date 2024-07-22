#include "params.h"

Params::Params(int numSingle, int numInt, int numBool, 
        int numSingleArray, int numIntArray, int numBoolArray,
        asynPortDriver* driver) {
    this->driver = driver;
    
    this->singles = new int[numSingle];
    this->ints = new int[numInt];
    this->bools = new int[numBool];
    this->singleArrays = new int[numSingleArray];
    this->intArrays = new int[numIntArray];
    this->boolArrays = new int[numBoolArray];

    this->singleLabels = new int[numSingle];
    this->intLabels = new int[numInt];
    this->boolLabels = new int[numBool];
    this->singleArrayLabels = new int[numSingleArray];
    this->intArrayLabels = new int[numIntArray];
    this->boolArrayLabels = new int[numBoolArray];

    this->singleValues = new double[numSingle];
    this->intValues = new int[numInt];
    this->boolValues = new bool[numBool];
    this->singleArrayValues = new double*[numSingleArray];
    this->intArrayValues = new int*[numIntArray];
    this->boolArrayValues = new bool*[numBoolArray];

    for(int i = 0; i < numSingle; i++) {
        singleValues[i] = 0;
    }
    for(int i = 0; i < numInt; i++) {
        intValues[i] = 0;
    }
    for(int i = 0; i < numBool; i++) {
        boolValues[i] = 0;
    }
    for(int i = 0; i < numSingleArray; i++) {
        singleArrayValues[i] = nullptr;
    }
    for(int i = 0; i < numIntArray; i++) {
        intArrayValues[i] = nullptr;
    }
    for(int i = 0; i < numBoolArray; i++) {
        boolArrayValues[i] = nullptr;
    }

    this->numSingle = numSingle;
    this->numInt = numInt;
    this->numBool = numBool;
    this->numSingleArray = numSingleArray;
    this->numIntArray = numIntArray;
    this->numBoolArray = numBoolArray;

    this->singleArrayLengths = new int[numSingleArray];
    this->intArrayLengths = new int[numIntArray];
    this->boolArrayLengths = new int[numBoolArray];

    this->singleNames = new string[numSingle];
    this->intNames = new string[numInt];
    this->boolNames = new string[numBool];
    this->singleArrayNames = new string[numSingleArray];
    this->intArrayNames = new string[numIntArray];
    this->boolArrayNames = new string[numBoolArray];

    sIndex = 0;
    iIndex = 0;
    bIndex = 0;
    saIndex = 0;
    iaIndex = 0;
    baIndex = 0;
    ready = false;
}

Params::~Params() {
    delete[] singles;
    delete[] ints;
    delete[] bools;
    delete[] singleArrays;
    delete[] intArrays;
    delete[] boolArrays;

    delete[] singleLabels;
    delete[] intLabels;
    delete[] boolLabels;
    delete[] singleArrayLabels;
    delete[] intArrayLabels;
    delete[] boolArrayLabels;

    delete[] singleValues;
    delete[] intValues;
    delete[] boolValues;

    delete[] singleNames;
    delete[] intNames;
    delete[] boolNames;
    delete[] singleArrayNames;
    delete[] intArrayNames;
    delete[] boolArrayNames;
    
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

    delete[] singleArrayLengths;
    delete[] intArrayLengths;
    delete[] boolArrayLengths;
}

void Params::createParams() {
    char substitutions[40];
    for(int i = 0; i < numSingle; i++) {
        snprintf(substitutions, 40, "VSP_PSINGLE%d", i);
        driver->createParam(substitutions, asynParamFloat64, &singles[i]);
        snprintf(substitutions, 40, "VSP_LSINGLE%d", i);
        driver->createParam(substitutions, asynParamOctet, &singleLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/singleParam.template", substitutions);
    }

    for(int i = 0; i < numInt; i++) {
        snprintf(substitutions, 40, "VSP_PINT%d", i);
        driver->createParam(substitutions, asynParamInt32, &ints[i]);
        snprintf(substitutions, 40, "VSP_LINT%d", i);
        driver->createParam(substitutions, asynParamOctet, &intLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/intParam.template", substitutions);
    }

    for(int i = 0; i < numBool; i++) {
        snprintf(substitutions, 40, "VSP_PBOOL%d", i);
        driver->createParam(substitutions, asynParamInt32, &bools[i]);
        snprintf(substitutions, 40, "VSP_LBOOL%d", i);
        driver->createParam(substitutions, asynParamOctet, &boolLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/boolParam.template", substitutions);
    }

    for(int i = 0; i < numSingleArray; i++) {
        snprintf(substitutions, 40, "VSP_PSINGLEARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &singleArrays[i]);
        snprintf(substitutions, 40, "VSP_LSINGLEARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &singleArrayLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/singleArrayParam.template", substitutions);
    }

    for(int i = 0; i < numIntArray; i++) {
        snprintf(substitutions, 40, "VSP_PINTARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &intArrays[i]);
        snprintf(substitutions, 40, "VSP_LINTARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &intArrayLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/intArrayParam.template", substitutions);
    }

    for(int i = 0; i < numBoolArray; i++) {
        snprintf(substitutions, 40, "VSP_PBOOLARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &boolArrays[i]);
        snprintf(substitutions, 40, "VSP_LBOOLARR%d", i);
        driver->createParam(substitutions, asynParamOctet, &boolArrayLabels[i]);

        snprintf(substitutions, 40, "PREFIX=DEV:VSP, PORT=%s, INDEX=%d", driver->portName, i);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/boolArrayParam.template", substitutions);
    }

    ready = true;
}

void Params::updateValue(int function, void* value) {
    for(int i = 0; i < sIndex; i++) {
        if(function == singles[i]) {
            singleValues[i] = *((double*) value);
        }
    }
    for(int i = 0; i < iIndex; i++) {
        if(function == ints[i]) {
            intValues[i] = *((int*) value);
        }
    }
    for(int i = 0; i < bIndex; i++) {
        if(function == bools[i]) {
            int intValue = *((int*) value);
            boolValues[i] = intValue;
        }
    }
}

void Params::updateArrayValue(int function, string values) {
    string work = values;
    for(int i = 0; i < saIndex; i++) {
        if(function == singleArrays[i]) {
            if(singleArrayValues[i]) {
                delete[] singleArrayValues[i];
                singleArrayValues[i] = nullptr;
            }
            vector<double> vals;
            size_t commaIndex = 0;
            while(commaIndex != string::npos) {
                commaIndex = work.find_first_of(',');
                string element = work.substr(0, commaIndex);
                work = work.substr(commaIndex + 1);
                vals.push_back(stod(element));
            }
            singleArrayValues[i] = new double[vals.size()];
            for(int j = 0; j < vals.size(); j++) {
                singleArrayValues[i][j] = vals[j];
            }
            singleArrayLengths[i] = vals.size();
            return;
        }
    }
    for(int i = 0; i < iaIndex; i++) {
        if(function == intArrays[i]) {
            if(intArrayValues[i]) {
                delete[] intArrayValues[i];
                intArrayValues[i] = nullptr;
            }
            vector<int> vals;
            size_t commaIndex = 0;
            while(commaIndex != string::npos) {
                commaIndex = work.find_first_of(',');
                string element = work.substr(0, commaIndex);
                work = work.substr(commaIndex + 1);
                vals.push_back(stoi(element));
            }
            intArrayValues[i] = new int[vals.size()];
            for(int j = 0; j < vals.size(); j++) {
                intArrayValues[i][j] = vals[j];
            }
            intArrayLengths[i] = vals.size();
            return;
        }
    }
    for(int i = 0; i < baIndex; i++) {
        if(function == boolArrays[i]) {
            if(boolArrayValues[i]) {
                delete[] boolArrayValues[i];
                boolArrayValues[i] = nullptr;
            }
            vector<bool> vals;
            size_t commaIndex = 0;
            while(commaIndex != string::npos) {
                commaIndex = work.find_first_of(',');
                string element = work.substr(0, commaIndex);
                work = work.substr(commaIndex + 1);
                vals.push_back(stoi(element));
            }
            //me when vector<bool> doesn't have .data for memory optimization
            bool* b = new bool[vals.size()];
            for(int j = 0; j < vals.size(); j++) {
                b[j] = vals[j];
            }
            boolArrayValues[i] = b;
            boolArrayLengths[i] = vals.size();
            return;
        }
    }
}

//this will not clear the names variables so make sure you've got those indexes well tracked
void Params::clearLabels() {
    sIndex = 0;
    iIndex = 0;
    bIndex = 0;
    saIndex = 0;
    iaIndex = 0;
    baIndex = 0;
    for(int i = 0; i < numSingle; i++) {
        driver->setStringParam(singleLabels[i], "");
    }
    for(int i = 0; i < numInt; i++) {
        driver->setStringParam(intLabels[i], "");
    }
    for(int i = 0; i < numBool; i++) {
        driver->setStringParam(boolLabels[i], "");
    }
    for(int i = 0; i < numSingleArray; i++) {
        driver->setStringParam(singleArrayLabels[i], "");
        singleArrayLengths[i] = 0;
    }
    for(int i = 0; i < numIntArray; i++) {
        driver->setStringParam(intArrayLabels[i], "");
        intArrayLengths[i] = 0;
    }
    for(int i = 0; i < numBoolArray; i++) {
        driver->setStringParam(boolArrayLabels[i], "");
        boolArrayLengths[i] = 0;
    }
}

void Params::addSLabel(string label) {
    driver->setStringParam(singleLabels[sIndex], label);
    singleNames[sIndex] = label;
    sIndex++;
}

void Params::addILabel(string label) {
    driver->setStringParam(intLabels[iIndex], label);
    intNames[iIndex] = label;
    iIndex++;
}

void Params::addBLabel(string label) {
    driver->setStringParam(boolLabels[bIndex], label);
    boolNames[bIndex] = label;
    bIndex++;
}

void Params::addSALabel(string label) {
    driver->setStringParam(singleArrayLabels[saIndex], label);
    singleArrayNames[saIndex] = label;
    saIndex++;
}

void Params::addIALabel(string label) {
    driver->setStringParam(intArrayLabels[iaIndex], label);
    intArrayNames[iaIndex] = label;
    iaIndex++;
}

void Params::addBALabel(string label) {
    driver->setStringParam(boolArrayLabels[baIndex], label);
    boolArrayNames[baIndex] = label;
    baIndex++;
}

void Params::setupParamsForTech(string name) {
    clearLabels();
    if(name == "ocv") {
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dE");
        addSLabel("Record_every_dT");
        // t.len = 3;
        // params = new TEccParam_t[t.len];
        // BL_DefineSglParameter("Rest_time_T", blParams->singleValues[0], 0, &params[0]);
        // BL_DefineSglParameter("Record_every_dE", blParams->singleValues[1], 0, &params[1]);
        // BL_DefineSglParameter("Record_every_dT", blParams->singleValues[2], 0, &params[2]);
    } else if(name == "cv") {
        addBALabel("vs_initial");
        addSALabel("Voltage_step");
        addSALabel("Scan_Rate");
        addSLabel("Record_every_dE");
        addBLabel("Average_over_dE");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
    } else if(name == "biovscan") { //cva
        addBALabel("vs_initial");
        addSALabel("Voltage_step");
        addSALabel("Scan_Rate");
        addSLabel("Record_every_dE");
        addBLabel("Average_over_dE");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addBALabel("vs_initial_step");
        addSALabel("Voltage_step");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addBLabel("Trig_on_off");

    } else if(name == "cp") {
        addSALabel("Current_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addILabel("I_Range");
    } else if(name == "ca") {
        addSALabel("Voltage_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
    } else if(name == "vscan") {
        addSALabel("Voltage_step");
        addBALabel("vs_initial");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
    } else if(name == "iscan") {
        addSALabel("Current_step");
        addBALabel("vs_initial");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("Record_every_dI");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_E");
        addSLabel("End_measuring_E");
        addILabel("I_Range");
    } else if(name == "pow") {
        addSALabel("Power_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addILabel("I_Range");
    } else if(name == "load") {
        addSALabel("Load_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addILabel("I_Range");
    } else if(name == "peis" || name == "speis") {
        addBLabel("vs_initial");
        addBLabel("vs_final");
        addSLabel("Initial_Voltage_step");
        addSLabel("Final_Voltage_step");
        addSLabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addSLabel("Final_frequency");
        addSLabel("Initial_frequency");
        addBLabel("sweep");
        addSLabel("Amplitude_Voltage");
        addILabel("Frequency_nuumber");
        addILabel("Average_N_times");
        addBLabel("Correction");
        addSLabel("Wait_for_steady");
    } else if(name == "geis" || name == "sgies") {
        addBLabel("vs_initial");
        addBLabel("vs_final");
        addSLabel("Initial_Voltage_step");
        addSLabel("Final_Voltage_step");
        addSLabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addSLabel("Final_frequency");
        addSLabel("Initial_frequency");
        addBLabel("sweep");
        addSLabel("Amplitude_Current");
        addILabel("Frequency_nuumber");
        addILabel("Average_N_times");
        addBLabel("Correction");
        addSLabel("Wait_for_steady");
        addILabel("I_Range");
    } else if(name == "dpv" || name == "swv" 
            || name == "npv" || name == "rnpv"
            || name == "dnpv") {
        addSLabel("Ei");
        addBLabel("OCi");
        addSLabel("Rest_time_Ti");
        addSLabel("Ef");
        addBLabel("OCf");
        addSLabel("PH");
        addSLabel("PW");
        addSLabel("SH");
        addSLabel("ST");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addILabel("I_Range");
    } else if(name == "dpa") {
        addSLabel("Ei");
        addBLabel("OCi");
        addSLabel("Rest_time_Ti");
        addSLabel("PPH");
        addSLabel("PPW");
        addSLabel("PH");
        addSLabel("PW");
        addSLabel("P");
        addSLabel("Tp");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addILabel("I_Range");
    } else if(name == "evt") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
    } else if(name == "lp" || name == "gc") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
        addBLabel("OC1");
        addSLabel("E1");
        addSLabel("T1");
        addBALabel("vs_initial_scan");
        addSALabel("Voltage_scan");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("Record_every_dE");
        addBLabel("Average_over_dE");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
    } else if(name == "cpp") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
        addBALabel("vs_initial_scan");
        addSALabel("Voltage_scan");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("I_pitting");
        addSLabel("t_b");
        addSLabel("Record_every_dE");
        addBLabel("Average_over_dE");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addSLabel("Record_every_dT");
    } else if(name == "pdp") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
        addBALabel("vs_initial_scan");
        addSALabel("Voltage_scan");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("I_pitting");
        addSLabel("t_b");
        addSLabel("Record_every_dE");
        addBLabel("Average_over_dE");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addSLabel("Record_every_dT");
        addBLabel("Hold");
    } else if(name == "psp") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
        addSLabel("Ei");
        addBLabel("OCi");
        addSLabel("Rest_time_Ti");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addSLabel("I_pitting");
        addSLabel("t_b");
        addILabel("I_Range");
    } else if(name == "zra") {
        addSLabel("Record_every_dEr");
        addSLabel("Rest_time_T");
        addSLabel("Record_every_dTr");
        addSLabel("Ei");
        addBLabel("OCi");
        addSLabel("Rest_time_Ti");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addSLabel("I_max");
        addSLabel("t_b");
    } else if(name == "IRcmp") {
        addSLabel("Rcmp_Value");
        addILabel("Rcmp_Mode");
    } else if(name == "pzir") {
        addSLabel("Final_frequency");
        addSLabel("Initial_frequency");
        addSLabel("Amplitude_Voltage");
        addILabel("Average_N_times");
        addSLabel("Wait_for_steady");
        addBLabel("sweep");
        addSLabel("Rcomp_Level");
        addILabel("Rcmp_Mode");
    } else if(name == "gzir") {
        addSLabel("Final_frequency");
        addSLabel("Initial_frequency");
        addSLabel("Amplitude_Current"); //docs say single depend on instrument??
        addILabel("Average_N_times");
        addSLabel("Rcomp_Level");
        addSLabel("Wait_for_steady");
        addBLabel("sweep");
        addILabel("I_Range");
        addILabel("Rcmp_Mode");
    } else if(name == "loop") {
        addILabel("loop_N_times");
        addILabel("protocol_number");
    } else if(name == "TO") {
        addILabel("Trigger_Logic");
        addILabel("Trigger_Duration");
    } else if(name == "TI" || name == "TOS") {
        addILabel("Trigger_Logic");
    } else if(name == "lasv") {
        addSLabel("Ei");
        addBLabel("Ei_vs_initial");
        addSALabel("Fs");
        addSALabel("E1");
        addBALabel("E1_vs_initial");
        addSALabel("E2");
        addBALabel("vs_initial");
        addIALabel("Period_number");
        addSALabel("Record_every_dT");
        addSALabel("Record_every_dI");
        addILabel("Step_number");
        addILabel("N_Cycles");
    } else if(name == "cplimit") {
        addSALabel("Current_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addIALabel("Test1_Config");
        addSALabel("Test1_Value");
        addIALabel("Test2_Config");
        addSALabel("Test2_Value");
        addIALabel("Test3_Config");
        addSALabel("Test3_Value");
        addIALabel("Exit_Cond");
        addILabel("I_Range");
    } else if(name == "calimit") {
        addSALabel("Voltage_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addILabel("Step_number");
        addSLabel("Record_every_dT");
        addSLabel("Record_every_dI");
        addIALabel("Test1_Config");
        addSALabel("Test1_Value");
        addIALabel("Test2_Config");
        addSALabel("Test2_Value");
        addIALabel("Test3_Config");
        addSALabel("Test3_Value");
        addIALabel("Exit_Cond");
        addILabel("N_Cycles");
    } else if(name == "vscanlimit") {
        addSALabel("Voltage_step");
        addBALabel("vs_initial");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("Record_every_dE");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_I");
        addSLabel("End_measuring_I");
        addIALabel("Test1_Config");
        addSALabel("Test1_Value");
        addIALabel("Test2_Config");
        addSALabel("Test2_Value");
        addIALabel("Test3_Config");
        addSALabel("Test3_Value");
        addIALabel("Exit_Cond");
    } else if(name == "iscanlimit") {
        addSALabel("Current_step");
        addBALabel("vs_initial");
        addSALabel("Scan_Rate");
        addILabel("Scan_number");
        addSLabel("Record_every_dI");
        addILabel("N_Cycles");
        addSLabel("Begin_measuring_E");
        addSLabel("End_measuring_E");
        addIALabel("Test1_Config");
        addSALabel("Test1_Value");
        addIALabel("Test2_Config");
        addSALabel("Test2_Value");
        addIALabel("Test3_Config");
        addSALabel("Test3_Value");
        addIALabel("Exit_Cond");
        addILabel("I_Range");
    } else if(name == "mp") {
        addSALabel("Value_step");
        addBALabel("vs_initial");
        addSALabel("Duration_step");
        addSALabel("Record_every_dT");
        addSALabel("Record_every_dM");
        addIALabel("Mode_step");
        addILabel("Step_number");
        addILabel("Record_every_rc");
        addILabel("N_Cycles");
    } else if(name == "casg") {
        addSLabel("Ii");
        addBLabel("Ii_vs_initial");
        addSALabel("Fs");
        addSALabel("I1");
        addBALabel("I1_vs_initial");
        addSALabel("I2");
        addBALabel("I2_vs_initial");
        addIALabel("Period_number");
        addSALabel("Record_every_dT");
        addSALabel("Record_every_dE");
        addILabel("Step_number");
        addILabel("N_Cycles");
    } else if(name == "casp") {
        addSLabel("Ei");
        addBLabel("Ei_vs_initial");
        addSALabel("Fs");
        addSALabel("E1");
        addBALabel("E1_vs_initial");
        addSALabel("E2");
        addBALabel("vs_initial");
        addIALabel("Period_number");
        addSALabel("Record_every_dT");
        addSALabel("Record_every_dI");
        addILabel("Step_number");
        addILabel("N_Cycles");
    } else {
        printf("Unrecognized technique: %s\n", name);
    }
}

Technique Params::buildTechnique(string name) {
    Technique t(name);
    for(int i = 0; i < sIndex; i++) {
        t.addParam(singleNames[i], singleValues[i]);
    }
    for(int i = 0; i < iIndex; i++) {
        t.addParam(intNames[i], intValues[i]);
    }
    for(int i = 0; i < bIndex; i++) {
        t.addParam(boolNames[i], boolValues[i]);
    }
    //you FOOL dont you know for arrays each element in the array is its OWN TEccParam??? (gonna explode)
    for(int i = 0; i < saIndex; i++) {
        for(int j = 0; j < singleArrayLengths[i]; j++) {
            t.addParamArrayValue(singleArrayNames[i], singleArrayValues[i][j]);
        }
    }
    for(int i = 0; i < iaIndex; i++) {
        for(int j = 0; j < intArrayLengths[i]; j++) {
            t.addParamArrayValue(intArrayNames[i], intArrayValues[i][j]);
        }
    }
    for(int i = 0; i < baIndex; i++) {
        for(int j = 0; j < boolArrayLengths[i]; j++) {
            t.addParamArrayValue(boolArrayNames[i], boolArrayValues[i][j]);
        }
    }
    return t;
}