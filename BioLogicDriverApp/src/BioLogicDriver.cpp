/**
 * Main source file for the BioLogicDriver EPICS driver
 *
 * Author: Adam Schultzer
 *
 * Copyright (c) : Brookhaven National Laboratory, 2024
 *
 */

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

// EPICS includes
#include <epicsExit.h>
#include <epicsExport.h>
#include <epicsStdio.h>
#include <epicsString.h>
#include <epicsThread.h>
#include <epicsTime.h>
#include <iocsh.h>

#include "BioLogicDriver.hpp"
#include <dbAccessDefs.h>

// Error message formatters
#define ERR(msg)                                                                                 \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "ERROR | %s::%s: %s\n", driverName, functionName, \
              msg)

#define ERR_ARGS(fmt, ...)                                                              \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "ERROR | %s::%s: " fmt "\n", driverName, \
              functionName, __VA_ARGS__);

// Warning message formatters
#define WARN(msg) \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "WARN | %s::%s: %s\n", driverName, functionName, msg)

#define WARN_ARGS(fmt, ...)                                                            \
    asynPrint(pasynUserSelf, ASYN_TRACE_ERROR, "WARN | %s::%s: " fmt "\n", driverName, \
              functionName, __VA_ARGS__);

// Log message formatters
#define LOG(msg) \
    asynPrint(pasynUserSelf, ASYN_TRACEIO_DRIVER, "%s::%s: %s\n", driverName, functionName, msg)

#define LOG_ARGS(fmt, ...)                                                                       \
    asynPrint(pasynUserSelf, ASYN_TRACEIO_DRIVER, "%s::%s: " fmt "\n", driverName, functionName, \
              __VA_ARGS__);


using namespace std;

const char* driverName = "BioLogicDriver";

/**
 * @brief External configuration function for BioLogicDriver.
 *
 * Envokes the constructor to create a new BioLogicDriver object
 * This is the function that initializes the driver, and is called in the IOC startup script
 *
 * NOTE: When implementing a new driver with ADDriverTemplate, your camera may use a different
 * connection method than a const char* connectionParam. Just edit the param to fit your device, and
 * make sure to make the same edit to the constructor below
 *
 */
extern "C" int BioLogicDriverConfig(const char* portName) {
    new BioLogicDriver(portName);
    return (asynSuccess);
}


/**
 * @brief Callback function called when IOC is terminated.
 *
 * @param pPvt Pointer to BioLogicDriver object
 */
static void exitCallbackC(void* pPvt) {
    BioLogicDriver* pBioLogicDriver = (BioLogicDriver*)pPvt;
    delete pBioLogicDriver;
}

Channel BioLogicDriver::createChannel(int id) {
    Channel c;
    c.id = id;
    char sampleString[40];
    snprintf(sampleString, 40, "%s%d", EWE_STRING, id);
    createParam(sampleString, asynParamFloat64, &c.ewe);
    snprintf(sampleString, 40, "%s%d", ECE_STRING, id);
    createParam(sampleString, asynParamFloat64, &c.ece);
    snprintf(sampleString, 40, "%s%d", I_STRING, id);
    createParam(sampleString, asynParamFloat64, &c.I);
    snprintf(sampleString, 40, "%s%d", TECH_STRING, id);
    createParam(sampleString, asynParamOctet, &c.technique);

    return c;
}


/*
 * Function overwriting asynPortDriver base function.
 * Takes in a function (PV) changes, and a value it is changing to, and processes the input
 *
 * @params[in]: pasynUser       -> asyn client who requests a write
 * @params[in]: value           -> int32 value to write
 * @return: asynStatus      -> success if write was successful, else failure
 */
asynStatus BioLogicDriver::writeInt32(asynUser* pasynUser, epicsInt32 value) {
    int function = pasynUser->reason;
    int status = asynSuccess;
    static const char* functionName = "writeInt32";

    if (function < FIRST_BIOLOGICDRIVER_PARAM) {
        status = asynPortDriver::writeInt32(pasynUser, value);
    } else if(function == uploadNum) {
        printf(currentTechnique.c_str());
        printf("Uploading technique: %s\n", currentTechnique.c_str());
        string fullPath = "C:/EC-Lab Development Package/EC-Lab Development Package/" + currentTechnique + "4.ecc";

        TEccParams_t t = blParams->getEccParams();

        // BL_LoadTechnique(deviceID, currentChannel, fullPath.c_str(), t, false, false, false);

        printf("Loaded Params:\n");
        for(int i = 0; i < t.len; i++) {
            printf("Name: \"%s\", with value: %d\n", t.pParams[i].ParamStr, t.pParams[i].ParamVal);
        }
    } else if(function == chanNum) {
        this->currentChannel = value;
    } else {
        if(blParams) {
            blParams->updateValue(function, &value);
        } else {
            printf("blParams accessed before being initialized");
        }
    }

    if (status) {
        ERR_ARGS("ERROR status=%d, function=%d, value=%d", status, function, value);
        return asynError;
    }
    callParamCallbacks();
    return asynSuccess;
}

