#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

#include "stdinc.h"

void DBGACT_ImpulseExternalLed();
void DBGACT_SwitchAmp11V();
void DBGACT_SwitchAmp1500MV();
void DBGACT_SwitchAmp250MV();
void DBGACT_SwitchAmp30MV();
void DBGACT_SwitchRange20MA();
void DBGACT_SwitchRange200MA();
void DBGACT_SwitchRange2A();
void DBGACT_SwitchRange20A();
void DBGACT_SwitchRange270A();
void DBGACT_SwitchBatteryDischarge();
void DBGACT_SwitchPsBoard();
void DBGACT_ImpulseSync1();
void DBGACT_ImpulseSync2();
void DBGACT_GenerateWriteToDACx(uint16_t Data, uint16_t LDACx);
void DBGACT_MEASURE(uint16_t Data, uint16_t ADC_CHx);
bool DBGDBGACT_HandleDiagnosticAction(uint16_t ActionID, uint16_t *pUserError);

#endif //__DEBUGACTIONS_H
