// Header
#include "Logic.h"
// Includes
#include "Controller.h"
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
	for (int i = 0; i < PULSE_BUFFER_SIZE; i++)
	{
		if (i < 10)
		{
			PulseDataBuffer[i] = CurrentAmplitude*(0.1*(i+1));
		}
		else PulseDataBuffer[i] = CurrentAmplitude;
	}
}
//---------------------

void LOGIC_CacheVariables()
{
	PropKoef = (float)DataTable[REG_CTRL_P_COEF]/1000;
	IntKoef = (float)DataTable[REG_CTRL_I_COEF]/1000;

	ShuntResistance = CC_EnableCurrentChannel(CurrentAmplitude);

	Pulse2PulsePause = (uint32_t)CurrentAmplitude*DataTable[REG_MAX_PULSE_TO_PULSE_PAUSE]/BLOCK_MAX_CURRENT;

	Qi = 0;
	PulseCounter = 0;
}


