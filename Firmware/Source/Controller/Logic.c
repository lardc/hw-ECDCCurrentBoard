// Header
#include "Logic.h"
// Includes
#include "Controller.h"
#include "CurrentControl.h"
#include "Measurement.h"
#include "Board.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Interrupts.h"
#include "Delay.h"

// Variables
//
volatile float PulseDataBuffer[PULSE_BUFFER_SIZE];
volatile float CurrentAmplitude = 0, CurrentAmplifier = 0, ShuntResistance = 0, VoltageAmplitude = 0, VoltageAmplifier =
		0;

// Forward functions
void LOGIC_ClearDataArrays()
{
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	AverageVdut = 0;
	AverageIdut = 0;

	PulseToPulsePause = 0;
	
	Qi = 0;
	PulseCounter = 0;
	
	CONTROL_ValuesCounter = 0;

	for(int i = 0; i < VALUES_OUT_SIZE; ++i)
	{
		CONTROL_ValuesDUTVoltage[i] = 0;
		CONTROL_ValuesDUTCurrent[i] = 0;
		CONTROL_DUTCurrentRaw[i] = 0;
		CONTROL_DUTVoltageRaw[i] = 0;
	}
	
	for(int i = 0; i < PULSE_BUFFER_SIZE; i++)
	{
		PulseDataBuffer[i] = 0;
	}
	
}
//---------------------

void LOGIC_PulseConfig()
{
	for(int i = 0; i < PULSE_BUFFER_SIZE; i++)
	{
		if(i < PULSE_LITE_START)
		{
			PulseDataBuffer[i] = CurrentAmplitude * ((float)i / PULSE_LITE_START);
		}
		else
			PulseDataBuffer[i] = CurrentAmplitude;
	}
}
//---------------------

void LOGIC_CacheVariables()
{
	uint32_t Current;
	
	Current = ((uint32_t)(DataTable[REG_CURRENT_SETPOINT_HIGH]) << 16) | DataTable[REG_CURRENT_SETPOINT_LOW];
	
	CurrentAmplitude = CC_CurrentSetup((float)Current);
	VoltageAmplitude = (float)((uint32_t)(DataTable[REG_VOLTAGE_DUT_LIM_HIGH] << 16)
			| DataTable[REG_VOLTAGE_DUT_LIM_LOW]);
	
	PropKoef = (float)DataTable[REG_CTRL_P_COEF] / 1000;
	IntKoef = (float)DataTable[REG_CTRL_I_COEF] / 1000;
	
	ShuntResistance = CC_EnableShuntRes(CurrentAmplitude);
	
	PulseToPulsePause = ((CurrentAmplitude / BLOCK_MAX_CURRENT) * ((float)DataTable[REG_MAX_PULSE_TO_PULSE_PAUSE]) + 1000);
}
//---------------------

void LOGIC_EnableVoltageChannel(float Voltage)
{
	LL_EnableAmp30mV(false);
	LL_EnableAmp250mV(false);
	LL_EnableAmp1500mV(false);
	LL_EnableAmp11V(false);
	
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
void LOGIC_OffAllRelay()
{
	LL_EnableRange20mA(false);
	LL_EnableRange200mA(false);
	LL_EnableRange2A(false);
	LL_EnableRange20A(false);
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
	DELAY_MS(10);
	LL_DisableRange270A(true);
	DELAY_MS(10);
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
}

void LOGIC_FillEndPoint(float Voltage, float Current, float Error, float DataToDAC)
{
	CONTROL_ValuesCounter = PulseCounter;

	CONTROL_AvrVoltageRaw[CONTROL_ValuesCounter] = (Int16U)(Voltage / 1000);
	CONTROL_AvrCurrentRaw[CONTROL_ValuesCounter] = (Int16U)(Current / 1000);
	CONTROL_RegulatorErrorRaw[CONTROL_ValuesCounter] = (Int16U)(Error);
	CONTROL_OutDataRaw[CONTROL_ValuesCounter] = (Int16U)(DataToDAC / 1000);
}
//---------------------
