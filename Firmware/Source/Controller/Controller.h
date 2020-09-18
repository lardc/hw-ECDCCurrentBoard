#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Include
#include "stdinc.h"

// Types
typedef enum __DeviceState
{
	DS_None = 0,
	DS_Fault = 1,
	DS_Disabled = 2,
	DS_Ready = 3,
	DS_InProcess = 4,
	DS_StartPulse = 5,
} DeviceState;

typedef enum __DeviceSubState
{
	SS_None = 0,
	SS_WaitingSync = 1,
	SS_PulsePrepareReady = 2,
	SS_WaitCharging = 3
} DeviceSubState;

// Variables
extern volatile DeviceState CONTROL_State;
extern volatile DeviceSubState CONTROL_SubState;
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;
extern volatile uint16_t CONTROL_DUTCurrentRaw[];
extern volatile uint16_t CONTROL_DUTVoltageRaw[];
extern volatile Int16U CONTROL_ValuesDUTVoltage[];
extern volatile Int16U CONTROL_ValuesDUTCurrent[];
extern volatile Int16U CONTROL_AvrVoltageRaw[];
extern volatile Int16U CONTROL_AvrCurrentRaw[];
extern volatile Int16U CONTROL_RegulatorErrorRaw[];
extern volatile Int16U CONTROL_OutDataRaw[];
extern volatile float PulseDataBuffer[];
extern volatile Int16U PulseDelayCounter;
extern volatile float Vdut, Idut, CurrentAmplitude, CurrentAmplifier, ShuntResistance, VoltageAmplitude,
		VoltageAmplifier;
extern volatile float Correction, RegulatorError, PropKoef, IntKoef, Qp, Qi;
// Functions
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_SetDeviceSubState(DeviceSubState NewSubState);
bool CONTROL_CheckDeviceSubState(DeviceSubState NewSubState);
void CONTROL_SwitchToFault(Int16U Reason);

#endif // __CONTROLLER_H
