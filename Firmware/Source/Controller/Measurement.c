#include "Measurement.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Global.h"
#include "ZwADC.h"

void MEASURE_ConvertRawArray(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength,
		uint16_t RegisterOffset, uint16_t RegisterK, uint16_t RegisterP0, uint16_t RegisterP1, uint16_t RegisterP2)
{
	uint16_t i;
	float tmp;
	
	float Offset = (float)((int16_t)DataTable[RegisterOffset]);
	float K = (float)DataTable[RegisterK] / 1000;
	//
	float P0 = (float)((int16_t)DataTable[RegisterP0]);
	float P1 = (float)DataTable[RegisterP1] / 1000;
	float P2 = (float)((int16_t)DataTable[RegisterP2]) / 1e6;
	
	for(i = 0; i < DataLength; ++i)
	{
		tmp = ((float)InputArray[i] - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
		tmp = tmp * tmp * P2 + tmp * P1 + P0;
		OutputArray[i] = (tmp > 0) ? tmp : 0;
	}
}
//---------------------

void MEASURE_ReadCurrent2A(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength)
{
	MEASURE_ConvertRawArray(InputArray, OutputArray, DataLength, REG_ADC_ID2A_OFFSET, REG_ADC_ID2A_K,
	REG_ADC_ID2A_FINE_P0, REG_ADC_ID2A_FINE_P1, REG_ADC_ID2A_FINE_P2);
}

void MEASURE_ReadCurrent270A(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength)
{
	MEASURE_ConvertRawArray(InputArray, OutputArray, DataLength, REG_ADC_ID270A_OFFSET, REG_ADC_ID270A_K,
	REG_ADC_ID270A_FINE_P0, REG_ADC_ID270A_FINE_P1, REG_ADC_ID270A_FINE_P2);
}

void MEASURE_ReadVoltage250mV(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength)
{
	MEASURE_ConvertRawArray(InputArray, OutputArray, DataLength, REG_ADC_VD250MV_OFFSET, REG_ADC_VD250MV_K,
	REG_ADC_VD250MV_FINE_P0, REG_ADC_VD250MV_FINE_P1, REG_ADC_VD250MV_FINE_P2);
}

void MEASURE_ReadVoltage11V(volatile uint16_t *InputArray, float *OutputArray, uint16_t DataLength)
{
	MEASURE_ConvertRawArray(InputArray, OutputArray, DataLength, REG_ADC_VD11V_OFFSET, REG_ADC_VD11V_K,
	REG_ADC_VD11V_FINE_P0, REG_ADC_VD11V_FINE_P1, REG_ADC_VD11V_FINE_P2);
}

uint16_t MEASURE_GetBatteryVoltage()
{
	float Offset = (float)((int16_t)DataTable[REG_ADC_VBAT_OFFSET]);
	float K = (float)DataTable[REG_ADC_VBAT_K] / 1000;
	float result = ((float)ADC_Measure(ADC3, VBAT_ADC3_CH) - Offset) * ADC_REF_VOLTAGE / ADC_RESOLUTION * K;
	
	return (result > 0) ? result : 0;
}
//------------------------------------------------

void MEASURE_MeasuremenChannel(float Current, float Voltage)
{
	if(Current <= I_RANGE_2A)
	{
		MEASURE_ReadCurrent2A(CONTROL_DUTCurrentRaw, (float *)CONTROL_ValuesDUTCurrent, VALUES_OUT_SIZE);
	}
	else
	{
		MEASURE_ReadCurrent270A(CONTROL_DUTCurrentRaw, (float *)CONTROL_ValuesDUTCurrent, VALUES_OUT_SIZE);
	}
	
	if(Voltage <= V_RANGE_250MV)
	{
		MEASURE_ReadVoltage250mV(CONTROL_DUTVoltageRaw, (float *)CONTROL_ValuesDUTVoltage, VALUES_OUT_SIZE);
	}
	else
	{
		MEASURE_ReadVoltage11V(CONTROL_DUTVoltageRaw, (float *)CONTROL_ValuesDUTVoltage, VALUES_OUT_SIZE);
	}
}
//-----------------------------------------------
