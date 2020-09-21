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
volatile Int64U CONTROL_ChargeTimeout = 0;
volatile Int16U CONTROL_ValuesDUTVoltage[VALUES_OUT_SIZE];
volatile Int16U CONTROL_ValuesDUTCurrent[VALUES_OUT_SIZE];
volatile uint16_t CONTROL_DUTCurrentRaw[VALUES_OUT_SIZE];
volatile uint16_t CONTROL_DUTVoltageRaw[VALUES_OUT_SIZE];
volatile Int16U CONTROL_AvrVoltageRaw[EP_VALUE];
volatile Int16U CONTROL_AvrCurrentRaw[EP_VALUE];
volatile Int16U CONTROL_RegulatorErrorRaw[EP_VALUE];
volatile Int16U CONTROL_OutDataRaw[EP_VALUE];
volatile float PulseDataBuffer[PULSE_BUFFER_SIZE];
volatile Int16U CONTROL_ValuesCounter = 0;
volatile Int16U CONTROL_ValuesDiagEPCounter = 0;
volatile Int16U PulseDelayCounter = 0;
volatile float Vdut, Idut, CurrentAmplitude = 0, CurrentAmplifier = 0, ShuntResistance = 0, VoltageAmplitude = 0,
		VoltageAmplifier = 0;
volatile float Correction = 0, PropKoef = 0, IntKoef = 0, Qp = 0, Qi = 0;

// Forward functions
//
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_DelayMs(uint32_t Delay);
void CONTROL_Init();
void CONTROL_UpdateWatchDog();
void CONTROL_ResetToDefaultState();
void CONTROL_ResetHardware();
void CONTROL_StartBatteryCharge();
void CONTROL_BatteryChargeMonitorLogic();
void CONTROL_StartPrepare();
void CONTROL_ClearDataArrays();
void CONTROL_PrepareMeasurement();

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

void CONTROL_ResetToDefaultState()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
	DataTable[REG_ADC_VBAT_MEASURE] = 0;
	DataTable[REG_VDUT_AVERAGE] = 0;
	DataTable[REG_IDUT_AVERAGE] = 0;
	
	DEVPROFILE_ResetScopes(0);
	DEVPROFILE_ResetEPReadState();
	
	CONTROL_ResetHardware();
	CONTROL_SetDeviceSubState(SS_None);
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
	LL_ForceSync1(false);
	LL_ForceSync1(false);
	LL_WriteOutReg(0);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_UpdateWatchDog();
	CONTROL_BatteryChargeMonitorLogic();
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
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
				}
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
				{
					CONTROL_ResetToDefaultState();
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
				}
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
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
				}
			}
			break;
			
		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_Ready)
				{
					CONTROL_ResetToDefaultState();
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
				}
			}
			break;
			
		case ACT_START_DIAG_PULSE:
			{
				if(CONTROL_State == DS_StartPulse)
				{
					CONTROL_SetDeviceSubState(SS_WaitingSync);
					LL_ForceSync1(true);
				}
				else
				{
					DataTable[REG_OP_RESULT] = OPRESULT_FAIL;
					*pUserError = ERR_OPERATION_BLOCKED;
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
	
	if(CONTROL_State == DS_InProcess)
	{
		if(BatteryVoltage >= BAT_VOLTAGE_THRESHOLD)
		{
			CONTROL_SetDeviceState(DS_Ready);
			LL_SwitchPsBoard(false);
		}
		else if(CONTROL_ChargeTimeout < CONTROL_TimeCounter)
			CONTROL_SwitchToFault(DF_BATTERY);
	}
	
	if((CONTROL_TimeCounter >= PulseDelayCounter) && (CONTROL_State == DS_InProcess)
			&& (CONTROL_SubState == SS_WaitCharging))
	{
		if(BatteryVoltage >= BAT_VOLTAGE_THRESHOLD)
		{
			CONTROL_SetDeviceState(DS_Ready);
			CONTROL_SetDeviceSubState(SS_None);
			LL_SwitchPsBoard(false);
		}
		else
			LL_SwitchPsBoard(true);
	}
	else if(CONTROL_TimeCounter < PulseDelayCounter)
		CONTROL_SwitchToFault(DF_BATTERY);
	
}
//------------------------------------------

void CONTROL_StartPrepare()
{
	LOGIC_ClearDataArrays();
	
	LOGIC_CacheVariables();
	
	LOGIC_PulseConfig();
	
	LOGIC_EnableVoltageChannel(VoltageAmplitude);

	CC_EnableCurrentChannel(CurrentAmplitude, (float) DataTable[REG_EN_CURRENT_FB]);
	
	CONTROL_SetDeviceState(DS_StartPulse);
}
//------------------------------------------

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

void CONTROL_SetDeviceSubState(DeviceSubState NewSubState)
{
	CONTROL_SubState = NewSubState;
}
//------------------------------------------

bool CONTROL_CheckDeviceSubState(DeviceSubState NewSubState)
{
	if(CONTROL_SubState == NewSubState)
		return true;
	else
		return false;
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
