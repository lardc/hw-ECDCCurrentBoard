// Header
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
#include "Measurement.h"
#include "SysConfig.h"
#include "DebugActions.h"
#include "CurrentControl.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;
volatile Int64U CONTROL_TimeCounter = 0;
volatile Int64U CONTROL_ChargeTimeout = 0;
volatile Int16U CONTROL_Values_DUTVoltage[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_DUTCurrent[VALUES_x_SIZE];
volatile uint16_t CONTROL_DUTCurrentRaw[VALUES_x_SIZE];
volatile uint16_t CONTROL_DUTVoltageRaw[VALUES_x_SIZE];
volatile Int16U CONTROL_Values_Counter = 0;
volatile Int16U CONTROL_Values_DiagEPCounter = 0;
volatile Int16U PulseCounter = 0;
volatile Int16U PulseDelayCounter = 0;
float Vdut, Idut, CurrentAmplitude, CurrentAmplifier, ShuntResistance, VoltageAmplitude, VoltageAmplifier;
//
float Correction, RegulatorError, P_RegKoef, I_RegKoef, Qp, Qi;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_Init();
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware();
void CONTROL_StartBatteryCharge();
void CONTROL_BatteryChargeMonitorLogic();
void CONTROL_StartPrepare();
void CONTROL_StartPulse();
void CONTROL_SaveResultToEndpoints();
void CONTROL_ClearDataArrays();
void CONTROL_PrepareMeasurement();
void CONTROL_EnableMeasuremenChannel(float Current, float Voltage);


// Functions
//
void CONTROL_Init()
{
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT] = {EP_DUT_V, EP_DUT_I};
	Int16U EPSized[EP_COUNT] = {VALUES_x_SIZE, VALUES_x_SIZE};
	pInt16U EPCounters[EP_COUNT] = {(pInt16U)&CONTROL_Values_Counter, (pInt16U)&CONTROL_Values_Counter};
	pInt16U EPDatas[EP_COUNT] = {(pInt16U)CONTROL_Values_DUTVoltage, (pInt16U)CONTROL_Values_DUTCurrent};
	
	// Конфигурация сервиса работы Data-table и EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// Инициализация data table
	DT_Init(EPROMService, false);
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaultState();
}
//------------------------------------------

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	DataTable[REG_ACTUAL_BAT_VOLTAGE] = 0;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_ResetHardware();
	CONTROL_SetDeviceState(DS_None);
}
//------------------------------------------

void CONTROL_ResetHardware()
{
	LL_ExternalLed(false);
	LL_EnableAmp11V(false);
	LL_EnableAmp1500mV(false);
	LL_EnableAmp250mV(false);
	LL_EnableAmp30mV(false);
	LL_EnableRange20mA(false);
	LL_EnableRange200mA(false);
	LL_EnableRange2A(false);
	LL_EnableRange20A(false);
	LL_DisableRange270A(false);
	LL_DischargeBattery(false);
	LL_SwitchPsBoard(false);
	LL_WriteOutReg(0);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_BatteryChargeMonitorLogic();
	CONTROL_StartPulse();
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
				{
					CONTROL_ResetToDefaultState();
				}
			}
			break;
			
		case ACT_WARNING_CLEAR:
			DataTable[REG_WARNING] = 0;
			break;
			
		case ACT_ENABLE_POWER:
			{
				if(CONTROL_State == DS_None)
				{
					CONTROL_StartBatteryCharge();
				}
				else if(CONTROL_State != DS_Ready || CONTROL_State != DS_InProcess)
					*pUserError = ERR_OPERATION_BLOCKED;
				
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
				{
					CONTROL_ResetToDefaultState();
				}
				else
					*pUserError = ERR_OPERATION_BLOCKED;
				break;
			}
			break;
			
		case ACT_START_PROCESS:
			{
				if(CONTROL_State == DS_Ready)
				{
					CONTROL_StartPrepare();
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;
			
		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_Ready)
				{
					CONTROL_ResetToDefaultState();
				}
			}
			break;
			
		default:
			return DBGACT_HandleDiagnosticAction(ActionID, pUserError);
	}
	
	return true;
}
//------------------------------------------

void CONTROL_StartBatteryCharge()
{
	LL_SwitchPsBoard(true);
	CONTROL_ChargeTimeout = CONTROL_TimeCounter + TIME_BAT_CHARGE;
	CONTROL_SetDeviceState(DS_InProcess);
}
//------------------------------------------

