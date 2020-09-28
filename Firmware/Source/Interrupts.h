#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "stdinc.h"

// Variables
extern volatile float Vdut, Idut;
extern volatile float Correction, RegulatorError, PropKoef, IntKoef, Qp, Qi;
extern volatile uint32_t PulseCounter, PulseToPulsePause;

#endif // __INTERRUPTS_H