/*
 * Function overwriting asynPortDriver base function.
 * Takes in a function (PV) changes, and a value it is changing to, and processes the input
 * This is the same functionality as writeInt32, but for processing doubles.
 *
 * @params[in]: pasynUser       -> asyn client who requests a write
 * @params[in]: value           -> int32 value to write
 * @return: asynStatus      -> success if write was successful, else failure
 */
asynStatus BioLogicDriver::writeFloat64(asynUser* pasynUser, epicsFloat64 value) {
    int function = pasynUser->reason;
    asynStatus status = asynSuccess;
    static const char* functionName = "writeFloat64";
    if (function < FIRST_BIOLOGICDRIVER_PARAM) {
        status = asynPortDriver::writeFloat64(pasynUser, value);
    } else {
        if(blParams && blParams->ready) {
            blParams->updateValue(function, &value);
        } else {
            printf("blParams accessed before ready");
        }
    }

    if (status) {
        ERR_ARGS("ERROR status=%d, function=%d, value=%f", status, function, value);
    }

    callParamCallbacks();
    return status;
}

asynStatus BioLogicDriver::writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual) {
    int function = pasynUser->reason;
    asynStatus status = asynSuccess;
    static const char* functionName = "writeOctet";

    if (function < FIRST_BIOLOGICDRIVER_PARAM) {
        status = asynPortDriver::writeOctet(pasynUser, value, maxChars, nActual);
    } else if(function == techniqueNum) {
        currentTechnique = string(value);
        blParams->setupParamsForTech(currentTechnique);
    } else {
        blParams->updateArrayValue(function, string(value));
    }

    if (status) {
        ERR_ARGS("ERROR status=%d, function=%d, value=%f", status, function, value);
    }
    callParamCallbacks();
    return status;
}

/*
 * Function used for reporting BioLogicDriver device and library information to a external
 * log file. The function first prints all libuvc specific information to the file,
 * then continues on to the base asynPortDriver 'report' function
 *
 * @params[in]: fp      -> pointer to log file
 * @params[in]: details -> number of details to write to the file
 * @return: void
 */
void BioLogicDriver::report(FILE* fp, int details) {
    const char* functionName = "report";
    LOG("Reporting to external log file");
    if (details > 0) {
        fprintf(fp, " Connected Device Information\n");

        asynPortDriver::report(fp, details);
    }
}

void BioLogicDriver::setupConnection() {
    int code = BL_Connect("USB0", 5, &deviceID, &deviceInfo); //remember to change this you fool

    if(code) {
        numChannels = 0;
        this->channels = new Channel[0];
        return;
    }

    printf("VSP-300 Connected with ID: %d, Version: %d\n", deviceID, deviceInfo.FirmwareVersion);

    uint8_t plugged[MAX_CHANNELS];
    int results[MAX_CHANNELS];

    int err = BL_GetChannelsPlugged(deviceID, plugged, MAX_CHANNELS);

    numChannels = 0;

    for(int i = 0; i < MAX_CHANNELS; i++) {
        numChannels += plugged[i];
    }

    printf("Channels active: %d\n", numChannels);
    this->channels = new Channel[numChannels];

    int index = 0;

    for(int i = 0; i < numChannels; i++) {
        this->channels[index] = createChannel(i);
        this->channels[index].id = i;
        index++;
    }

    printf("Flashing VSP-300 firmware...\n");
    BL_LoadFirmware(deviceID, plugged, results, MAX_CHANNELS, false, true, 
            "C:/EC-Lab Development Package/EC-Lab Development Package/kernel4.bin", 
            "C:/EC-Lab Development Package/EC-Lab Development Package/Vmp_iv_0395_aa.xlx");
}

void BioLogicDriver::setupInitialValues() {
    this->setIntegerParam(idNum, deviceID);
    this->setIntegerParam(nchanNum, numChannels);
    this->setIntegerParam(versionNum, deviceInfo.FirmwareVersion);

    updateValues();
}

