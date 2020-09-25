// Header
#include "Logic.h"
// Includes
#include "Controller.h"
#include "CurrentControl.h"
#include "Board.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Interrupts.h"
#include "Delay.h"

// Forward functions
void LOGIC_ClearDataArrays()
{
	uint16_t i;
	
	for(i = 0; i < VALUES_OUT_SIZE; ++i)
	{
		CONTROL_ValuesDUTVoltage[i] = 0;
		CONTROL_ValuesDUTCurrent[i] = 0;
	}
}
//---------------------

void LOGIC_PulseConfig()
{
	for(int i = 0; i < PULSE_BUFFER_SIZE; i++)
	{
		if(i < PULSE_LITE_START)
		{
			PulseDataBuffer[i] = CurrentAmplitude * ((i) / PULSE_LITE_START);
		}
		else
			PulseDataBuffer[i] = CurrentAmplitude;
	}
}
//---------------------

void LOGIC_CacheVariables()
{
	CurrentAmplitude = CC_CurrentSetup((float)DataTable[REG_CURRENT_SETPOINT]);
	VoltageAmplitude = (float)DataTable[REG_VOLTAGE_SETPOINT];

	PropKoef = (float)DataTable[REG_CTRL_P_COEF] / 1000;
	IntKoef = (float)DataTable[REG_CTRL_I_COEF] / 1000;
	
	ShuntResistance = CC_EnableShuntRes(CurrentAmplitude);
	
	Pulse2PulsePause = (uint32_t)CurrentAmplitude * DataTable[REG_MAX_PULSE_TO_PULSE_PAUSE] / BLOCK_MAX_CURRENT;
	
	Qi = 0;
	PulseCounter = 0;
}
//---------------------

void LOGIC_EnableVoltageChannel(float Voltage)
{
	if(Voltage <= V_RANGE_30MV)
	{
		LL_EnableAmp30mV(true);
	}
	else if(Voltage <= V_RANGE_250MV)
	{
		LL_EnableAmp250mV(true);
	}
	else if(Voltage <= V_RANGE_1500MV)
	{
		LL_EnableAmp1500mV(true);
	}
	else
	{
		LL_EnableAmp11V(true);
	}
}
//---------------------

void LOGIC_FillEndPoint(float Voltage, float Current, float Error, uint16_t DataToDAC)
{
	CONTROL_AvrVoltageRaw[PulseCounter] = Voltage;
	CONTROL_AvrCurrentRaw[PulseCounter] = Current;
	CONTROL_RegulatorErrorRaw[PulseCounter] = Error;
	CONTROL_OutDataRaw[PulseCounter] = DataToDAC;
}
//---------------------
