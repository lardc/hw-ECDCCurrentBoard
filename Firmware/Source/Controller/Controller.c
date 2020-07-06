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
	// Переменные для конфигурации EndPoint
	Int16U EPIndexes[EP_COUNT];
	Int16U EPSized[EP_COUNT];
	pInt16U EPCounters[EP_COUNT];
	pInt16U EPDatas[EP_COUNT];
	
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
	LL_ExternalLED(false);
	LL_PSBoardOff(false);
	LL_ForceSYNC1(false);
	LL_ForceSYNC2(false);
	LL_EN_Range20mA(false);
	LL_EN_Range200mA(false);
	LL_EN_Range2A(false);
	LL_EN_Range20A(false);
	LL_EN_Range270A(false);
	LL_BatteryDischarge(true);
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
					CONTROL_StartPrepare();
				}
				else
					*pUserError = ERR_DEVICE_NOT_READY;
			}
			break;
			
		case ACT_STOP_PROCESS:
			{
				if (CONTROL_State == DS_InProcess)
				{
					CONTROL_ResetToDefaultState();
				}
			}
			break;

			// Блок отладочных функция
			
		case ACT_DBG_Implse_ExternalLED:
			{
				DBGACT_GenerateImpulseExternalLED();
			}
			break;

		case ACT_DBG_CTRL_VDUTAmp11V:
			{
				DBGACT_GenerateCTRL_VDUTAmp11V();
			}
			break;

		case ACT_DBG_CTRL_VDUTAmp1500mV:
			{
				DBGACT_GenerateCTRL_VDUTAmp1500mV();
			}
			break;

		case ACT_DBG_CTRL_VDUTAmp250mV:
			{
				DBGACT_GenerateCTRL_VDUTAmp250mV();
			}
			break;

		case ACT_DBG_CTRL_VDUTAmp30mV:
			{
				DBGACT_GenerateCTRL_VDUTAmp30mV();
			}
			break;

		case ACT_DBG_EN_Range20mA:
			{
				DBGACT_GenerateEN_Range20mA();
			}
			break;

		case ACT_DBG_EN_Range200mA:
			{
				DBGACT_GenerateEN_Range200mA();
			}
			break;

		case ACT_DBG_EN_Range2A:
			{
				DBGACT_GenerateEN_Range2A();
			}
			break;

		case ACT_DBG_EN_Range20A:
			{
				DBGACT_GenerateEN_Range20A();
			}
			break;

		case ACT_DBG_EN_Range270A:
			{
				DBGACT_GenerateEN_Range270A();
			}
			break;

		case ACT_DBG_EN_BatteryDischarge:
			{
				DBGACT_GenerateImpulseBatteryDischarge();
			}
			break;

		case ACT_ACT_DBG_EN_PSBoardOutput:
			{
				DBGACT_GenerateImpulsePSBoardOff();
			}
			break;

		case ACT_DBG_Impulse_ForceSYNC1:
			{
				DBGACT_GenerateImpulseForceSYNC1();
			}
			break;

		case ACT_DBG_Impulse_ForceSYNC2:
			{
				DBGACT_GenerateImpulseForceSYNC2();
			}
			break;

		case ACT_DBG_SendDataToDACx:
			{
				DBGACT_GenerateWriteToDACx(DataTable[REG_DBG_IOData], DataTable[REG_DBG_ChanellSelect]);
			}
			break;

		case ACT_DBG_SendDataToOutRegister:
			{
				DBGACT_GenerateWriteToOutputRegister(DataTable[REG_DBG_IOData]);
			}
			break;

		case ACT_DBG_MEASURE_ADC_CH:
			{
				DBGACT_MEASURE(DataTable[REG_DBG_IOData], DataTable[REG_DBG_ChanellSelect]);
			}
			break;
		default:
			return false;
	}
	
	return true;
}
//------------------------------------------

void CONTROL_StartBatteryCharge()
{
	LL_BatteryDischarge(false);
	LL_PSBoardOff(false);

	CONTROL_ChargeTimeout = CONTROL_TimeCounter + TIME_BAT_CHARGE;

	CONTROL_SetDeviceState(DS_BatteryCharge);
}
//------------------------------------------

void CONTROL_BatteryChargeMonitorLogic()
{
	if (CONTROL_State == DS_BatteryCharge  || CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
	{
		float BatteryVoltage = MEASURE_GetBatteryVoltage();
		DataTable[REG_V_BAT_MEASURE] = (uint16_t)(BatteryVoltage * 10);

		if (CONTROL_State == DS_BatteryCharge)
		{
			if (BatteryVoltage >= BAT_VOLTAGE_THRESHOLD)
			{
				CONTROL_SetDeviceState(DS_Ready);
			}
			else if(CONTROL_TimeCounter > CONTROL_ChargeTimeout)
				CONTROL_SwitchToFault(DF_BATTERY);
		}

		if (CONTROL_State == DS_Ready || CONTROL_State == DS_InProcess)
		{
			if(BatteryVoltage >= (BAT_VOLTAGE_THRESHOLD + BAT_VOLTAGE_DELTA))
				LL_PSBoardOff(true);
			if(BatteryVoltage < BAT_VOLTAGE_THRESHOLD )
				LL_PSBoardOff(false);
		}
	}
}
//------------------------------------------

void CONTROL_StartPrepare()
{
	CONTROL_SetDeviceState(DS_InProcess);

	int16_t CurrentOrder = DataTable[REG_CURRENT_SETPOINT];

	if (CurrentOrder <= I_RANGE_20mA)
	{
		LL_EN_Range20mA(true);
		LL_EN_Range200mA(false);
		LL_EN_Range2A(false);
		LL_EN_Range20A(false);
		LL_EN_Range270A(false);
	}
	else if ((CurrentOrder > I_RANGE_20mA) && (CurrentOrder <= I_RANGE_200mA))
	{
		LL_EN_Range200mA(true);
		LL_EN_Range20mA(false);
		LL_EN_Range2A(false);
		LL_EN_Range20A(false);
		LL_EN_Range270A(false);
	}
	else if ((CurrentOrder > I_RANGE_200mA) && (CurrentOrder <= I_RANGE_2A))
	{
		LL_EN_Range2A(true);
		LL_EN_Range20mA(false);
		LL_EN_Range200mA(false);
		LL_EN_Range20A(false);
		LL_EN_Range270A(false);
	}
	else if ((CurrentOrder > I_RANGE_2A) && (CurrentOrder <= I_RANGE_20A))
	{
		LL_EN_Range20A(true);
		LL_EN_Range20mA(false);
		LL_EN_Range200mA(false);
		LL_EN_Range2A(false);
		LL_EN_Range270A(false);
	}
	else if ((CurrentOrder > I_RANGE_20A) && (CurrentOrder <= I_RANGE_270A))
	{
		LL_EN_Range270A(true);
		LL_EN_Range20mA(false);
		LL_EN_Range200mA(false);
		LL_EN_Range2A(false);
		LL_EN_Range20A(false);
	}
}

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

