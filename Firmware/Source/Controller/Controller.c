﻿// Header
#include "Controller.h"
//
// Includes
#include "math.h"
#include "Board.h"
#include "InitConfig.h"
#include "stdlib.h"
#include "Delay.h"
#include "DataTable.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "Global.h"
#include "LowLevel.h"
#include "Logic.h"
#include "Measurement.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "CurrentControl.h"
#include "BCCIxParams.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
volatile DeviceSubState CONTROL_SubState = SS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int16U CONTROL_AvrVoltageRaw[EP_VALUE];
volatile Int16U CONTROL_AvrCurrentRaw[EP_VALUE];
volatile Int16U CONTROL_RegulatorErrorRaw[EP_VALUE];
volatile Int16U CONTROL_OutDataRaw[EP_VALUE];
volatile Int16U CONTROL_ValuesCounter = 0;
volatile Int16U PulseDelayCounter = 0;
static Int16U CONTROL_BatteryVoltage;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_Init();
void CONTROL_UpdateWatchDog();
void CONTROL_KeepBatteryCharge();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware(bool KeepCharge);
void CONTROL_PowerOn();
void CONTROL_PowerOff();
void CONTROL_StartPulseConfig();
void CONTROL_ClearDataArrays();
void CONTROL_PrepareMeasurement();
void CONTROL_ResetRegistersOutputs();

// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_DUT_V, EP_DUT_I, EP_REG_ERROE, EP_OUT_DATA};
	Int16U EPSized[EP_COUNT] = {EP_VALUE, EP_VALUE, EP_VALUE, EP_VALUE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_ValuesCounter, (pInt16U)&CONTROL_ValuesCounter,
			(pInt16U)&CONTROL_ValuesCounter, (pInt16U)&CONTROL_ValuesCounter};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_AvrVoltageRaw, (pInt16U)CONTROL_AvrCurrentRaw,
			(pInt16U)CONTROL_RegulatorErrorRaw, (pInt16U)CONTROL_OutDataRaw};
	
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, 0);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetRegistersOutputs()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	DataTable[REG_ADC_VBAT_MEASURE] = 0;
	DataTable[REG_VDUT_AVERAGE_LOW] = 0;
	DataTable[REG_VDUT_AVERAGE_HIGH] = 0;
	DataTable[REG_IDUT_AVERAGE_LOW] = 0;
	DataTable[REG_IDUT_AVERAGE_HIGH] = 0;

	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	CONTROL_ResetRegistersOutputs();
	
	CONTROL_ResetHardware(true);
	CONTROL_SetDeviceSubState(SS_None);
	CONTROL_SetDeviceState(DS_None);
}
//------------------------------------------

void CONTROL_ResetHardware(bool KeepCharge)
{
	if (KeepCharge)
	{
		LL_DischargeBattery(false);
	}
	else
	{
		LL_DischargeBattery(true);
	}
	LOGIC_OffAllRelay();
	LL_ExternalLed(false);
	LL_EnableAmp11V(false);
	LL_EnableAmp1500mV(false);
	LL_EnableAmp250mV(false);
	LL_EnableAmp30mV(false);
	LL_SwitchPsBoard(true);
	LL_ForceSync1(false);
	LL_ForceSync2(false);
	LL_WriteOutReg(0);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();

	CONTROL_PowerOn();
	CONTROL_PowerOff();
	CONTROL_KeepBatteryCharge();

	CONTROL_StartPulseConfig();
	CONTROL_UpdateWatchDog();
}
//------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_FAULT_CLEAR:
			{
				if(CONTROL_State == DS_Fault)
					CONTROL_ResetToDefaultState();
			}
			break;
			
		case ACT_WARNING_CLEAR:
			DataTable[REG_WARNING] = 0;
			break;
			
		case ACT_ENABLE_POWER:
			{
				if(CONTROL_State == DS_None)
				{
					CONTROL_SetDeviceState(DS_InProcess);
					CONTROL_SetDeviceSubState(SS_PowerOn);
				}
				else if(CONTROL_State != DS_Ready)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
				{
					CONTROL_SetDeviceState(DS_None);
					CONTROL_SetDeviceSubState(SS_PowerOff);
				}
				else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
				break;
			}
			break;
			
		case ACT_START_PROCESS:
			{
				if(CONTROL_State == DS_Ready)
				{
					CONTROL_ResetRegistersOutputs();

					LL_ExternalLed(true);
					CONTROL_SetDeviceState(DS_InProcess);
					CONTROL_SetDeviceSubState(SS_PulseConfig);
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;
			
		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_InProcess)
				{
					CONTROL_ResetHardware(false);
					CONTROL_SetDeviceState(DS_Ready);
					CONTROL_SetDeviceSubState(SS_None);
				}
			}
			break;
			
		default:
			return DBGACT_HandleDiagnosticAction(ActionID, pUserError);
	}
	
	return true;
}
//------------------------------------------

void CONTROL_PowerOn()
{
	static Int64U Timeout = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case SS_PowerOn:
				{
					LL_DischargeBattery(true);
					DELAY_MS(12);
					Timeout = CONTROL_TimeCounter + TIME_BAT_CHARGE;
					CONTROL_SetDeviceState(DS_InProcess);
					CONTROL_SetDeviceSubState(SS_WaitCharging);
				}
				break;
				
			case SS_WaitCharging:
				{
					if(CONTROL_BatteryVoltage >= (BAT_VOLTAGE_THRESHOLD - BAT_VOLTAGE_DELTA))
					{
						CONTROL_SetDeviceState(DS_Ready);
						CONTROL_SetDeviceSubState(SS_None);
					}
					else if(Timeout < CONTROL_TimeCounter)
						CONTROL_SwitchToFault(DF_BATTERY);
				}
				break;
				
			default:
				break;
		}
	}
}
//------------------------------------------

