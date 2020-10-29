#ifndef __LOGIC_H
#define __LOGIC_H

// Include
#include "stdinc.h"

// Variables
extern volatile float PulseDataBuffer[];
extern volatile float CurrentAmplitude, CurrentAmplifier, ShuntResistance, VoltageAmplitude, VoltageAmplifier;

// Functions
void LOGIC_ClearDataArrays();
void LOGIC_PulseConfig();
void LOGIC_CacheVariables();
void LOGIC_EnableVoltageChannel(float Voltage);
void LOGIC_OffAllRelay();
void LOGIC_FillEndPoint(float Voltage, float Current, float Error, float DataToDAC);

#endif // __LOGIC_H
