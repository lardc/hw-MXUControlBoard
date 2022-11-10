#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "Board.h"
#include "stdinc.h"


// Functions
//
void LL_ToggleBoardLED();
void LL_SetStateFP_LED(bool State);
void LL_SetStateSF_RED_LED(bool State);
void LL_SetStateSF_GRN_LED(bool State);
void LL_SetStateSPI_SS(bool State);
void LL_SetStateSPI_RST(bool State);
void LL_SetStateSPI_OE(bool State);
void LL_SetStateSF_EN(bool State);
void LL_SetStateSD_EN(bool State);
float LL_ADC_Measure();

#endif //__LOWLEVEL_H
