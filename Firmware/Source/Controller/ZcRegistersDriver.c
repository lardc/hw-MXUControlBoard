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
#include "DataTable.h"


// Constants
//
#define IO_REGISTER_WRITE_DELAY_US	10

// Variables
//
static uint8_t CurrentOutputValues[NUM_REGS_TOTAL] = {};

void ZcRD_RegisterReset()
{
	// Set values to zero
	ZcRD_OutputValuesReset();
	// Reset physical register
	LL_SPIReset();
}
// ----------------------------------------

void ZbIOE_OutputValuesDirect(Int16U BoardID, Int8U Mask)
{
	if (BoardID >= COMMUTATION_EXT_BOARDS)
		return;

	CurrentOutputValues[BoardID] = Mask;
}
// ----------------------------------------

void ZcRD_OutputValuesCompose(Int16U TableID, Boolean TurnOn)
{
	if (TurnOn)
		CurrentOutputValues[CommutationTable[TableID].RegNum] |= CommutationTable[TableID].Bit;
	else
		CurrentOutputValues[CommutationTable[TableID].RegNum] &= ~CommutationTable[TableID].Bit;
}
// ----------------------------------------


void ZcRD_OutputValuesReset()
{
	for (uint8_t i = 0; i < NUM_REGS_TOTAL; ++i)
		CurrentOutputValues[i] = 0;

	ZcRD_RegisterFlushWrite();
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	uint8_t CurrentOutputValuesCopy[(NUM_REGS_TOTAL - 1)];

	for (uint8_t i = 0; i < NUM_REGS_TOTAL; ++i)
		CurrentOutputValuesCopy[i] = CurrentOutputValues[(NUM_REGS_TOTAL - 1) - i];

	GPIO_SetState(GPIO_SPI_OE, true);

	for (uint8_t i = 0; i < NUM_REGS_TOTAL; i++)
	{
		SPI_WriteByte8b(SPI1, CurrentOutputValuesCopy[i]);
		DELAY_US(1);
		GPIO_SetState(GPIO_SPI_SS, true);
		DELAY_US(1);
		GPIO_SetState(GPIO_SPI_SS, false);
		DELAY_US(1);
	}

	GPIO_SetState(GPIO_SPI_OE, false);
}
// ----------------------------------------

// No more.
