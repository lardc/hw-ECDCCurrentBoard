// Header
#include "DebugActions.h"

// Include
#include "CurrentControl.h"
#include "Measurement.h"
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Functions
//
void DBGACT_ImpulseExternalLed()
{
	LL_ExternalLed(true);
	DELAY_US(1000);
	LL_ExternalLed(false);
}
//-----------------------------

void DBGACT_SwitchAmp11V()
{
	LL_EnableAmp11V(true);
	DELAY_US(1000);
	LL_EnableAmp11V(false);
}
//-----------------------------

void DBGACT_SwitchAmp1500MV()
{
	LL_EnableAmp1500MV(true);
	DELAY_US(1000);
	LL_EnableAmp1500MV(false);
}
//-----------------------------

void DBGACT_SwitchAmp250MV()
{
	LL_EnableAmp250MV(true);
	DELAY_US(1000);
	LL_EnableAmp250MV(false);
}
//-----------------------------

void DBGACT_SwitchAmp30MV()
{
	LL_EnableAmp30MV(true);
	DELAY_US(1000);
	LL_EnableAmp30MV(false);
}
//-----------------------------

void DBGACT_SwitchRange20MA()
{
	LL_EnableRange20MA(true);
	DELAY_US(1000);
	LL_EnableRange20MA(false);
}
//-----------------------------

void DBGACT_SwitchRange200MA()
{
	LL_EnableRange200MA(true);
	DELAY_US(1000);
	LL_EnableRange200MA(false);
}
//-----------------------------

void DBGACT_SwitchRange2A()
{
	LL_EnableRange2A(true);
	DELAY_US(1000);
	LL_EnableRange2A(false);
}
//-----------------------------

void DBGACT_SwitchRange20A()
{
	LL_EnableRange20A(true);
	DELAY_US(1000);
	LL_EnableRange20A(false);
}
//-----------------------------

void DBGACT_SwitchRange270A()
{
	LL_EnableRange270A(true);
	DELAY_US(1000);
	LL_EnableRange270A(false);
}
//-----------------------------

void DBGACT_SwitchBatteryDischarge()
{
	LL_DischargeBattery(true);
	DELAY_US(1000);
	LL_DischargeBattery(false);
}
//-----------------------------

void DBGACT_SwitchPsBoard()
{
	LL_SwitchPsBoard(true);
	DELAY_US(1000);
	LL_SwitchPsBoard(false);
}
//-----------------------------

void DBGACT_ImpulseSync1()
{
	LL_ForceSync1(true);
	DELAY_US(1000);
	LL_ForceSync1(false);
}
//-----------------------------

void DBGACT_ImpulseSync2()
{
	LL_ForceSync2(true);
	DELAY_US(1000);
	LL_ForceSync2(false);
}
//-----------------------------

bool DBGACT_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
{
	switch (ActionID)
	{
		case ACT_DBG_IMPULSE_LED:
			{
				DBGACT_ImpulseExternalLed();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP11V:
			{
				DBGACT_SwitchAmp11V();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP1500MV:
			{
				DBGACT_SwitchAmp1500MV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP250MV:
			{
				DBGACT_SwitchAmp250MV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP30MV:
			{
				DBGACT_SwitchAmp30MV();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG20MA:
			{
				DBGACT_SwitchRange20MA();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG200MA:
			{
				DBGACT_SwitchRange200MA();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG2A:
			{
				DBGACT_SwitchRange2A();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG20A:
			{
				DBGACT_SwitchRange20A();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG270A:
			{
				DBGACT_SwitchRange270A();
			}
			break;
			
		case ACT_DBG_ENABLE_DISCHARGE:
			{
				DBGACT_SwitchBatteryDischarge();
			}
			break;
			
		case ACT_DBG_ENABLE_PSBOARD:
			{
				DBGACT_SwitchPsBoard();
			}
			break;
			
		case ACT_DBG_IMPULSE_SYNC1:
			{
				DBGACT_ImpulseSync1();
			}
			break;
			
		case ACT_DBG_IMPULSE_SYNC2:
			{
				DBGACT_ImpulseSync2();
			}
			break;
			
		case ACT_DBG_SEND_DATA_TO_DAC:
			{
				CC_SetCurrent(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_SEND_DATA_TO_REG:
			{
				LL_WriteOutReg(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_MEASURE_ID2A:
			{
				DataTable[REG_DBG_DATA] = MEASURE_ReadCurrent2A();
			}
			break;
			
		case ACT_DBG_MEASURE_ID270A:
			{
				DataTable[REG_DBG_DATA] = MEASURE_ReadCurrent270A();
			}
			break;
			
		case ACT_DBG_MEASURE_VD250MV:
			{
				DataTable[REG_DBG_DATA] = MEASURE_ReadVoltage250MV();
			}
			break;
			
		case ACT_DBG_MEASURE_VD11V:
			{
				DataTable[REG_DBG_DATA] = MEASURE_ReadVoltage11V();
			}
			break;
			
		default:
			return false;
	}
	
	return true;
}
//-----------------------------

