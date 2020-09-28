#ifndef __LOGIC_H
#define __LOGIC_H

// Include
#include "stdinc.h"

// Functions
void LOGIC_ClearDataArrays();
void LOGIC_PulseConfig();
void LOGIC_CacheVariables();
void LOGIC_EnableVoltageChannel(float Voltage);
void LOGIC_FillEndPoint(float Voltage, float Current, float Error, uint16_t DataToDAC);

#endif // __LOGIC_H
