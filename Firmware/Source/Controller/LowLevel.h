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
void LL_EnableAmp1500MV(bool State);
void LL_EnableAmp250MV(bool State);
void LL_EnableAmp30MV(bool State);
void LL_EnableRange20MA(bool State);
void LL_EnableRange200MA(bool State);
void LL_EnableRange2A(bool State);
void LL_EnableRange20A(bool State);
void LL_EnableRange270A(bool State);
void LL_DischargeBattery(bool State);
void LL_SwitchPsBoard(bool State);
void LL_ForceSync1(bool State);
void LL_ForceSync2(bool State);
void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx);
void LL_WriteOutReg(uint16_t Data);

#endif //__LOWLEVEL_H
