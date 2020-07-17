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

void CC_SetCurrent(float Current)
{
	if(Current <= I_RANGE_2A)
	{
		uint16_t Data = CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
	}
	else if((Current > I_RANGE_2A) && (Current <= I_RANGE_20A))
	{
		uint16_t Data = CC_ItoDAC(Current) | DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
	}
	else if((Current >= I_RANGE_20A) && (Current <= I_RANGE_270A))
	{
		uint16_t Data = CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC2);
	}
}
//---------------------

void CC_EnableCurrentChannel(float Current)
{
	LL_EnableRange20MA(FALSE);
	LL_EnableRange200MA(FALSE);
	LL_EnableRange2A(FALSE);
	LL_EnableRange20A(FALSE);
	LL_EnableRange270A(FALSE);
	
	if(Current <= I_RANGE_20MA)
	{
		LL_EnableRange20MA(TRUE);
	}
	else if((Current > I_RANGE_20MA) && (Current <= I_RANGE_200MA))
	{
		LL_EnableRange200MA(TRUE);
	}
	else if((Current > I_RANGE_200MA) && (Current <= I_RANGE_2A))
	{
		LL_EnableRange2A(TRUE);
	}
	else if((Current > I_RANGE_2A) && (Current <= I_RANGE_20A))
	{
		LL_EnableRange20A(TRUE);
	}
	else if((Current > I_RANGE_20A) && (Current <= I_RANGE_270A))
	{
		LL_EnableRange270A(TRUE);
	}
}

