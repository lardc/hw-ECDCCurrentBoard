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

// Forward function definitions
void DBGACT_ImpulseExternalLed();
void DBGACT_SwitchAmp11V();
void DBGACT_SwitchAmp1500mV();
void DBGACT_SwitchAmp250mV();
void DBGACT_SwitchAmp30mV();
void DBGACT_SwitchRange20mA();
void DBGACT_SwitchRange200mA();
void DBGACT_SwitchRange2A();
void DBGACT_SwitchRange20A();
void DBGACT_TurnOnRange270A();
void DBGACT_TurnOffRange270A();
void DBGACT_SwitchBatteryDischarge();
void DBGACT_SwitchPsBoard();
void DBGACT_ImpulseSync1();
void DBGACT_ImpulseSync2();

// Functions
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

void DBGACT_SwitchAmp1500mV()
{
	LL_EnableAmp1500mV(true);
	DELAY_US(1000);
	LL_EnableAmp1500mV(false);
}
//-----------------------------

void DBGACT_SwitchAmp250mV()
{
	LL_EnableAmp250mV(true);
	DELAY_US(1000);
	LL_EnableAmp250mV(false);
}
//-----------------------------

void DBGACT_SwitchAmp30mV()
{
	LL_EnableAmp30mV(true);
	DELAY_US(1000);
	LL_EnableAmp30mV(false);
}
//-----------------------------

void DBGACT_SwitchRange20mA()
{
	LL_EnableRange20mA(true);
	DELAY_US(1000);
	LL_EnableRange20mA(false);
}
//-----------------------------

void DBGACT_SwitchRange200mA()
{
	LL_EnableRange200mA(true);
	DELAY_US(1000);
	LL_EnableRange200mA(false);
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

void DBGACT_TurnOnRange270A()
{
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
	DELAY_MS(15);
	LL_EnableRange270A(true);
	DELAY_MS(15);
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
}
//-----------------------------

void DBGACT_TurnOffRange270A()
{
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
	DELAY_MS(15);
	LL_DisableRange270A(true);
	DELAY_MS(15);
	LL_EnableRange270A(false);
	LL_DisableRange270A(false);
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
	float Data = DataTable[REG_DBG_DATA];
	float Current;
	
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
				DBGACT_SwitchAmp1500mV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP250MV:
			{
				DBGACT_SwitchAmp250mV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP30MV:
			{
				DBGACT_SwitchAmp30mV();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG20MA:
			{
				DBGACT_SwitchRange20mA();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG200MA:
			{
				DBGACT_SwitchRange200mA();
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
			
		case ACT_DBG_TURNON_RNG270A:
			{
				DBGACT_TurnOnRange270A();
			}
			break;
			
		case ACT_DBG_TURNOFF_RNG270A:
			{
				DBGACT_TurnOffRange270A();
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
			
		case ACT_DBG_SET_CURRENT_MAX_2A:
			{
				CC_SetCurrentMax2A(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_SET_CURRENT_MAX_20A:
			{
				CC_SetCurrentMax20A(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_SET_CURRENT_MAX_270A:
			{
				CC_SetCurrentMax270A(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_SEND_DATA_TO_REG:
			{
				LL_WriteOutReg(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_IMPULSE_20MA:
			{
				LL_EnableRange20mA(true);
				DELAY_MS(15);
				CC_SetCurrentMax2A(DataTable[REG_DBG_DATA]);
				DELAY_US(1000);
				LL_EnableRange20mA(false);
			}
			break;
			
		case ACT_DBG_IMPULSE_200MA:
			{
				LL_EnableRange200mA(true);
				DELAY_MS(15);
				CC_SetCurrentMax2A(DataTable[REG_DBG_DATA]);
				DELAY_US(1000);
				LL_EnableRange200mA(false);
			}
			break;
			
		case ACT_DBG_IMPULSE_2A:
			{
				LL_EnableRange2A(true);
				DELAY_MS(15);
				Current = CC_ItoDAC(Data);
				CC_SetCurrentMax2A(DataTable[REG_DBG_DATA]);
				DELAY_US(1000);
				LL_EnableRange2A(false);
			}
			break;
			
		case ACT_DBG_IMPULSE_20A:
			{
				LL_EnableRange20A(true);
				DELAY_MS(15);
				Current = CC_ItoDAC(Data);
				CC_SetCurrentMax20A(Current);
				DELAY_US(1000);
				LL_EnableRange20A(false);
			}
			break;
			
		case ACT_DBG_IMPULSE_270A:
			{
				DBGACT_TurnOnRange270A();
				DELAY_MS(15);
				Current = CC_ItoDAC(Data);
				CC_SetCurrentMax270A(Current);
				DELAY_US(1000);
				DBGACT_TurnOffRange270A();
			}
			break;
			
		default:
			return false;
	}
	
	return true;
}
//-----------------------------

