#Makefile at top of application tree
TOP = .
include $(TOP)/configure/CONFIG
DIRS += configure BioLogicDriverApp iocs
BioLogicDriverApp_DEPEND_DIRS   += configure
iocs_DEPEND_DIRS += BioLogicDriverApp
include $(TOP)/configure/RULES_TOP

uninstall: uninstall_iocs
	uninstall_iocs:
		$(MAKE) -C iocs uninstall
.PHONY: uninstall uninstall_iocs

realuninstall: realuninstall_iocs
	realuninstall_iocs:
		$(MAKE) -C iocs realuninstall
.PHONY: realuninstall realuninstall_iocs