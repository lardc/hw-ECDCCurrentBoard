#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"
#include "Board.h"

// Functions
//
void LL_ToggleLed();
void LL_ExternalLed(bool State);
void LL_EnableAmp11V(bool State);
void LL_EnableAmp1500mV(bool State);
void LL_EnableAmp250mV(bool State);
void LL_EnableAmp30mV(bool State);
void LL_EnableRange20mA(bool State);
void LL_EnableRange200mA(bool State);
void LL_EnableRange2A(bool State);
void LL_EnableRange20A(bool State);
void LL_EnableRange270A(bool State);
void LL_DisableRange270A(bool State);
void LL_DischargeBattery(bool State);
void LL_SwitchPsBoard(bool State);
void LL_ForceSync1(bool State);
void LL_ForceSync2(bool State);
bool LL_GetSync1State();
bool LL_GetSync2State();
void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx);
void LL_WriteOutReg(uint16_t Data);

#endif //__LOWLEVEL_H
