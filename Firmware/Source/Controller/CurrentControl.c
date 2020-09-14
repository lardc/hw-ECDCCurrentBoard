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
	uint16_t Data = (uint32_t)Current & ~DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC1);
	DELAY_US(15000);
	LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax20A(float Current)
{
	uint16_t Data = (uint32_t)Current | DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC1);
	DELAY_US(15000);
	LL_WriteDACx(((uint16_t)END_CURRENT_PULSE | DAC_CHANNEL_B), GPIO_LDAC1);
}
//---------------------

void CC_SetCurrentMax270A(float Current)
{
	uint16_t Data = (uint32_t)Current & ~DAC_CHANNEL_B;
	LL_WriteDACx(Data, GPIO_LDAC2);
	DELAY_US(15000);
	LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC2);
}
//---------------------

void CC_SetCurrentPulse(float Current)
{
	uint16_t Data;
	
	if(Current <= I_RANGE_2A)
	{
		Data = (uint32_t)Current & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
		DELAY_US(10000);
		LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC1);
	}
	
	else if(Current <= I_RANGE_20A)
	{
		Data = (uint32_t)Current | DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC1);
		DELAY_US(10000);
		LL_WriteDACx(((uint16_t)END_CURRENT_PULSE | DAC_CHANNEL_B), GPIO_LDAC1);
	}
	else
	{
		Data = (uint32_t)Current & ~DAC_CHANNEL_B;
		LL_WriteDACx(Data, GPIO_LDAC2);
		DELAY_US(10000);
		LL_WriteDACx((uint16_t)END_CURRENT_PULSE, GPIO_LDAC2);
	}
}
//---------------------

float CC_EnableCurrentChannel(float Current)
{
	float ShuntRes;
	
	if(Current <= I_RANGE_20MA)
	{
		LL_EnableRange20mA(true);
		LL_WriteOutReg(I_ANALOG_2A);
		ShuntRes = (float) I_SHUNT_20MA;
	}
	else if(Current <= I_RANGE_200MA)
	{
		LL_EnableRange200mA(true);
		LL_WriteOutReg(I_ANALOG_2A);
		ShuntRes = (float) I_SHUNT_200MA;
	}
	else if(Current <= I_RANGE_2A)
	{
		LL_EnableRange2A(true);
		LL_WriteOutReg(I_ANALOG_2A);
		ShuntRes = (float) I_SHUNT_200MA;
	}
	else if(Current <= I_RANGE_20A)
	{
		LL_EnableRange20A(true);
		LL_WriteOutReg(I_ANALOG_20A);
		ShuntRes = (float) I_SHUNT_20A;
	}
	else
	{
		LL_EnableRange270A(true);
		LL_WriteOutReg(I_ANALOG_270A);
		ShuntRes = (float) I_SHUNT_270A;
	}
	
	return ShuntRes;
}
//---------------------

