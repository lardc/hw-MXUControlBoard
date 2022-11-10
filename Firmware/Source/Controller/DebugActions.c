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
const uint8_t SPI_Data[] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0x0A};

// Functions
//
void DBACT_ToggleBoardLED()
{
	LL_ToggleBoardLED(true);
	DELAY_MS(1000);
	LL_ToggleBoardLED(false);
}
//-----------------------

void DBACT_SetStateFP_LED()
{
	LL_SetStateFP_LED(true);
	DELAY_MS(1000);
	LL_SetStateFP_LED(false);
}
//-----------------------

void DBACT_SF_RED_LED()
{
	LL_SetStateSF_RED_LED(true);
	DELAY_MS(1000);
	LL_SetStateSF_RED_LED(false);
}
//-----------------------

void DBACT_SF_GRN_LED()
{
	LL_SetStateSF_GRN_LED(true);
	DELAY_MS(1000);
	LL_SetStateSF_GRN_LED(false);
}
//-----------------------

void DBACT_SPI_WRITE()
{
	SPI_Enable(SPI3, true);

	// Reset all shift-registers
	LL_SetStateSPI_RST(false);
	DELAY_MS(5);
	LL_SetStateSPI_RST(true);

	// Latch outputs of shift-registers
	LL_SetStateSPI_SS(false);

	// Send 15 bytes of data
	for (int i = 0; i<=15; i++)
		SPI_WriteByte(SPI3, SPI_Data[i]);

	// Turn outputs ON
	LL_SetStateSPI_OE(true);
}

void DBACT_SPI_STOP_COMMUTATION()
{
	// Turn outputs OFF
	LL_SetStateSPI_OE(false);

	LL_SetStateSPI_SS(true);

	// Reset all shift-registers
	LL_SetStateSPI_RST(false);
	DELAY_MS(5);
	LL_SetStateSPI_RST(true);
}

bool DBACT_ADC_MEASURE_OPEN_CURCUIT()
{
	float MeasuredTestVoltage, Error;

	LL_SetStateSD_EN(true);
	DELAY_MS(5);
	MeasuredTestVoltage = LL_ADC_Measure();
	LL_SetStateSD_EN(false);
	Error = (MeasuredTestVoltage - ADC_V_OC) / ADC_V_OC * 100;
	return (Error >= DataTable[REG_SFTST_V_ALLOWED_ERR]) ? false : true;
}

bool DBACT_ADC_MEASURE_CLOSE_CURCUIT()
{
	float MeasuredTestVoltage, Error;

	LL_SetStateSD_EN(true);
	DELAY_MS(5);
	MeasuredTestVoltage = LL_ADC_Measure();
	LL_SetStateSD_EN(false);
	Error = (MeasuredTestVoltage - ADC_V_CC) / ADC_V_CC * 100;
	return (Error >= DataTable[REG_SFTST_V_ALLOWED_ERR]) ? false : true;
}
