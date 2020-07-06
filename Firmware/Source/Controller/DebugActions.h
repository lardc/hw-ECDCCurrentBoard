#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

#include "stdinc.h"

void DBGACT_GenerateImpulseExternalLED();
void DBGACT_GenerateCTRL_VDUTAmp11V();
void DBGACT_GenerateCTRL_VDUTAmp1500mV();
void DBGACT_GenerateCTRL_VDUTAmp250mV();
void DBGACT_GenerateCTRL_VDUTAmp30mV();
void DBGACT_GenerateEN_Range20mA();
void DBGACT_GenerateEN_Range200mA();
void DBGACT_GenerateEN_Range2A();
void DBGACT_GenerateEN_Range20A();
void DBGACT_GenerateEN_Range270A();
void DBGACT_GenerateImpulseBatteryDischarge();
void DBGACT_GenerateImpulsePSBoardOff();
void DBGACT_GenerateImpulseForceSYNC1();
void DBGACT_GenerateImpulseForceSYNC2();
void DBGACT_GenerateWriteToDACx(uint16_t Data, uint16_t LDACx);
void DBGACT_GenerateWriteToOutputRegister(uint16_t Data);
void DBGACT_MEASURE(uint16_t Data, uint16_t ADC_CHx);

#endif //__DEBUGACTIONS_H
