#ifndef __CURRENTCONTROL_H_
#define __CURRENTCONTROL_H_

// Include
#include "stdinc.h"
#include "Board.h"

// Defines
#define DAC_CHANNEL_B		BIT15

// Functions
uint16_t CC_ItoDAC(float Current);
void CC_SetCurrentMax2A(float Current);
void CC_SetCurrentMax20A(float Current);
void CC_SetCurrentMax270A(float Current);
float CC_EnableCurrentChannel(float Current);

#endif /* __CURRENTCONTROL_H_ */
