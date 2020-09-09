// Header
#include "CurrentControl.h"
// Includes
#include "Board.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"

// Forward functions
uint16_t CC_ItoDAC(float Current)
{
	float K = (float)DataTable[REG_DAC_I_SET_K] / 1000;
	float Offset = (float)((int16_t)DataTable[REG_DAC_I_SET_OFFSET]);
	
	uint32_t result = Current * K + Offset;
	return (result > DAC_RESOLUTION) ? DAC_RESOLUTION : result;
}
//---------------------

void CC_SetCurrentMax2A(float Current)
{
		uint16_t Data = CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
		DELAY_US(15000);
		LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax20A(float Current)
{
		uint16_t Data = CC_ItoDAC(Current) | DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
		DELAY_US(15000);
		LL_WriteDACx(((uint16_t)END_CURRENT_PULSE | DAC_CHANNEL_B), GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax270A(float Current)
{
		uint16_t Data = CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC2);
		DELAY_US(15000);
		LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC2);
}
//---------------------

void CC_EnableCurrentChannel(float Current)
{
	if(Current <= I_RANGE_20MA)
	{
		LL_EnableRange20mA(TRUE);
	}
	else if(Current <= I_RANGE_200MA)
	{
		LL_EnableRange200mA(TRUE);
	}
	else if(Current <= I_RANGE_2A)
	{
		LL_EnableRange2A(TRUE);
	}
	else if(Current <= I_RANGE_20A)
	{
		LL_EnableRange20A(TRUE);
	}
	else
	{
		LL_EnableRange270A(TRUE);
	}
}
