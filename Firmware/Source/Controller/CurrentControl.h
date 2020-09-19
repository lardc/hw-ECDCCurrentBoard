#ifndef __CURRENTCONTROL_H_
#define __CURRENTCONTROL_H_

// Include
#include "stdinc.h"
#include "Board.h"

// Defines
#define DAC_CHANNEL_B		BIT15

// Functions
uint16_t CC_ItoDAC(float Current);
float CC_CurrentSetup(float Current);
void CC_SetCurrentMax2A(float Current);
void CC_SetCurrentMax20A(float Current);
void CC_SetCurrentMax270A(float Current);
void CC_SetCurrentPulse(uint16_t OutData, float Current);
void CC_EnableCurrentChannel(float Current, float EnableFb);
float CC_EnableShuntRes (float Current);
//---------------------

#endif /* __CURRENTCONTROL_H_ */
