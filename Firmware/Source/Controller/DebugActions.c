// Header
#include "DebugActions.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Delay.h"
#include "Controller.h"
#include "DataTable.h"

// Variables
uint8_t SPI_Data[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A};
uint8_t Data_Length = 0x74;

// Functions

// Send pulse to Front Panel LED
void DBACT_ToggleFPLed()
{
	LL_SetStateFPLed(true);
	DELAY_MS(1000);
	LL_SetStateFPLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Red LED
void DBACT_ToggleSFRedLed()
{
	LL_SetStateSFRedLed(true);
	DELAY_MS(1000);
	LL_SetStateSFRedLed(false);
}
//-----------------------

// Send pulse to Safety Subsystem Green LED
void DBACT_ToggleSFGreenLed()
{
	LL_SetStateSFGreenLed(true);
	DELAY_MS(1000);
	LL_SetStateSFGreenLed(false);
}
//-----------------------

// Write variable SPI_Data via SPI
void DBACT_WriteSPI()
{
	LL_WriteSPI(SPI_Data, Data_Length);
}
//-----------------------

// Stop commutation, reset shift-registers, turn outputs Hi-Z
void DBACT_StopSPI()
{
	LL_StopSPI();
}
//-----------------------

// Safety EN check
void DBACT_ToggleSF_EN()
{
	LL_SetStateSF_EN(true);
	DELAY_MS(1000);
	LL_SetStateSF_EN(false);
}
//-----------------------

// Turn self-test current ON, measure voltage with ADC, compare result with DataTable constant
void DBACT_SelfTestMeasure()
{
	LL_SelfTestMeasure();
}
//-----------------------
