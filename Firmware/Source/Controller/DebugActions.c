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
uint8_t SPI_Data[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
uint8_t SPI_Data_PE_OFF[] = {0xFC, 0x00, 0x00, 0x00, 0x3F};
uint8_t SPI_Data_Ileak_Gate_Emitter_Pos[] = {0xFF, 0xA3, 0xCE, 0xBC, 0x3F};
uint8_t SPI_Data_Ileak_Gate_Emitter_Neg[] = {0xFF, 0xA3, 0xAF, 0x3C, 0x3F};
uint8_t SPI_Debug[] = {0x00, 0x00, 0x01, 0x00, 0x00};
uint8_t Data_Length = 4;

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

// Disable PE-Relays
void DBACT_SPI_PE_OFF()
{

	LL_WriteSPI(SPI_Data_PE_OFF, Data_Length);
}
//-----------------------

// Commutate Ileak of Gate-Emitter Positive Measurement
void DBACT_SPI_Ileak_Gate_Emit_Pos()
{

	LL_WriteSPI(SPI_Data_Ileak_Gate_Emitter_Pos, Data_Length);
}
//-----------------------

// Commutate Ileak of Gate-Emitter Negative Measurement
void DBACT_SPI_Ileak_Gate_Emit_Neg()
{
	LL_WriteSPI(SPI_Data_Ileak_Gate_Emitter_Neg, Data_Length);
}
//-----------------------

// Stop commutation, reset shift-registers, turn outputs Hi-Z
void DBACT_StopSPI()
{
	LL_StopSPI();
}
//-----------------------

// Turn OE On
void DBACT_SPITurnOnOE()
{
	LL_SPITurnOnOE();
}
//-----------------------

// Turn OE Off
void DBACT_SPITurnOffOE()
{
	LL_SPITurnOffOE();
}
//-----------------------

// Turn SS On
void DBACT_SPITurnOnSS()
{
	LL_SPITurnOnSS();
}
//-----------------------

// Turn SS Off
void DBACT_SPITurnOffSS()
{
	LL_SPITurnOffSS();
}
//-----------------------

// Reset All Registers
void DBACT_SPIReset()
{
	LL_SPIReset();
}
//-----------------------

// Safety EN check
void DBACT_TurnONSF_EN()
{
	LL_SetStateSF_EN(true);
}
//-----------------------

// Safety EN check
void DBACT_TurnOFFSF_EN()
{
	LL_SetStateSF_EN(false);
}
//-----------------------

void DBACT_TurnOFFSD_EN()
{
	LL_SetStateSD_EN(false);
}
//-----------------------

void DBACT_TurnONSD_EN()
{
	LL_SetStateSD_EN(true);
}
//-----------------------

// Turn self-test current ON, measure voltage with ADC, compare result with DataTable constant
void DBACT_SelfTestMeasure()
{
	float Result, Error;
	Result = LL_SelfTestMeasure();
	DataTable[REG_DBG] = Result;

	Error = (Result - ADC_V_CC) / Result * 100;

	if (Error >= 20)
	{
		DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_FAIL;
	}
	else
	{
		DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
	}
}
//-----------------------
