// Header
#include "DebugActions.h"

// Include
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

void DBGACT_GenerateWriteToDACx(uint16_t Data, uint16_t LDACx)
{
	if(LDACx == 1)
	{
		LL_WriteDACx(Data, GPIO_LDAC1);
	}
	else if(LDACx == 2)
	{
		LL_WriteDACx(Data, GPIO_LDAC2);
	}
}
//-----------------------------

void DBGACT_MEASURE(uint16_t Data, uint16_t ADC_CHx)
{
	if(ADC_CHx == 1)
	{
		Data = ((uint16_t)ADC_Measure(ADC1, V_ADC1_CH)) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
	else if(ADC_CHx == 2)
	{
		Data = ((uint16_t)ADC_Measure(ADC2, V_ADC1_CH)) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
	else if(ADC_CHx == 3)
	{
		Data = ((uint16_t)ADC_Measure(ADC2, VBAT_ADC2_CH)) * ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
}
//-----------------------------

bool DBGDBGACT_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError)
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
				DBGACT_GenerateCTRL_VDUTAmp11V();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP1500MV:
			{
				DBGACT_GenerateCTRL_VDUTAmp1500mV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP250MV:
			{
				DBGACT_GenerateCTRL_VDUTAmp250mV();
			}
			break;
			
		case ACT_DBG_ENABLE_AMP30MV:
			{
				DBGACT_GenerateCTRL_VDUTAmp30mV();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG20MA:
			{
				DBGACT_GenerateEN_Range20mA();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG200MA:
			{
				DBGACT_GenerateEN_Range200mA();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG2A:
			{
				DBGACT_GenerateEN_Range2A();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG20A:
			{
				DBGACT_GenerateEN_Range20A();
			}
			break;
			
		case ACT_DBG_ENABLE_RNG270A:
			{
				DBGACT_GenerateEN_Range270A();
			}
			break;
			
		case ACT_DBG_ENABLE_DISCHARGE:
			{
				DBGACT_GenerateImpulseBatteryDischarge();
			}
			break;
			
		case ACT_DBG_ENABLE_PSBOARD:
			{
				DBGACT_GenerateImpulsePSBoardOff();
			}
			break;
			
		case ACT_DBG_IMPULSE_SYNC1:
			{
				DBGACT_GenerateImpulseForceSYNC1();
			}
			break;
			
		case ACT_DBG_IMPULSE_SYNC2:
			{
				DBGACT_GenerateImpulseForceSYNC2();
			}
			break;
			
		case ACT_DBG_SEND_DATA_TO_DAC:
			{
				DBGACT_GenerateWriteToDACx(DataTable[REG_DBG_DATA], DataTable[REG_DBG_ENABLE_DEVICE]);
			}
			break;
			
		case ACT_DBG_SEND_DATA_TO_REG:
			{
				DBGACT_GenerateWriteToOutputRegister(DataTable[REG_DBG_DATA]);
			}
			break;
			
		case ACT_DBG_MEASURE_ADC:
			{
				DBGACT_MEASURE(DataTable[REG_DBG_DATA], DataTable[REG_DBG_ENABLE_DEVICE]);
			}
			break;
			
		default:
			return false;
	}
	
	return true;
}
//-----------------------------

