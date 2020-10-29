#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "stdinc.h"

// Variables
extern volatile float Vdut, Idut;
extern volatile float Correction, RegulatorError, PropKoef, IntKoef, Qp, Qi;
extern volatile float Vdut, Idut, AverageVdut, AverageIdut;
extern volatile uint32_t PulseCounter;
extern volatile float PulseToPulsePause;
extern volatile uint16_t OutPulse;

#endif // __INTERRUPTS_H