void CONTROL_PowerOff()
{
	if(CONTROL_State == DS_None && CONTROL_SubState == SS_PowerOff)
	{
		CONTROL_ResetToDefaultState();
		CONTROL_SetDeviceState(DS_None);
		CONTROL_SetDeviceSubState(SS_None);
	}
}
//------------------------------------------

void CONTROL_StartPulseConfig()
{
	static Int64U NextPulseTime = 0, Timeout = 0;

	if(NextPulseTime < CONTROL_TimeCounter)
		DataTable[REG_AFTER_PULSE_DELAY] = 0;

	if(CONTROL_State == DS_InProcess)
	{
		switch (CONTROL_SubState)
		{
			case SS_PulseConfig:
				{
					LL_SwitchOutBus(false);
					LL_SwitchOutBus(true);
					LL_SwitchPsBoard(true);
					
					LOGIC_ClearDataArrays();
					LOGIC_CacheVariables();
					LOGIC_PulseConfig();
					LOGIC_EnableVoltageChannel(VoltageAmplitude);
					
					CC_EnableCurrentChannel(CurrentAmplitude, (float)DataTable[REG_EN_CURRENT_FB]);
					CC_SetCurrentPulse(END_CURRENT_PULSE, CurrentAmplitude);
					
					CONTROL_SetDeviceSubState(SS_PulseToPulsePause);
				}
				break;
				
			case SS_PulseToPulsePause:
				{
					if(CONTROL_TimeCounter > NextPulseTime)
					{
						Timeout = CONTROL_TimeCounter + TIME_BAT_CHARGE;
						CONTROL_SetDeviceSubState(SS_WaitBatteryVoltage);
					}
				}
				break;

			case SS_WaitBatteryVoltage:
				{
					if(CONTROL_BatteryVoltage > (BAT_VOLTAGE_THRESHOLD - BAT_VOLTAGE_DELTA))
					{
						LL_SwitchPsBoard(true);
						Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
						CONTROL_SetDeviceSubState(SS_PreWaitSync);
					}
					else if(CONTROL_TimeCounter > Timeout)
						CONTROL_SwitchToFault(DF_BATTERY);
				}
				break;

			case SS_PreWaitSync:
				{
					if(CONTROL_TimeCounter > Timeout)
						CONTROL_SetDeviceSubState(SS_StartPulse);
				}
				break;

			case SS_StartPulse:
				{
					NextPulseTime = CONTROL_TimeCounter + (Int16U)PulseToPulsePause;
					LL_ExternalLed(true);
					LL_ForceSync2(true);

					ADC_SamplingStart(ADC1);
					ADC_SamplingStart(ADC2);
					TIM_Start(TIM6);
					CONTROL_SetDeviceSubState(SS_StartRegulator);
				}
				break;
				
			case SS_AfterPulse:
				{
					LL_ExternalLed(false);
					LL_ForceSync2(false);
					LL_WriteOutReg(0);
					LOGIC_OffAllRelay();
					
					Timeout = CONTROL_TimeCounter + TIME_TRANSIENT_DELAY;
					CONTROL_SetDeviceSubState(SS_AfterPulseSwitchDelay);
				}
				break;

			case SS_AfterPulseSwitchDelay:
				{
					if(CONTROL_TimeCounter > Timeout)
					{
						uint16_t Problem = LOGIC_GetProblem();
						if(Problem == PROBLEM_NONE)
							DataTable[REG_OP_RESULT] = OPRESULT_OK;
						else
						{
							DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
							DataTable[REG_PROBLEM] = Problem;
						}

						DataTable[REG_AFTER_PULSE_DELAY] = 1;

						CONTROL_SetDeviceState(DS_Ready);
						CONTROL_SetDeviceSubState(SS_None);
					}
				}
				break;
				
			default:
				break;
		}
	}
}
//------------------------------------------

void CONTROL_KeepBatteryCharge()
{
	bool ActiveCharging = (CONTROL_State == DS_InProcess &&
			(CONTROL_SubState == SS_WaitBatteryVoltage || CONTROL_SubState == SS_WaitCharging));

	// Условие оцифровки напряжения батареи и управления зарядом
	if(CONTROL_State != DS_InProcess || ActiveCharging)
	{
		CONTROL_BatteryVoltage = MEASURE_GetBatteryVoltage();
		DataTable[REG_ADC_VBAT_MEASURE] = CONTROL_BatteryVoltage;

		// Управление зарядом батареи
		if(CONTROL_State == DS_Ready || ActiveCharging)
		{
			if(CONTROL_BatteryVoltage >= (BAT_VOLTAGE_THRESHOLD + BAT_VOLTAGE_DELTA))
			{
				LL_SwitchPsBoard(true);
			}
			else if(CONTROL_BatteryVoltage < (BAT_VOLTAGE_THRESHOLD -
					((CONTROL_SubState == SS_WaitBatteryVoltage) ? BAT_VOLTAGE_NEG_DELTA_ACTIVE : BAT_VOLTAGE_NEG_DELTA_PASSIVE)))
			{
				LL_SwitchPsBoard(false);
			}
		}
	}
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_ResetHardware(true);
	CONTROL_SetDeviceState(DS_Fault);
	CONTROL_SetDeviceSubState(SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
	DataTable[REG_SUB_STATE] = NewSubState;
	CONTROL_SubState = NewSubState;
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------
