// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"

// Functions
//
void LL_ToggleLED()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_ExternalLED(bool State)
{
	GPIO_SetState(GPIO_LED_EXT, State);
}
//-----------------------------

void LL_CTRL_VDUTAmp11V(bool State)
{
	GPIO_SetState(GPIO_CTRL_SEN_11V, State);
}
//-----------------------------

void LL_CTRL_VDUTAmp1500mV(bool State)
{
	GPIO_SetState(GPIO_CTRL_SEN_1500mV, State);
}
//-----------------------------

void LL_CTRL_VDUTAmp250mV(bool State)
{
	GPIO_SetState(GPIO_CTRL_SEN_250mV, State);
}
//-----------------------------

void LL_CTRL_VDUTAmp30mV(bool State)
{
	GPIO_SetState(GPIO_CTRL_SEN_30mV, State);
}
//-----------------------------

void LL_EN_Range20mA(bool State)
{
	GPIO_SetState(GPIO_EN_RANGE_20mA, State);
}
//-----------------------------

void LL_EN_Range200mA(bool State)
{
	GPIO_SetState(GPIO_EN_RANGE_200mA, State);
}
//-----------------------------

void LL_EN_Range2A(bool State)
{
	GPIO_SetState(GPIO_EN_RANGE_2A, State);
}
//-----------------------------

void LL_EN_Range20A(bool State)
{
	GPIO_SetState(GPIO_CTRL_RLC_20A, State);
}
//-----------------------------

void LL_EN_Range270A(bool State)
{
	bool ResState;

	ResState=!State;

	GPIO_SetState(GPIO_SET_RLC_270A, State);
	GPIO_SetState(GPIO_RES_RLC_270A, ResState);
}
//-----------------------------

void LL_BatteryDischarge(bool State)
{
	GPIO_SetState(GPIO_BAT_DISCHARGE, State);
}
//-----------------------------

void LL_PSBoardOff(bool State)
{
	GPIO_SetState(GPIO_PS_CTRL, State);
}
//-----------------------------

void LL_ForceSYNC1(bool State)
{
	GPIO_SetState(GPIO_SYNC_OUT1, State);
}
//-----------------------------

void LL_ForceSYNC2(bool State)
{
	GPIO_SetState(GPIO_SYNC_OUT2, State);
}
//-----------------------------

void LL_WriteDACx(uint16_t Data, GPIO_PortPinSetting GPIO_LDACx)
{
	GPIO_SetState(GPIO_CS, false);
	SPI_WriteByte(SPI1, Data);
	GPIO_SetState(GPIO_CS, true);
	DELAY_US(1);

	GPIO_SetState(GPIO_LDACx, false);
	DELAY_US(1);
	GPIO_SetState(GPIO_LDACx, true);
	DELAY_US(1);
}
//-----------------------------

void LL_OutputRegister_Write(uint16_t Data)
{
	GPIO_SetState(GPIO_SREG_CS, false);
	SPI_WriteByte(SPI1, Data);
	GPIO_SetState(GPIO_SREG_CS, true);
	GPIO_SetState(GPIO_SREG_OE, false);
}
//-----------------------------
