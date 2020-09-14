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
	DS_PulsePrepareReady = 5
} DeviceState;

// Variables
extern volatile Int64U CONTROL_TimeCounter;
extern Int64U CONTROL_LEDTimeout;
extern volatile uint16_t CONTROL_DUTCurrentRaw[];
extern volatile uint16_t CONTROL_DUTVoltageRaw[];

// Functions
void CONTROL_Init();
void CONTROL_Idle();

#endif // __CONTROLLER_H
