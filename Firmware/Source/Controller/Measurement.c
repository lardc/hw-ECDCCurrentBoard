#include "Measurement.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

// Variables
//
volatile float CONTROL_ValuesDUTVoltage[VALUES_OUT_SIZE];
volatile float CONTROL_ValuesDUTCurrent[VALUES_OUT_SIZE];
volatile uint16_t CONTROL_DUTCurrentRaw[VALUES_OUT_SIZE];
volatile uint16_t CONTROL_DUTVoltageRaw[VALUES_OUT_SIZE];

void MEASURE_ConvertRawArray(volatile uint16_t *InputArray, volatile float* OutputArray, uint16_t DataLength,
		uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2)
{
	uint16_t i;
	float tmp;
	
	float Offset = (float)((int16_t)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 1000;
	float P0 = (float)((int16_t)DataTable[RegisterP0]);
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P2 = (float)((int16_t)DataTable[RegisterP2]) / 1e6;
	
	for(i = 0; i < DataLength; ++i)
	{
		tmp = ((float)InputArray[i] * (ADC_REF_VOLTAGE / ADC_RESOLUTION) + Offset)  * K;
		tmp = tmp * tmp * P2 + tmp * P1 + P0;
		OutputArray[i] = (tmp > 0) ? tmp : 0;
	}
}
//---------------------

void MEASURE_ReadDutCurrent(float Current)
{
	if(Current <= I_RANGE_20MA)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTCurrentRaw[0], &CONTROL_ValuesDUTCurrent[0], VALUES_OUT_SIZE,
		REG_ADC_ID20MA_OFFSET, REG_ADC_ID20MA_K, REG_ADC_ID20MA_FINE_P0, REG_ADC_ID20MA_FINE_P1,
		REG_ADC_ID20MA_FINE_P2);
	}
	else if(Current <= I_RANGE_200MA)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTCurrentRaw[0], &CONTROL_ValuesDUTCurrent[0], VALUES_OUT_SIZE,
		REG_ADC_ID200MA_OFFSET, REG_ADC_ID200MA_K, REG_ADC_ID200MA_FINE_P0, REG_ADC_ID200MA_FINE_P1,
		REG_ADC_ID200MA_FINE_P2);
	}
	else if(Current <= I_RANGE_2A)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTCurrentRaw[0], &CONTROL_ValuesDUTCurrent[0], VALUES_OUT_SIZE,
		REG_ADC_ID2A_OFFSET, REG_ADC_ID2A_K, REG_ADC_ID2A_FINE_P0, REG_ADC_ID2A_FINE_P1, REG_ADC_ID2A_FINE_P2);
	}
	else if(Current <= I_RANGE_20A)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTCurrentRaw[0], &CONTROL_ValuesDUTCurrent[0], VALUES_OUT_SIZE,
		REG_ADC_ID20A_OFFSET, REG_ADC_ID20A_K, REG_ADC_ID20A_FINE_P0, REG_ADC_ID20A_FINE_P1, REG_ADC_ID20A_FINE_P2);
	}
	else
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTCurrentRaw[0], &CONTROL_ValuesDUTCurrent[0], VALUES_OUT_SIZE,
		REG_ADC_ID270A_OFFSET, REG_ADC_ID270A_K, REG_ADC_ID270A_FINE_P0, REG_ADC_ID270A_FINE_P1,
		REG_ADC_ID270A_FINE_P2);
	}
}
//---------------------

void MEASURE_ReadDutVoltage(float Voltage)
{
	if(Voltage <= V_RANGE_10MV)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTVoltageRaw[0], &CONTROL_ValuesDUTVoltage[0], VALUES_OUT_SIZE,
		REG_ADC_VD10MV_OFFSET, REG_ADC_VD10MV_K, REG_ADC_VD10MV_FINE_P0, REG_ADC_VD10MV_FINE_P1,
		REG_ADC_VD10MV_FINE_P2);
	}
	else if(Voltage <= V_RANGE_30MV)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTVoltageRaw[0], &CONTROL_ValuesDUTVoltage[0], VALUES_OUT_SIZE,
		REG_ADC_VD30MV_OFFSET, REG_ADC_VD30MV_K, REG_ADC_VD30MV_FINE_P0, REG_ADC_VD30MV_FINE_P1,
		REG_ADC_VD30MV_FINE_P2);
	}
	else if(Voltage <= V_RANGE_250MV)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTVoltageRaw[0], &CONTROL_ValuesDUTVoltage[0], VALUES_OUT_SIZE,
		REG_ADC_VD250MV_OFFSET, REG_ADC_VD250MV_K, REG_ADC_VD250MV_FINE_P0, REG_ADC_VD250MV_FINE_P1,
		REG_ADC_VD250MV_FINE_P2);
	}
	else if(Voltage <= V_RANGE_1500MV)
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTVoltageRaw[0], &CONTROL_ValuesDUTVoltage[0], VALUES_OUT_SIZE,
		REG_ADC_VD1500MV_OFFSET, REG_ADC_VD1500MV_K, REG_ADC_VD1500MV_FINE_P0, REG_ADC_VD1500MV_FINE_P1,
		REG_ADC_VD1500MV_FINE_P2);
	}
	else
	{
		MEASURE_ConvertRawArray(&CONTROL_DUTVoltageRaw[0], &CONTROL_ValuesDUTVoltage[0], VALUES_OUT_SIZE,
		REG_ADC_VD11V_OFFSET, REG_ADC_VD11V_K, REG_ADC_VD11V_FINE_P0, REG_ADC_VD11V_FINE_P1, REG_ADC_VD11V_FINE_P2);
	}
	
}
//---------------------

uint16_t MEASURE_GetBatteryVoltage()
{
	float Offset = (float)((int16_t)DataTable[REG_ADC_VBAT_OFFSET]);
	float K = (float)DataTable[REG_ADC_VBAT_K] / 1000;
	float result = (((float)ADC_Measure(ADC3, VBAT_ADC3_CH)) * ((ADC_REF_VOLTAGE / 1000)/ ADC_RESOLUTION) + Offset) * K;
	
	return (result > 0) ? result : 0;
}
//------------------------------------------------
