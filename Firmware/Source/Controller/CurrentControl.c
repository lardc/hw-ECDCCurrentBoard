// Header
#include "CurrentControl.h"
// Includes
#include "Board.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Controller.h"
#include "Delay.h"

// Forward functions
uint16_t CC_ItoDAC(float Current)
{
	float K = (float)DataTable[REG_DAC_I_SET_K] / 1000;
	float Offset = (float)((int16_t)DataTable[REG_DAC_I_SET_OFFSET]);
	
	uint32_t result = Current * K + Offset;
	return (result > DAC_RESOLUTION) ? DAC_RESOLUTION : result;
}
//---------------------

float CC_CurrentSetup(float Current)
{
	Current = DataTable[REG_CURRENT_SETPOINT];
	if(Current > BLOCK_MAX_CURRENT)
	{
		if(DataTable[REG_PROBLEM] == PROBLEM_NONE)
			DataTable[REG_PROBLEM] = PROBLEM_CURRENT_TO_HIGH;
		
		return BLOCK_MAX_CURRENT;
	}
	else
		return Current;
}
//---------------------

void CC_SetCurrentMax2A(float Current)
{
	uint16_t Data = (uint32_t)CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC1);
	DELAY_US(15000);
	LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax20A(float Current)
{
	uint16_t Data = (uint32_t)CC_ItoDAC(Current) | DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC1);
	DELAY_US(15000);
	LL_WriteDACx(((uint16_t)END_CURRENT_PULSE | DAC_CHANNEL_B), GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax270A(float Current)
{
	uint16_t Data = (uint32_t)CC_ItoDAC(Current) & ~DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC2);
	DELAY_US(15000);
	LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC2);
}
//---------------------

void CC_SetCurrentPulse(uint16_t OutData, float Current)
{
	uint16_t Data;
	
	if(Current <= I_RANGE_2A)
	{
		Data = (uint32_t)OutData & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
	}
	
	else if(Current <= I_RANGE_20A)
	{
		Data = (uint32_t)OutData | DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
	}
	else
	{
		Data = (uint32_t)OutData & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC2);
	}
}
//---------------------

void CC_EnableCurrentChannel(float Current, float EnableFb)
{
	uint16_t Data;
	
	if(Current <= I_RANGE_20MA)
	{
		LL_EnableRange20mA(true);
		Data = (EnableFb == 0) ? I_ANALOG_2A : (I_ANALOG_2A | I_FB_2A);
		LL_WriteOutReg(Data);
	}
	else if(Current <= I_RANGE_200MA)
	{
		LL_EnableRange200mA(true);
		Data = (EnableFb == 0) ? I_ANALOG_2A : (I_ANALOG_2A | I_FB_2A);
		LL_WriteOutReg(Data);
	}
	else if(Current <= I_RANGE_2A)
	{
		LL_EnableRange2A(true);
		Data = (EnableFb == 0) ? I_ANALOG_2A : (I_ANALOG_2A | I_FB_2A);
		LL_WriteOutReg(I_ANALOG_2A);
	}
	else if(Current <= Data)
	{
		LL_EnableRange20A(true);
		Data = (EnableFb == 0) ? I_ANALOG_20A : (I_ANALOG_20A | I_FB_20A);
		LL_WriteOutReg(I_ANALOG_20A);
	}
	else
	{
		LL_EnableRange270A(true);
		Data = (EnableFb == 0) ? I_ANALOG_270A : (I_ANALOG_270A | I_FB_270A);
		LL_WriteOutReg(Data);
	}
}
//---------------------

float CC_EnableShuntRes(float Current)
{
	float ShuntRes;
	
	if(Current <= I_RANGE_20MA)
	{
		ShuntRes = (float) I_SHUNT_20MA;
	}
	else if(Current <= I_RANGE_200MA)
	{
		ShuntRes = (float) I_SHUNT_200MA;
	}
	else if(Current <= I_RANGE_2A)
	{
		ShuntRes = (float) I_SHUNT_200MA;
	}
	else if(Current <= I_RANGE_20A)
	{
		ShuntRes = (float) I_SHUNT_20A;
	}
	else
	{
		ShuntRes = (float) I_SHUNT_270A;
	}
	
	return ShuntRes;
}
//---------------------

