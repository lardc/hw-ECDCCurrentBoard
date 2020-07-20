// Header
#include "Controller.h"
//
// Includes
#include "Board.h"
#include "Delay.h"
#include "DataTable.h"
#include "DeviceProfile.h"
#include "Interrupts.h"
#include "Global.h"
#include "LowLevel.h"
#include "Measurement.h"
#include "SysConfig.h"
#include "DebugActions.h"

// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
//
volatile DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;

volatile Int64U CONTROL_TimeCounter = 0;
Int64U CONTROL_ChargeTimeout = 0, CONTROL_LEDTimeout = 0;

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

// Functions
//
void CONTROL_Init()
{
	// ���������� ��� ������������ EndPoint
	Int16U EPIndexes[EP_COUNT];
	Int16U EPSized[EP_COUNT];
	pInt16U EPCounters[EP_COUNT];
	pInt16U EPDatas[EP_COUNT];
	
	// ������������ ������� ������ Data-table � EPROM
	EPROMServiceConfig EPROMService = {(FUNC_EPROM_WriteValues)&NFLASH_WriteDT, (FUNC_EPROM_ReadValues)&NFLASH_ReadDT};
	// ������������� data table
	DT_Init(EPROMService, false);
	// ������������� device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	DEVPROFILE_InitEPService(EPIndexes, EPSized, EPCounters, EPDatas);
	// ����� ��������
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
	LL_SwitchPsBoard(false);
	LL_ForceSync1(false);
	LL_ForceSync2(false);
	LL_EnableRange20mA(false);
	LL_EnableRange200mA(false);
	LL_EnableRange2A(false);
	LL_EnableRange20A(false);
	LL_EnableRange270A(false);
	LL_DischargeBattery(true);
}
//------------------------------------------

void CONTROL_Idle()
{
	DEVPROFILE_ProcessRequests();
	CONTROL_BatteryChargeMonitorLogic();
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
					
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;
			
		case ACT_STOP_PROCESS:
			{
				if(CONTROL_State == DS_InProcess)
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
	LL_DischargeBattery(false);
	LL_SwitchPsBoard(false);
	
	CONTROL_ChargeTimeout = CONTROL_TimeCounter + TIME_BAT_CHARGE;
	
	CONTROL_SetDeviceState(DS_InProcess);
}
//------------------------------------------

void CONTROL_BatteryChargeMonitorLogic()
{
	
	if(CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
	{
		float BatteryVoltage = MEASURE_GetBatteryVoltage();
		DataTable[REG_ADC_VBAT_MEASURE] = BatteryVoltage;
		
		if(BatteryVoltage >= BAT_VOLTAGE_THRESHOLD)
		{
			LL_SwitchPsBoard(false);
		}
		else if(BatteryVoltage < BAT_VOLTAGE_THRESHOLD)
		{
			LL_SwitchPsBoard(true);
		}
		else if(CONTROL_TimeCounter > CONTROL_ChargeTimeout)
			CONTROL_SwitchToFault(DF_BATTERY);
	}
}
//------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_ResetHardware();
	
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

