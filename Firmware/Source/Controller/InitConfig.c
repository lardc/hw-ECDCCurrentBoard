#include "InitConfig.h"
#include "Board.h"
#include "SysConfig.h"
#include "Controller.h"
#include "LowLevel.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"

// Functions
//
Boolean INITCFG_ConfigSystemClock()
{
	return RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
}
//------------------------------------------------

void INITCFG_ConfigIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	RCC_GPIO_Clk_EN(PORTC);
	
	// Аналаговые входы
	GPIO_InitAnalog(GPIO_MEASURE_V);
	GPIO_InitAnalog(GPIO_MEASURE_I);
	GPIO_InitAnalog(GPIO_MEASURE_VBAT);
	
	// Линия синхронизации (выходы)
	GPIO_InitPushPullOutput(GPIO_SYNC_OUT2);
	GPIO_InitPushPullOutput(GPIO_SYNC_OUT1);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_CS);
	GPIO_InitPushPullOutput(GPIO_LDAC1);
	GPIO_InitPushPullOutput(GPIO_LDAC2);
	GPIO_InitPushPullOutput(GPIO_ENABLE_11V);
	GPIO_InitPushPullOutput(GPIO_ENABLE_1500MV);
	GPIO_InitPushPullOutput(GPIO_SREG_OE);
	GPIO_InitPushPullOutput(GPIO_SREG_CS);
	GPIO_InitPushPullOutput(GPIO_ENABLE_200MA);
	GPIO_InitPushPullOutput(GPIO_ENABLE_250MV);
	GPIO_InitPushPullOutput(GPIO_ENABLE_30MV);
	GPIO_InitPushPullOutput(GPIO_ENABLE_20A);
	GPIO_InitPushPullOutput(GPIO_SET_RLC_270A);
	GPIO_InitPushPullOutput(GPIO_RESET_RLC_270A);
	GPIO_InitPushPullOutput(GPIO_DISCHARGE_BAT);
	GPIO_InitPushPullOutput(GPIO_CTRL_PS);
	GPIO_InitPushPullOutput(GPIO_ENABLE_2A);
	GPIO_InitPushPullOutput(GPIO_ENABLE_20MA);
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_LED_EXT);
	
	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_UART_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART_TX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_CLK, AltFn_5);
	GPIO_InitAltFunction(GPIO_ALT_SPI1_MOSI, AltFn_5);
}
//------------------------------------------------

void INITCFG_ConfigCAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, FALSE);
	NCAN_FIFOInterrupt(TRUE);
	NCAN_FilterInit(0, 0, 0); // Фильтр 0 пропускает все сообщения
}
//------------------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------------------

void INITCFG_ConfigSPI()
{
	SPI_Init(SPI1, SPI1_BAUDRATE_BITS, SPI1_LSB_FIRST);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);
	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_SoftTrigConfig(ADC1);
	ADC_SoftTrigConfig(ADC2);
	ADC_ChannelSet_SampleTime(ADC1, 1, ADC_SMPL_TIME_7_5);
	ADC_ChannelSet_SampleTime(ADC2, 1, ADC_SMPL_TIME_7_5);
	ADC_ChannelSet_SampleTime(ADC2, 3, ADC_SMPL_TIME_7_5);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);

	ADC_DMAConfig(ADC1);
	ADC_DMAConfig(ADC2);
	ADC_DMAEnable(ADC1, false);
	ADC_DMAEnable(ADC2, false);
}
//------------------------------------------------

void INITCFG_ConfigADCHighSpeed()
{
	ADC1_2_SetDualMode(true);

	ADC_Calibration(ADC1);
	ADC_Calibration(ADC2);
	ADC_Enable(ADC1);
	ADC_Enable(ADC2);
	ADC_TrigConfig(ADC1, ADC12_TIM6_TRGO, RISE);

	ADC_ChannelSeqReset(ADC1);
	ADC_ChannelSet_Sequence(ADC1, ADC1_VOLTAGE_CHANNEL, 1);
	ADC_ChannelSeqLen(ADC1, 1);

	ADC_ChannelSeqReset(ADC2);
	ADC_ChannelSet_Sequence(ADC2, ADC2_CURRENT_CHANNEL, 1);
	ADC_ChannelSeqLen(ADC2, 1);

	ADC_DMAEnable(ADC1, true);
	ADC_DMAEnable(ADC2, true);
}
//------------------------------------------------------------------------------

void INITCFG_DMAConfig()
{
	DMA_Clk_Enable(DMA1_ClkEN);
	DMA_Clk_Enable(DMA2_ClkEN);

	DMA_Reset(DMA_ADC_DUT_V_CHANNEL);
	DMAChannelX_DataConfig(DMA_ADC_DUT_V_CHANNEL, (uint32_t)CONTROL_DUTVoltageRaw, (uint32_t)(&ADC1->DR), VALUES_x_SIZE);
	DMAChannelX_Config(DMA_ADC_DUT_V_CHANNEL, DMA_MEM2MEM_DIS, DMA_LvlPriority_LOW, DMA_MSIZE_16BIT, DMA_PSIZE_16BIT,
						DMA_MINC_EN, DMA_PINC_DIS, DMA_CIRCMODE_DIS, DMA_READ_FROM_PERIPH);

	DMA_Reset(DMA_ADC_DUT_I_CHANNEL);
	DMAChannelX_DataConfig(DMA_ADC_DUT_I_CHANNEL, (uint32_t)CONTROL_DUTCurrentRaw, (uint32_t)(&ADC2->DR), VALUES_x_SIZE);
	DMAChannelX_Config(DMA_ADC_DUT_I_CHANNEL, DMA_MEM2MEM_DIS, DMA_LvlPriority_LOW, DMA_MSIZE_16BIT, DMA_PSIZE_16BIT,
						DMA_MINC_EN, DMA_PINC_DIS, DMA_CIRCMODE_DIS, DMA_READ_FROM_PERIPH);
}
//------------------------------------------------------------------------------

void INITCFG_ConfigTimer7()
{
	TIM_Clock_En(TIM_7);
	TIM_Config(TIM7, SYSCLK, TIMER7_uS);
	TIM_Interupt(TIM7, 0, true);
	TIM_Start(TIM7);
}
//------------------------------------------------

void INITCFG_ConfigTimer6()
{
	TIM_Clock_En(TIM_6);
	TIM_Config(TIM6, SYSCLK, TIMER6_uS);
	TIM_DMA(TIM6, DMAEN);
	TIM_MasterMode(TIM6, MMS_UPDATE);
}
//------------------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------------------
