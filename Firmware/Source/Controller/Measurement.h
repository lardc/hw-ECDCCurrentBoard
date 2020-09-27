#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

void MEASURE_ConvertRawArray(volatile uint16_t *InputArray, volatile Int16U* OutputArray, uint16_t DataLength,
		uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2);
void MEASURE_ReadDutCurrent(float Current);
void MEASURE_ReadDutVoltage(float Voltage);
uint16_t MEASURE_GetBatteryVoltage();

//------------------------------------------------

#endif // __MEASUREMENT_H