void CONTROL_BatteryChargeMonitorLogic()
{
	float BatteryVoltage = MEASURE_GetBatteryVoltage();
	DataTable[REG_ADC_VBAT_MEASURE] = BatteryVoltage;
	
	if((BatteryVoltage >= BAT_VOLTAGE_THRESHOLD) && (CONTROL_State == DS_InProcess))
	{
		CONTROL_SetDeviceState(DS_Ready);
		LL_SwitchPsBoard(false);
	}
	else if(CONTROL_ChargeTimeout < CONTROL_TimeCounter)
		CONTROL_SwitchToFault(DF_BATTERY);
	
	if((CONTROL_TimeCounter >= PulseDelayCounter) && (CONTROL_State == DS_InProcess))
		CONTROL_SetDeviceState(DS_Ready);
	
}
//------------------------------------------

void CONTROL_StartPrepare()
{
	CONTROL_ClearDataArrays();
	CurrentAmplitude = (float)DataTable[REG_CURRENT_SETPOINT];
	VoltageAmplitude = (float)DataTable[REG_VOLTAGE_SETPOINT];
	ShuntResistance = CC_EnableCurrentChannel(CurrentAmplitude);
	CONTROL_PrepareMeasurement();
	CONTROL_SetDeviceState(DS_PulsePrepareReady);
}
//------------------------------------------

void CONTROL_StartPulse()
{
	if(CONTROL_State == DS_PulsePrepareReady)
	{
		LL_ExternalLed(true);
		
		CONTROL_EnableMeasuremenChannel(CurrentAmplitude, VoltageAmplitude);
		
		for(int i = 0; i < VALUES_x_SIZE; i++)
		{
			Vdut += CONTROL_Values_DUTVoltage[i];
			Vdut = Vdut / VALUES_x_SIZE;
			DataTable[REG_VDUT_AVERAGE] = Vdut;
			
			Idut += CONTROL_Values_DUTCurrent[i];
			Idut = Idut / VALUES_x_SIZE / ShuntResistance;
			DataTable[REG_IDUT_AVERAGE] = Idut;
		}
		
		ADC_SamplingStop(ADC1);
		ADC_SamplingStop(ADC2);
		
		RegulatorError = (PulseCounter == 0) ? 0 : (CurrentAmplitude - Idut);
		
		Qp = RegulatorError * P_RegKoef;
		Qi += RegulatorError * I_RegKoef;
		
		Correction = CurrentAmplitude + Qp + Qi;
		
		CC_SetCurrentPulse(Correction);
		
		PulseCounter++;
		
		LL_ExternalLed(false);
		
		INITCFG_ConfigADC();
		
		PulseDelayCounter = CONTROL_TimeCounter + Pulse2PulsePause;
		
		CONTROL_SetDeviceState(DS_InProcess);
	}
}
//------------------------------------------

void CONTROL_PrepareMeasurement(void)
{
	INITCFG_ConfigADCHighSpeed();
	
	DMA_ChannelReload(DMA_ADC_DUT_V_CHANNEL, CONTROL_Values_Counter);
	DMA_ChannelReload(DMA_ADC_DUT_I_CHANNEL, CONTROL_Values_Counter);
	
	DMA_ChannelEnable(DMA_ADC_DUT_V_CHANNEL, true);
	DMA_ChannelEnable(DMA_ADC_DUT_I_CHANNEL, true);
	
	ADC_SamplingStart(ADC1);
	ADC_SamplingStart(ADC2);
}

void CONTROL_EnableMeasuremenChannel(float Current, float Voltage)
{
	if(Current <= I_RANGE_2A)
	{
		MEASURE_ReadCurrent2A(CONTROL_DUTCurrentRaw, CONTROL_Values_DUTCurrent, VALUES_x_SIZE);
	}
	else
	{
		MEASURE_ReadCurrent270A(CONTROL_DUTCurrentRaw, CONTROL_Values_DUTCurrent, VALUES_x_SIZE);
	}
	
	if(Voltage <= V_RANGE_250MV)
	{
		MEASURE_ReadVoltage250mV(CONTROL_DUTVoltageRaw, CONTROL_Values_DUTVoltage, VALUES_x_SIZE);
	}
	else
	{
		MEASURE_ReadVoltage11V(CONTROL_DUTVoltageRaw, CONTROL_Values_DUTVoltage, VALUES_x_SIZE);
	}
}

void CONTROL_ClearDataArrays(void)
{
	uint16_t i;
	
	for(i = 0; i < VALUES_x_SIZE; ++i)
	{
		CONTROL_Values_DUTVoltage[i] = 0;
		CONTROL_Values_DUTCurrent[i] = 0;
	}
	CONTROL_Values_Counter = 0;
}
//-----------------------------------------------

void CONTROL_SaveResultToEndpoints()
{
	
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//------------------------------------------

void CONTROL_DelayMs(uint32_t Delay)
{
	uint64_t Counter = (uint64_t)CONTROL_TimeCounter + Delay;
	while(Counter > CONTROL_TimeCounter)
		CONTROL_UpdateWatchDog();
}
//------------------------------------------

void CONTROL_UpdateWatchDog()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//------------------------------------------
