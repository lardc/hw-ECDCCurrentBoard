#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"
#include "Board.h"

// Functions
//
void LL_ToggleLED();
void LL_ExternalLED(bool State);
void LL_CTRL_VDUTAmp11V(bool State);
void LL_CTRL_VDUTAmp1500mV(bool State);
void LL_CTRL_VDUTAmp250mV(bool State);
void LL_CTRL_VDUTAmp30mV(bool State);
void LL_EN_Range20mA(bool State);
void LL_EN_Range200mA(bool State);
void LL_EN_Range2A(bool State);
void LL_EN_Range20A(bool State);
void LL_EN_Range270A(bool State);
void LL_BatteryDischarge(bool State);
void LL_PSBoardOff(bool State);
void LL_ForceSYNC1(bool State);
void LL_ForceSYNC2(bool State);
void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx);
void LL_OutputRegister_Write(uint16_t Data);

#endif //__LOWLEVEL_H
