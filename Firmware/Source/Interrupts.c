// Include
#include "Interrupts.h"
//
#include "Controller.h"
#include "Measurement.h"
#include "LowLevel.h"
#include "Board.h"
#include "SysConfig.h"
#include "Global.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "CurrentControl.h"
#include "Logic.h"

// Variables
//
volatile float Correction = 0, PropKoef = 0, IntKoef = 0, Qp = 0, Qi = 0;
volatile float Vdut = 0, Idut = 0, AverageVdut = 0, AverageIdut = 0;
volatile uint32_t PulseCounter;
volatile float PulseToPulsePause;
volatile uint16_t OutPulse;

// Functions
//
void DMA2_Channel1_IRQHandler()
{
	float RegulatorError;
	
	if(DMA_IsTransferComplete(DMA2, DMA_ISR_TCIF1))
	{
		DMA_TransferCompleteReset(DMA2, DMA_IFCR_CTCIF1);
		
		if(CONTROL_SubState == SS_StartPulse)
		{
			Vdut = 0;
			Idut = 0;
			
			ADC_SamplingStop(ADC1);
			ADC_SamplingStop(ADC2);
			
			MEASURE_ReadDutCurrent(CurrentAmplitude);
			MEASURE_ReadDutVoltage(VoltageAmplitude);
			
			for(int i = 0; i < VALUES_OUT_SIZE; i++)
			{
				Vdut += CONTROL_ValuesDUTVoltage[i];
				Idut += CONTROL_ValuesDUTCurrent[i];
			}
			
			Vdut = Vdut / VALUES_OUT_SIZE;
			Idut = (Idut / VALUES_OUT_SIZE) / ShuntResistance;
			
			RegulatorError = (PulseCounter == 0) ? 0 : (PulseDataBuffer[PulseCounter - 1] - Idut);
			
			if(((RegulatorError / Idut * 100) < CTRL_FOLLOW_ERR) && (PulseCounter <= PULSE_BUFFER_SIZE))
			{
				Qp = RegulatorError * PropKoef;
				Qi += RegulatorError * IntKoef;
				
				Correction = PulseDataBuffer[PulseCounter] + Qp + Qi;
				
				LOGIC_FillEndPoint(Vdut, Idut, RegulatorError, Correction);
				
				if(PulseCounter >= (PULSE_BUFFER_SIZE - OFFSET_BUFFER_SIZE))
				{
					AverageVdut += Vdut/(PULSE_BUFFER_SIZE - OFFSET_BUFFER_SIZE);
					AverageIdut += Idut/(PULSE_BUFFER_SIZE - OFFSET_BUFFER_SIZE);
				}

				PulseCounter++;
				
				ADC_SamplingStart(ADC1);
				ADC_SamplingStart(ADC2);

				CC_SetCurrentPulse(Correction, CurrentAmplitude);
			}
			/*
			else if((RegulatorError / Idut * 100) >= CTRL_FOLLOW_ERR)
			{
				LL_ExternalLed(false);
				TIM_Stop(TIM6);
				CC_SetCurrentPulse(END_CURRENT_PULSE, CurrentAmplitude);
				CONTROL_SwitchToFault(DF_ERRORMAX);
			}
			*/
			else if(PulseCounter > PULSE_BUFFER_SIZE)
			{
				TIM_Stop(TIM6);
				CC_SetCurrentPulse(END_CURRENT_PULSE, CurrentAmplitude);
				DataTable[REG_IDUT_AVERAGE_LOW] = (Int16U)((uint32_t)AverageIdut & IV_MASK_LOW);
				DataTable[REG_IDUT_AVERAGE_HIGH] = (Int16U)(((uint32_t)AverageIdut & IV_MASK_HIGH) >> 16);
				DataTable[REG_VDUT_AVERAGE_LOW] = (Int16U)((uint32_t)AverageVdut & IV_MASK_LOW);
				DataTable[REG_VDUT_AVERAGE_HIGH] = (Int16U)(((uint32_t)AverageVdut & IV_MASK_HIGH) >> 16);
				CONTROL_SetDeviceSubState(SS_AfterPulseWaiting);
				CONTROL_SetDeviceState(DS_InProcess);
			}
		}
	}
}
//-----------------------------------------

void EXTI15_10_IRQHandler()
{
	if(CONTROL_CheckDeviceSubState(SS_StartPulse))
	{
		if(LL_GetSync1State())
		{
			ADC_SamplingStart(ADC1);
			ADC_SamplingStart(ADC2);
			TIM_Start(TIM6);
			LL_ForceSync1(false);
		}
	}
	EXTI_FlagReset(EXTI_13);
}
//-----------------------------------------

void USART1_IRQHandler()
{
	if(ZwSCI_RecieveCheck(USART1))
	{
		ZwSCI_RegisterToFIFO(USART1);
		ZwSCI_RecieveFlagClear(USART1);
	}
}
//-----------------------------------------

void USB_LP_CAN_RX0_IRQHandler()
{
	if(NCAN_RecieveCheck())
	{
		NCAN_RecieveData();
		NCAN_RecieveFlagReset();
	}
}
//-----------------------------------------

void TIM7_IRQHandler()
{
	static uint16_t LED_BlinkTimeCounter = 0;
	
	if(TIM_StatusCheck(TIM7))
	{
		
		CONTROL_TimeCounter++;
		if(++LED_BlinkTimeCounter > TIME_LED_BLINK)
		{
			LL_ToggleLed();
			LED_BlinkTimeCounter = 0;
		}
		
		TIM_StatusClear(TIM7);
	}
}
//-----------------------------------------

