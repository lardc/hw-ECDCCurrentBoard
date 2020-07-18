#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

void MEASURE_ConvertRawArray(uint16_t* RawArray, uint16_t* OutputArray, uint16_t DataLength, uint16_t RegisterOffSet,
		uint16_t RegistergGain, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2);
uint16_t MEASURE_ReadCurrent2A();
uint16_t MEASURE_ReadCurrent270A();
uint16_t MEASURE_ReadVoltage250MV();
uint16_t MEASURE_ReadVoltage11V();
uint16_t MEASURE_GetBatteryVoltage();

#endif // __MEASUREMENT_H
