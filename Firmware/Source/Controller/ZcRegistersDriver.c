// -----------------------------------------
// Driver for IOExpansion buffers via SPI
// ----------------------------------------

// Header
#include "ZcRegistersDriver.h"
//
#include "SysConfig.h"
#include "CommutationTable.h"
#include "LowLevel.h"
#include "Delay.h"


// Constants
//
#define IO_REGISTER_WRITE_DELAY_US	10


// Variables
//
static uint8_t CurrentOutputValues[14];

void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	// Reset physical register
	LL_SPIReset();
}
// ----------------------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[CommutationTable[TableID].BoardNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].BoardNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------


void ZcRD_OutputValuesReset()
{
	uint8_t i;

	for (i = 0; i < 14; ++i)
		CurrentOutputValues[i] = 0x00;
}
// ----------------------------------------

void ZcRD_OutputValuesReset1()
{
	//CurrentOutputValues[] = {0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF};
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	int i;
	uint8_t CurrentOutputValuesCopy[14];
	uint8_t Data_Lenght = 14;

	for (i = 0; i < 14; ++i)
		CurrentOutputValuesCopy[i] = CurrentOutputValues[14 - i];

	GPIO_SetState(GPIO_SPI_OE, true);

	for (int i = 0; i <= Data_Lenght; i++)
	{
		SPI_WriteByte8b(SPI1, CurrentOutputValuesCopy[i]);
		//DELAY_MS(1);
		GPIO_SetState(GPIO_SPI_SS, true);
		//DELAY_MS(1);
		GPIO_SetState(GPIO_SPI_SS, false);
		//DELAY_MS(1);
	}

	GPIO_SetState(GPIO_SPI_OE, false);
}
// ----------------------------------------

// No more.
