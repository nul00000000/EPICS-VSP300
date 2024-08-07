#ifndef BIOLOGICDRIVER_H
#define BIOLOGICDRIVER_H
#include <asynPortDriver.h>
#include <epicsExport.h>
#include <iocsh.h>
#include <string>
#include <vector>

#include <BLStructs.h>
#include <BLFunctions.h>
#include "channel.h"
#include "params.h"
#include "technique.h"
#include "filemanager.h"

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
#define STATUS_STRING "VSP_STATUS"
#define START_STRING "VSP_START"
#define ADD_STRING "VSP_ADD"
#define CLEAR_STRING "VSP_CLEAR"
#define TECHLIST_STRING "VSP_TECHLIST"
#define TECHLIST_INDEX_STRING "VSP_TECHLIST_INDEX"
#define REMOVE_STRING "VSP_REMOVE"
#define UPDATE_STRING "VSP_UPDATE"
#define SAVEDATA_STRING "VSP_SAVEDATA"

#define EWE_STRING "VSP_EWE"
#define ECE_STRING "VSP_ECE"
#define I_STRING "VSP_I"
#define TECH_STRING "VSP_TECH"
#define RUNNING_STRING "VSP_RUNNING"
#define FILE_STRING "VSP_FILE"

class BioLogicDriver : public asynPortDriver {

public:
    BioLogicDriver(const char* portName, const char* connection = "USB0");
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

    /**
     * Polls various values from device and updaetes PVs
     */
    void updateValues();
    /**
     * Set the status message PV
     * 
     * @param msg Message to send to PV
     */
    void setStatusMessage(char* msg);
    /**
     * Set the status message PV
     * 
     * @param msg Message to send to PV
     */
    void setStatusMessage(std::string msg);

protected:

#define FIRST_BIOLOGICDRIVER_PARAM BioLogicDriverVersion
    int BioLogicDriverVersion;
#define LAST_BIOLOGICDRIVER_PARAM BioLogicDriverVersion

private:
    /**
     * Array of channels on device
     */
    Channel* channels;
    /**
     * Number of channels on device
     */
    int numChannels;

    /**
     * Parameter handler
     */
    Params* blParams;

    /**
     * Device id
     */
    int deviceID;
    /**
     * Device info received from device
     */
    TDeviceInfos_t deviceInfo;

    // PV handlers

    int idNum;
    int nchanNum;
    int versionNum;
    int techniqueNum;
    int uploadNum;
    int chanNum;
    int statusNum;
    int startNum;
    int addNum;
    int clearNum;
    int techlistNum;
    int techlistIndexNum;
    int removeNum;
    int updateNum;

    /**
     * Current technique being editted by parameter handler
     */
    std::string currentTechnique;
    /**
     * Current channel being interacted with
     */
    int currentChannel = 0;
    /**
     * Current index in technique list being editted
     */
    int currentTechlistIndex = 0;
    
    /**
     * 
     */
    vector<Technique> techniqueList;

    void createChannel(int id, Channel &channel);
    void setupConnection(const char* connection);
    void setupInitialValues();
    void updateListString();
};

#define NUM_BIOLOGICDRIVER_PARAMS ((int)(&LAST_BIOLOGICDRIVER_PARAM - &FIRST_BIOLOGICDRIVER_PARAM + 1))
#endif