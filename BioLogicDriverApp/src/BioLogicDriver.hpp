#ifndef BIOLOGICDRIVER_H
#define BIOLOGICDRIVER_H
#include <asynPortDriver.h>
#include <epicsExport.h>
#include <iocsh.h>
#include <string>

#include <BLStructs.h>
#include <BLFunctions.h>
#include "channel.h"
#include "params.h"

#define MAX_CHANNELS 16

#define BIOLOGICDRIVER_VERSION_MAJOR 0
#define BIOLOGICDRIVER_VERSION_MINOR 0
#define BIOLOGICDRIVER_VERSION_PATCH 1

// Defines of strings that map Params to Records
#define BioLogicDriverVersionString "BIOLOGICDRIVER_VERSION"

#define ID_STRING "VSP_ID"
#define NCHAN_STRING "VSP_NCHAN"
#define VERSION_STRING "VSP_VERSION"
#define UPLOAD_STRING "VSP_UPLOAD"
#define CHAN_STRING "VSP_CHAN"

#define EWE_STRING "VSP_EWE"
#define ECE_STRING "VSP_ECE"
#define I_STRING "VSP_I"
#define TECH_STRING "VSP_TECH"

class Params;

class BioLogicDriver : public asynPortDriver {

public:
    BioLogicDriver(const char* portName);
    ~BioLogicDriver();

    /* These are the methods that we override from asynPortDriver as needed*/
    //virtual asynStatus readInt32(asynUser *pasynUser, epicsInt32 *value);
    virtual asynStatus writeInt32(asynUser* pasynUser, epicsInt32 value);
    //virtual asynStatus readFloat64(asynUser *pasynUser, epicsFloat64 *value);
    virtual asynStatus writeFloat64(asynUser* pasynUser, epicsFloat64 value);
    //virtual asynStatus readOctet(asynUser *pasynUser, char *value, size_t maxChars, size_t *nActual, int *eomReason);
    virtual asynStatus writeOctet(asynUser *pasynUser, const char *value, size_t maxChars, size_t *nActual);
    //virtual asynStatus connect(asynUser* pasynUser);
    //virtual asynStatus disconnect(asynUser* pasynUser);
    virtual void report(FILE* fp, int details);

    void updateValues();

protected:

#define FIRST_BIOLOGICDRIVER_PARAM BioLogicDriverVersion
    int BioLogicDriverVersion;
#define LAST_BIOLOGICDRIVER_PARAM BioLogicDriverVersion

private:
    Channel* channels;
    int numChannels;

    Params* blParams;

    int deviceID;
    TDeviceInfos_t deviceInfo;

    int idNum;
    int nchanNum;
    int versionNum;
    int techniqueNum;
    int uploadNum;
    int chanNum;

    std::string currentTechnique;
    int currentChannel;

    Channel createChannel(int id);
    void setupConnection();
    void setupInitialValues();
};

#define NUM_BIOLOGICDRIVER_PARAMS ((int)(&LAST_BIOLOGICDRIVER_PARAM - &FIRST_BIOLOGICDRIVER_PARAM + 1))
#endif