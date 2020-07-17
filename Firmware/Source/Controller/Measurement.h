#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

void MEASURE_ConvertRawArray(uint16_t* RawArray, uint16_t* OutputArray, uint16_t DataLength, uint16_t RegisterOffSet,
		uint16_t RegistergGain, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2);
uint16_t MEASURE_ReadCurrent();
uint16_t MEASURE_ReadVoltage();
uint16_t MEASURE_GetBatteryVoltage();

#endif // __MEASUREMENT_H
