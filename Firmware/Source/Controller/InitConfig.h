#ifndef __INITCONFIG_H
#define __INITCONFIG_H

#include "stdinc.h"

//Functions
//
#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "Controller.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock();
void INITCFG_ConfigExtInt();
void INITCFG_ConfigIO();
void INITCFG_ConfigCAN();
void INITCFG_ConfigUART();
void INITCFG_ConfigSPI();
void INITCFG_ConfigADC();
void INITCFG_DMAConfig();
void INITCFG_ConfigTimer7();
void INITCFG_ConfigTimer6();
void INITCFG_ConfigWatchDog();
//------------------------------------------------

#endif //__INITCONFIG_H
