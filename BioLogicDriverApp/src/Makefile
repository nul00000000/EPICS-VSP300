TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#

LIBRARY_IOC += BioLogicDriver

INC += BioLogicDriver.hpp
INC += params.h
INC += channel.h
INC += technique.h
INC += filemanager.h
#INC += $(ECLAB)/BLFunctions.h
#INC += $(ECLAB)/BLStructs.h

LIB_SRCS += technique.cpp
LIB_SRCS += params.cpp
LIB_SRCS += filemanager.cpp
LIB_SRCS += BioLogicDriver.cpp

DBD += BioLogicDriverSupport.dbd


# #=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
