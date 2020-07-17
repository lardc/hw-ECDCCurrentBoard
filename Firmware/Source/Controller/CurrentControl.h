#ifndef __CURRENTCONTROL_H_
#define __CURRENTCONTROL_H_

// Include
#include "stdinc.h"

uint16_t DAC_CHANNEL_B = 0x8000;

// Functions
uint16_t ��_ItoDAC(float Current);
void ��_SetCurrent(float Current);
void CC_EnableCurrentChannel(float Current);

#endif /* __CURRENTCONTROL_H_ */
