// Header
#include "LowLevel.h"
// Include
#include "Board.h"
#include "Delay.h"

// Functions
//
void LL_ToggleLed()
{
	GPIO_Toggle(GPIO_LED);
}
//-----------------------------

void LL_ExternalLed(bool State)
{
	GPIO_SetState(GPIO_LED_EXT, State);
}
//-----------------------------

void LL_EnableAmp11V(bool State)
{
	GPIO_SetState(GPIO_ENABLE_11V, State);
}
//-----------------------------

void LL_EnableAmp1500mV(bool State)
{
	GPIO_SetState(GPIO_ENABLE_1500MV, State);
}
//-----------------------------

void LL_EnableAmp250mV(bool State)
{
	GPIO_SetState(GPIO_ENABLE_250MV, State);
}
//-----------------------------

void LL_EnableAmp30mV(bool State)
{
	GPIO_SetState(GPIO_ENABLE_30MV, State);
}
//-----------------------------

void LL_EnableRange20mA(bool State)
{
	GPIO_SetState(GPIO_ENABLE_20MA, State);
}
//-----------------------------

void LL_EnableRange200mA(bool State)
{
	GPIO_SetState(GPIO_ENABLE_200MA, State);
}
//-----------------------------

void LL_EnableRange2A(bool State)
{
	GPIO_SetState(GPIO_ENABLE_2A, State);
}
//-----------------------------

void LL_EnableRange20A(bool State)
{
	GPIO_SetState(GPIO_ENABLE_20A, State);
}
//-----------------------------

void LL_EnableRange270A(bool State)
{
	GPIO_SetState(GPIO_SET_RLC_270A, State);
}
//-----------------------------

void LL_DisableRange270A(bool State)
{
	GPIO_SetState(GPIO_RESET_RLC_270A, State);
}
//-----------------------------

void LL_DischargeBattery(bool State)
{
	GPIO_SetState(GPIO_DISCHARGE_BAT, State);
}
//-----------------------------

void LL_SwitchPsBoard(bool State)
{
	GPIO_SetState(GPIO_CTRL_PS, State);
}
//-----------------------------

void LL_ForceSync1(bool State)
{
	GPIO_SetState(GPIO_SYNC_OUT1, State);
}
//-----------------------------

void LL_ForceSync2(bool State)
{
	GPIO_SetState(GPIO_SYNC_OUT2, State);
}
//-----------------------------

bool LL_GetSync1State()
{
	return GPIO_GetState(GPIO_SYNC_OUT1);
}
//-----------------------------

bool LL_GetSync2State()
{
	return GPIO_GetState(GPIO_SYNC_OUT2);
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

void LL_WriteOutReg(uint16_t Data)
{
	GPIO_SetState(GPIO_SREG_CS, false);
	SPI_WriteByte(SPI1, Data);
	GPIO_SetState(GPIO_SREG_CS, true);
	GPIO_SetState(GPIO_SREG_OE, false);
}
//-----------------------------