void BioLogicDriver::updateValues() {
    TCurrentValues_t currentValues;
    TExperimentInfos_t expInfo;

    // for(int i = 0; i < numChannels; i++) {
    //     int code = BL_GetCurrentValues(deviceID, channels[i].id, &currentValues);
    //     if(code) {
    //         printf("ERROR: Could not get channel values on channel %d\n", channels[i].id);
    //     } else {
    //         setDoubleParam(channels[i].ewe, currentValues.Ewe);
    //         setDoubleParam(channels[i].ece, currentValues.Ece);
    //         setDoubleParam(channels[i].I, currentValues.I);
    //     }

    //     code = BL_GetExperimentInfos(deviceID, channels[i].id, &expInfo);
    //     if(code) {
    //         printf("ERROR: Could not get channel info on channel %d\n", channels[i].id);
    //     } else {
    //         setStringParam(channels[i].technique, expInfo.Filename);
    //     }
    // }

    callParamCallbacks();
}

void update(void* parm) {
    BioLogicDriver* ioc = (BioLogicDriver*) parm;

    while(true) {
        ioc->updateValues();
        epicsThreadSleep(0.33); //update at ~3Hz
    }
}

BioLogicDriver::BioLogicDriver(const char* portName)
    : asynPortDriver(
          portName, 1, /* maxAddr */
          (int)NUM_BIOLOGICDRIVER_PARAMS,
          asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask | asynDrvUserMask |
              asynOctetMask, /* Interface mask */
          asynInt32Mask | asynFloat64Mask | asynFloat64ArrayMask |
              asynOctetMask, /* Interrupt mask */
          0, /* asynFlags.  This driver does not block and it is not multi-device, so flag is 0 */
          1, /* Autoconnect */
          0, /* Default priority */
          0) /* Default stack size*/
{
    static const char* functionName = "BioLogicDriver";

    currentTechnique = "unset";
    blParams = new Params(10, 4, 4, 5, 4, 2, this);

    createParam(BioLogicDriverVersionString, asynParamOctet, &BioLogicDriverVersion);

    blParams->createParams();

    setupConnection();

    createParam(ID_STRING, asynParamInt32, &idNum);
    createParam(NCHAN_STRING, asynParamInt32, &nchanNum);
    createParam(VERSION_STRING, asynParamInt32, &versionNum);
    createParam(TECH_STRING, asynParamOctet, &techniqueNum);
    createParam(UPLOAD_STRING, asynParamInt32, &uploadNum);
    createParam(CHAN_STRING, asynParamInt32, &chanNum);

    char* substitutions = new char[40];
    for(int i = 0; i < numChannels; i++) {
        // This line of code is gonna come back to get me I can feel it
        snprintf(substitutions, 40, "PREFIX=DEV:VSP, CHAN=%d, PORT=%s", channels[i].id, portName);
        dbLoadRecords("$(BIOLOGICDRIVER)/db/channel.template", substitutions);
    }
    delete[] substitutions;

    setupInitialValues();

    epicsThreadCreateOpt("Update Thread", update, this, NULL);

    // when epics is exited, delete the instance of this class
    epicsAtExit(exitCallbackC, (void*)this);
}

BioLogicDriver::~BioLogicDriver() {
    const char* functionName = "~BioLogicDriver";

    delete[] channels;
    BL_Disconnect(deviceID);
    LOG("Disconnecting BioLogicDriver device...");
    LOG("Shutdown complete.");
}

//-------------------------------------------------------------
// BioLogicDriver ioc shell registration
//-------------------------------------------------------------

/* BioLogicDriverConfig -> These are the args passed to the constructor in the epics config function */
static const iocshArg BioLogicDriverConfigArg0 = {"portName", iocshArgString};


/* Array of config args */
static const iocshArg* const BioLogicDriverConfigArgs[] = {&BioLogicDriverConfigArg0};

/* what function to call at config */
static void configBioLogicDriverCallFunc(const iocshArgBuf* args) {
    BioLogicDriverConfig(args[0].sval);
}

/* information about the configuration function */
static const iocshFuncDef configBioLogicDriver = {"BioLogicDriverConfig", 1, BioLogicDriverConfigArgs};

/* IOC register function */
static void BioLogicDriverRegister(void) { iocshRegister(&configBioLogicDriver, configBioLogicDriverCallFunc); }

/* external function for IOC register */
extern "C" {
epicsExportRegistrar(BioLogicDriverRegister);
}