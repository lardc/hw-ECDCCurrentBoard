#ifndef __MEASUREMENT_H
#define __MEASUREMENT_H

#include "stdinc.h"

void MEASURE_ConvertRawArray(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength,
		  uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2);
void MEASURE_ReadCurrent2A(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength);
void MEASURE_ReadCurrent270A(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength);
void MEASURE_ReadVoltage250mV(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength);
void MEASURE_ReadVoltage11V(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength);
uint16_t MEASURE_GetBatteryVoltage();
void MEASURE_MeasuremenChannel(float Current, float Voltage);
//------------------------------------------------

#endif // __MEASUREMENT_H
