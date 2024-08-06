#!../../bin/win32-x86-static/BioLogicDriverApp

errlogInit(20000)
< envPaths

dbLoadDatabase("$(TOP)/dbd/BioLogicDriverApp.dbd")

BioLogicDriverApp_registerRecordDeviceDriver(pdbbase)

# Define asyn port name
epicsEnvSet("PORT", "DRV1")
epicsEnvSet("PREFIX", "DEV:VSP")

#switch which of these is commented in order to switch between connecting over USB or ethernet
BioLogicDriverConfig("$(PORT)", "USB")
#BioLogicDriverConfig("$(PORT)", "USB")


#asynSetTraceMask("$(PORT)", -1, 0x0)
#asynSetTraceMask("$(PORT)", -1, 0x1)

# Enables both log and error messages
asynSetTraceMask("$(PORT)", -1, 0x9)
#asynSetTraceMask("$(PORT)", -1, 0xF)
#asynSetTraceMask("$(PORT)", -1, 0x11)
#asynSetTraceMask("$(PORT)", -1, 0xFF)
#asynSetTraceIOMask("$(PORT)", -1, 0x0)
#asynSetTraceIOMask("$(PORT)", -1, 0x2)

dbLoadRecords("$(BIOLOGICDRIVER)/db/BioLogicDriver.template", "PREFIX=$(PREFIX), PORT=$(PORT), ADDR=0, TIMEOUT=1")
dbLoadRecords("$(ASYN)/db/asynRecord.db", "P=$(PREFIX), R=:AsynIO, PORT=$(PORT), ADDR=0, TIMEOUT=1, OMAX=0, IMAX=0")
dbLoadRecords("$(DEVIOCSTATS)/db/iocAdminSoft.db", "IOC=$(PREFIX)")

iocInit()
