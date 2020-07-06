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
void DBGACT_GenerateImpulseExternalLED()
{
	LL_ExternalLED(true);
	CONTROL_DelayMs(1000);
	LL_ExternalLED(false);
}
//-----------------------------

void DBGACT_GenerateCTRL_VDUTAmp11V()
{
	LL_CTRL_VDUTAmp11V(true);
	CONTROL_DelayMs(1000);
	LL_CTRL_VDUTAmp11V(false);
}
//-----------------------------

void DBGACT_GenerateCTRL_VDUTAmp1500mV()
{
	LL_CTRL_VDUTAmp1500mV(true);
	CONTROL_DelayMs(1000);
	LL_CTRL_VDUTAmp1500mV(false);
}
//-----------------------------

void DBGACT_GenerateCTRL_VDUTAmp250mV()
{
	LL_CTRL_VDUTAmp250mV(true);
	CONTROL_DelayMs(1000);
	LL_CTRL_VDUTAmp250mV(false);
}
//-----------------------------

void DBGACT_GenerateCTRL_VDUTAmp30mV()
{
	LL_CTRL_VDUTAmp30mV(true);
	CONTROL_DelayMs(1000);
	LL_CTRL_VDUTAmp30mV(false);
}
//-----------------------------

void DBGACT_GenerateEN_Range20mA()
{
	LL_EN_Range20mA(true);
	CONTROL_DelayMs(1000);
	LL_EN_Range20mA(false);
}
//-----------------------------

void DBGACT_GenerateEN_Range200mA()
{
	LL_EN_Range200mA(true);
	CONTROL_DelayMs(1000);
	LL_EN_Range200mA(false);
}
//-----------------------------

void DBGACT_GenerateEN_Range2A()
{
	LL_EN_Range2A(true);
	CONTROL_DelayMs(1000);
	LL_EN_Range2A(false);
}
//-----------------------------

void DBGACT_GenerateEN_Range20A()
{
	LL_EN_Range20A(true);
	CONTROL_DelayMs(1000);
	LL_EN_Range20A(false);
}
//-----------------------------

void DBGACT_GenerateEN_Range270A()
{
	LL_EN_Range270A(true);
	CONTROL_DelayMs(1000);
	LL_EN_Range270A(false);
}
//-----------------------------

void DBGACT_GenerateImpulseBatteryDischarge()
{
	LL_BatteryDischarge(true);
	CONTROL_DelayMs(1000);
	LL_BatteryDischarge(false);
}
//-----------------------------

void DBGACT_GenerateImpulsePSBoardOff()
{
	LL_PSBoardOff(true);
	CONTROL_DelayMs(1000);
	LL_PSBoardOff(false);
}
//-----------------------------

void DBGACT_GenerateImpulseForceSYNC1()
{
	LL_ForceSYNC1(true);
	CONTROL_DelayMs(1000);
	LL_ForceSYNC1(false);
}
//-----------------------------

void DBGACT_GenerateImpulseForceSYNC2()
{
	LL_ForceSYNC2(true);
	CONTROL_DelayMs(1000);
	LL_ForceSYNC2(false);
}
//-----------------------------

void DBGACT_GenerateWriteToDACx(uint16_t Data, uint16_t LDACx)
{
	if (LDACx==1)
	{
		LL_WriteDACx(Data,GPIO_LDAC1);
	}
	else if (LDACx==2)
	{
		LL_WriteDACx(Data,GPIO_LDAC2);
	}
}
//-----------------------------

void DBGACT_GenerateWriteToOutputRegister(uint16_t Data)
{
	LL_OutputRegister_Write(Data);
}
//-----------------------------

void DBGACT_MEASURE(uint16_t Data, uint16_t ADC_CHx)
{
	if (ADC_CHx==1)
	{
		Data = ((uint16_t)ADC_Measure(ADC1, V_DUT_ADC1_CH))* ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
	else if (ADC_CHx==2)
	{
		Data = ((uint16_t)ADC_Measure(ADC2, I_DUT_ADC2_CH))* ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
	else if (ADC_CHx==3)
	{
		Data = ((uint16_t)ADC_Measure(ADC2, BAT_ADC2_CH))* ADC_REF_VOLTAGE / ADC_RESOLUTION;
	}
}
//-----------------------------

