#ifndef __DEBUGACTIONS_H
#define __DEBUGACTIONS_H

// Include
//
#include "ZwBase.h"

// Functions
//
void DBACT_ToggleBoardLED();
void DBACT_SetStateFP_LED();
void DBACT_SF_RED_LED();
void DBACT_SF_GRN_LED();
void DBACT_SPI_WRITE();
void DBACT_SPI_STOP_COMMUTATION();
bool DBACT_ADC_MEASURE_OPEN_CURCUIT();

#endif //__DEBUGACTIONS_H
