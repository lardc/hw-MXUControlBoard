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

#define NUM_REGS_HV_BOARD			5
#define NUM_REGS_THERM_BOARD		2
#define NUM_REGS_INPUT_BOARD		3
#define NUM_REGS_TOTAL ((NUM_REGS_HV_BOARD * 2) + NUM_REGS_THERM_BOARD + NUM_REGS_INPUT_BOARD)


// Variables
//
static uint8_t CurrentOutputValues[(NUM_REGS_TOTAL - 1)];

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

	for (i = 0; i < (NUM_REGS_TOTAL - 1); ++i)
		CurrentOutputValues[i] = 0x00;
}
// ----------------------------------------

void ZcRD_RegisterFlushWrite()
{
	int i;
	uint8_t CurrentOutputValuesCopy[(NUM_REGS_TOTAL - 1)];

	for (i = 0; i < 14; ++i)
		CurrentOutputValuesCopy[i] = CurrentOutputValues[(NUM_REGS_TOTAL - 1) - i];

	GPIO_SetState(GPIO_SPI_OE, true);

	for (int i = 0; i <= (NUM_REGS_TOTAL - 1); i++)
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
