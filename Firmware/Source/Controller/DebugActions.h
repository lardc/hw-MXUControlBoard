#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBACT_ToggleFPLed();
void DBACT_ToggleSFRedLed();
void DBACT_ToggleSFGreenLed();
void DBACT_WriteSPI();
void DBACT_SPI_PE_OFF();
void DBACT_SPI_Ileak_Gate_Emit_Pos();
void DBACT_SPI_Ileak_Gate_Emit_Neg();
void DBACT_StopSPI();
void DBACT_SPITurnOnOE();
void DBACT_SPITurnOffOE();
void DBACT_SPITurnOnSS();
void DBACT_SPITurnOffSS();
void DBACT_SPIReset();
void DBACT_TurnONSF_EN();
void DBACT_TurnOFFSF_EN();
void DBACT_TurnOFFSD_EN();
void DBACT_TurnONSD_EN();
void DBACT_SelfTestMeasure();

#endif //__DEBUGACTIONS_H
