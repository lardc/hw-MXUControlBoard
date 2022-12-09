#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"


// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateFPLed(bool State);
void LL_SetStateSFRedLed(bool State);
void LL_SetStateSFGreenLed(bool State);
void LL_ResetRegisters();
void LL_WriteSPI(uint8_t SPI_Data[], uint8_t DataLength);
void LL_StopSPI();
void LL_SetStateSF_EN(bool State);
void LL_SetStateSD_EN(bool State);
bool LL_SelfTestMeasure();

#endif //__LOWLEVEL_H
