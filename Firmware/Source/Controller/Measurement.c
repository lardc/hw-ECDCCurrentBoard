#include "Measurement.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

void MEASURE_ConvertRawArray(uint16_t* RawArray, uint16_t* OutputArray, uint16_t DataLength, uint16_t RegisterOffSet,
		uint16_t RegistergGain, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2)
{
	uint16_t i;
	float tmp;
	
	float Offset = (float)((int16_t)DataTable[RegisterOffSet]);
	float K = (float)DataTable[RegisterGain] / 1000;
	
	float P0 = (float)((int16_t)DataTable[RegisterP0]);
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P2 = (float)((int16_t)DataTable[RegisterP2]) / 1e6;
	
	for(i = 0; i < DataLength; ++i)
	{
		tmp = ((float)RawArray[i] - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
		tmp = tmp * tmp * P2 + tmp * P1 + P0;
		OutputArray[i] = (tmp > 0) ? (uint16_t)tmp : 0;
	}
}
//---------------------

uint16_t MEASURE_ReadCurrent2A()
{
	uint16_t raw, result;
	
	raw = ADC_Measure(ADC2, I_ADC2_CH);
	MEASURE_ConvertRawArray(&raw, &result, 1, REG_ADC_ID2A_OFFSET, REG_ADC_ID2A_K, REG_ADC_ID2A_FINE_P0,
			REG_ADC_ID2A_FINE_P1, REG_ADC_ID2A_FINE_P2);
	
	return result;
}
//---------------------

uint16_t MEASURE_ReadCurrent270A()
{
	uint16_t raw, result;
	
	raw = ADC_Measure(ADC2, I_ADC2_CH);
	MEASURE_ConvertRawArray(&raw, &result, 1, REG_ADC_ID270A_OFFSET, REG_ADC_ID270A_K, REG_ADC_ID270A_FINE_P0,
			REG_ADC_ID270A_FINE_P1, REG_ADC_ID270A_FINE_P2);
	
	return result;
}
//---------------------

uint16_t MEASURE_ReadVoltage250MV()
{
	uint16_t raw, result;
	
	raw = ADC_Measure(ADC1, V_ADC1_CH);
	MEASURE_ConvertRawArray(&raw, &result, 1, REG_ADC_VD250MV_OFFSET, REG_ADC_VD250MV_K, REG_ADC_VD250MV_FINE_P0,
			REG_ADC_VD250MV_FINE_P1, REG_ADC_VD250MV_FINE_P2);
	
	return result;
}
//---------------------

uint16_t MEASURE_ReadVoltage11V()
{
	uint16_t raw, result;
	
	raw = ADC_Measure(ADC1, V_ADC1_CH);
	MEASURE_ConvertRawArray(&raw, &result, 1, REG_ADC_VD11V_OFFSET, REG_ADC_VD11V_K, REG_ADC_VD11V_FINE_P0,
			REG_ADC_VD11V_FINE_P1, REG_ADC_VD11V_FINE_P2);
	
	return result;
}
//---------------------

uint16_t MEASURE_GetBatteryVoltage()
{
	float Offset = (float)((int16_t)DataTable[REG_ADC_VBAT_OFFSET]);
	float K = (float)DataTable[REG_ADC_VBAT_K] / 1000;
	float result = ((float)ADC_Measure(ADC2, VBAT_ADC2_CH) - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
	
	return (result > 0) ? result : 0;
}
//------------------------------------------------
